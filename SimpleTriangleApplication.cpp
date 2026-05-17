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
	
	m_triangleModel.Init(VertexVersion::VERTEXVERSION0);
	m_triangleModel.SetVertexData(verticies, true);
	std::vector<float>& verticiesDataRaw = m_triangleModel.GetVerticiesRawData();//VertexBase::BuildRawVertexBuffer(verticies, verticiesDataRaw);
	m_triangleModel.CreateVertexBuffer(device);

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
	m_triangleModel.BuildInputElementDesc(inputElementDescs);
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
	 VertexVersionInfo vertInfo =VertexBase::GetVertexVersionInfo(VertexVersion::VERTEXVERSION0);
	UINT v_stride = vertInfo.stride;
	UINT v_offset = 0;
	context.m_mainContext->IASetVertexBuffers(0, 1, m_triangleModel.GetVertexBuffer().GetDXBuffer().GetAddressOf(),&v_stride, &v_offset);
	context.m_mainContext->IASetInputLayout(m_inputLayout.Get());
	context.m_mainContext->RSSetState(m_rasterState.Get());
	context.m_mainContext->OMSetBlendState(m_blendState.Get(),nullptr, 0xffffffff);
	//shader
	context.m_mainContext->VSSetShader(m_simpleVertexShader.GetVertexShader().Get(),NULL,0);
	context.m_mainContext->PSSetShader(m_simplePixelShader.GetPixelShader().Get(), NULL, 0);
	//draw
	context.m_mainContext->Draw(m_triangleModel.GetVertexCount(), 0);
	m_swapchain.Present();
}