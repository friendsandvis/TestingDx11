#include"SimpleTriangleApplication.h"
#include"BasicModelManager.h"
void SimpleTriangleApplication::InitExtras(ComPtr<ID3D11Device> device)
{
	//create shaders
	m_simplePixelShader.Init(device, L"shaders/simpletriangle/PS.hlsl", ShaderType::PS, "main");
	m_simpleVertexShader.Init(device,L"shaders/simpletriangle/VS.hlsl",ShaderType::VS,"main");
	//create triangle model data
	//vertexbuffer
	std::vector<VertexBase*> verticies;
	BasicModelManager::GetTriangleModelVerticies_NDC(verticies,VertexVersion::VERTEXVERSION0);//GetTriangleVertices(verticies);
	std::vector<float> verticiesDataRaw;
	VertexBase::BuildRawVertexBuffer(verticies, verticiesDataRaw);
	assert(verticiesDataRaw.size() > 0);
	D3D11_BUFFER_DESC vertexBufferDesc = {};
	//only vertex v0 used in here for test
	vertexBufferDesc.ByteWidth = sizeof(verticiesDataRaw[0]) * verticiesDataRaw.size();
	vertexBufferDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.Usage = D3D11_USAGE::D3D11_USAGE_IMMUTABLE;
	D3D11_SUBRESOURCE_DATA vertexBufferInitData = {};
	vertexBufferInitData.pSysMem = reinterpret_cast<void*>(verticiesDataRaw.data());
	vertexBufferInitData.SysMemPitch = 0;
	vertexBufferInitData.SysMemSlicePitch = 0;
	m_triangle_vertexBuffer.Init(device, vertexBufferDesc,vertexBufferInitData);

	//raster state
	D3D11_RASTERIZER_DESC rasterDesc = {};
	rasterDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
	rasterDesc.DepthClipEnable = FALSE;
	rasterDesc.ScissorEnable = FALSE;
	rasterDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_NONE;
	rasterDesc.FrontCounterClockwise = FALSE;
	DXASSERT(device->CreateRasterizerState(&rasterDesc, m_rasterState.GetAddressOf()))
		//input layout
		std::vector<D3D11_INPUT_ELEMENT_DESC> inputElementDescs;
	{
		D3D11_INPUT_ELEMENT_DESC inputElementDescPos = {};
		inputElementDescPos.InputSlot = 0;
		inputElementDescPos.SemanticName = "POS";
		inputElementDescPos.SemanticIndex = 0;
		inputElementDescPos.Format = DXGI_FORMAT::DXGI_FORMAT_R32G32B32_FLOAT;
		inputElementDescPos.InputSlotClass = D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA;
		inputElementDescPos.AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
		inputElementDescs.push_back(inputElementDescPos);
	}
	{
		D3D11_INPUT_ELEMENT_DESC inputElementDescVUV = {};
		inputElementDescVUV.InputSlot = 0;
		inputElementDescVUV.SemanticName = "VUV";
		inputElementDescVUV.SemanticIndex = 0;
		inputElementDescVUV.Format = DXGI_FORMAT::DXGI_FORMAT_R32G32_FLOAT;
		inputElementDescVUV.InputSlotClass = D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA;
		inputElementDescVUV.AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
		inputElementDescs.push_back(inputElementDescVUV);
	}
		ComPtr<ID3DBlob> vsCompiledCode = m_simpleVertexShader.GetCompiledCode();
		assert(vsCompiledCode->GetBufferPointer() != nullptr);
		DXASSERT(device->CreateInputLayout(inputElementDescs.data(), inputElementDescs.size(), vsCompiledCode->GetBufferPointer(), vsCompiledCode->GetBufferSize(), m_inputLayout.GetAddressOf()))

			//blendstate
			D3D11_BLEND_DESC blendDesc = {};
		blendDesc.AlphaToCoverageEnable = FALSE;
		blendDesc.IndependentBlendEnable = FALSE;
		for (unsigned int i = 0; i < 8; i++)
		{
			blendDesc.RenderTarget[i].BlendEnable = FALSE;
			blendDesc.RenderTarget[i].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
		}
		DXASSERT(device->CreateBlendState(&blendDesc, m_blendState.GetAddressOf()))
}
void SimpleTriangleApplication::Render(RenderContext context)
{
	context.m_mainContext->OMSetRenderTargets(1, m_swapchain.GetBackBufferRTV().GetAddressOf(), nullptr);
	D3D11_RECT scissorRect = GetScissorRect();
	context.m_mainContext->RSSetScissorRects(1, &scissorRect);
	D3D11_VIEWPORT viewport = GetViewport();
	context.m_mainContext->RSSetViewports(1, &viewport);
	float clearcolour[4] = { 0.0f,1.0f,0.0f,1.0f };
	context.m_mainContext->ClearRenderTargetView(m_swapchain.GetBackBufferRTV().Get(), clearcolour);
	//----pipeline states
	context.m_mainContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	//calculate  add stride and offset based on hardcoded assumption of using VertexVersion0 get from vertexdata used for triangle rendering.
	UINT v_stride = sizeof(float) * 5;
	UINT v_offset = 0;
	context.m_mainContext->IASetVertexBuffers(0, 1, m_triangle_vertexBuffer.GetDXBuffer().GetAddressOf(),&v_stride, &v_offset);
	context.m_mainContext->IASetInputLayout(m_inputLayout.Get());
	context.m_mainContext->RSSetState(m_rasterState.Get());
	context.m_mainContext->OMSetBlendState(m_blendState.Get(),nullptr, 0xffffffff);
	//shader
	context.m_mainContext->VSSetShader(m_simpleVertexShader.GetVertexShader().Get(),NULL,0);
	context.m_mainContext->PSSetShader(m_simplePixelShader.GetPixelShader().Get(), NULL, 0);
	//draw
	context.m_mainContext->Draw(3, 0);
	m_swapchain.Present();
}