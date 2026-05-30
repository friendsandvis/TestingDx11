#include"SimpleQuadApplication.h"
#include"BasicModelManager.h"
void SimpleQuadApplication::InitExtras(ComPtr<ID3D11Device> device)
{
	//create shaders
	m_simplePixelShader.Init(device, L"shaders/simpletriangle/PS.hlsl", ShaderType::PS, "main");
	m_simpleVertexShader.Init(device, L"shaders/simpletriangle/VS.hlsl", ShaderType::VS, "main");
	//create triangle model data
	//vertexbuffer
		std::vector<VertexBase*> verticies;
		std::vector<unsigned int> indicies;
	BasicModelManager::GetQuadModelVerticiesIndexed(verticies, indicies, VertexVersion::VERTEXVERSION0);
	m_quadModel.Init(VertexVersion::VERTEXVERSION0, true);
	m_quadModel.SetVertexData(verticies, true);
	m_quadModel.SetIndexData(indicies);
	m_quadModel.CreateVertexBuffer(device);
	m_quadModel.CreateIndexBuffer(device);

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
	m_quadModel.BuildInputElementDesc(inputElementDescs);
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
		//constant buffer
	{
		PSConstantBuffer testConstantBuffer;
		testConstantBuffer.colour = { 1.0f,1.0f,1.0f,1.0f };
		D3D11_BUFFER_DESC testConstantBufferDesc = { 0 };
		testConstantBufferDesc.ByteWidth = sizeof(PSConstantBuffer);
		testConstantBufferDesc.Usage = D3D11_USAGE::D3D11_USAGE_DYNAMIC;
		testConstantBufferDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_CONSTANT_BUFFER;
		testConstantBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_WRITE;
		testConstantBufferDesc.MiscFlags = 0;
		testConstantBufferDesc.StructureByteStride = sizeof(PSConstantBuffer);
		D3D11_SUBRESOURCE_DATA psConstantB8ufferSubresData = { 0 };
		psConstantB8ufferSubresData.pSysMem = &testConstantBuffer;
		psConstantB8ufferSubresData.SysMemPitch = 0;
		psConstantB8ufferSubresData.SysMemSlicePitch = 0;
		DXASSERT(device->CreateBuffer(&testConstantBufferDesc, &psConstantB8ufferSubresData, m_psConstantBuffer.GetAddressOf()))
	}
	{
		m_VertexConstantBufferData.viewMat = DirectX::XMMatrixIdentity();
		m_VertexConstantBufferData.projMat = DirectX::XMMatrixIdentity();
		m_VertexConstantBufferData.modelMat = DirectX::XMMatrixIdentity();
		DirectX::XMVECTOR camPos = DirectX::XMVectorSet(0.0f, 0.0f, -3.0f, 1.0f);
		DirectX::XMVECTOR targetPos = DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f);
		DirectX::XMVECTOR upDir = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
		m_VertexConstantBufferData.viewMat = DirectX::XMMatrixLookAtLH(camPos, targetPos, upDir);
		m_VertexConstantBufferData.projMat = DirectX::XMMatrixOrthographicLH(m_swapchain.GetWidth(), m_swapchain.GetHeight(), 0.1f, 100.0f);
		m_VertexConstantBufferData.modelMat = DirectX::XMMatrixScaling(50.0f, 50.0f, 1.0f);
		D3D11_BUFFER_DESC vsConstantBufferDesc = { 0 };
		vsConstantBufferDesc.ByteWidth = sizeof(VertexConstantBuffer);
		vsConstantBufferDesc.Usage = D3D11_USAGE::D3D11_USAGE_DYNAMIC;
		vsConstantBufferDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_CONSTANT_BUFFER;
		vsConstantBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_WRITE;
		vsConstantBufferDesc.MiscFlags = 0;
		vsConstantBufferDesc.StructureByteStride = sizeof(PSConstantBuffer);
		D3D11_SUBRESOURCE_DATA vsConstantB8ufferSubresData = { 0 };
		vsConstantB8ufferSubresData.pSysMem = &m_VertexConstantBufferData;
		vsConstantB8ufferSubresData.SysMemPitch = 0;
		vsConstantB8ufferSubresData.SysMemSlicePitch = 0;
		DXASSERT(device->CreateBuffer(&vsConstantBufferDesc, &vsConstantB8ufferSubresData, m_vsConstantBuffer.GetAddressOf()))
	}
}
void SimpleQuadApplication::Render(RenderContext context)
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
	VertexVersionInfo vertInfo = VertexBase::GetVertexVersionInfo(VertexVersion::VERTEXVERSION0);
	UINT v_stride = vertInfo.stride;
	UINT v_offset = 0;
	context.m_mainContext->IASetVertexBuffers(0, 1, m_quadModel.GetVertexBuffer().GetDXBuffer().GetAddressOf(), &v_stride, &v_offset);
	if (m_quadModel.HasIndicies())
	{
		context.m_mainContext->IASetIndexBuffer(m_quadModel.GetIndexBuffer().GetDXBuffer().Get(), DXGI_FORMAT_R32_UINT, 0);
	}
	context.m_mainContext->IASetInputLayout(m_inputLayout.Get());
	context.m_mainContext->RSSetState(m_rasterState.Get());
	context.m_mainContext->OMSetBlendState(m_blendState.Get(), nullptr, 0xffffffff);
	//shader
	context.m_mainContext->VSSetShader(m_simpleVertexShader.GetVertexShader().Get(), NULL, 0);
	context.m_mainContext->PSSetShader(m_simplePixelShader.GetPixelShader().Get(), NULL, 0);
	//draw
	context.m_mainContext->PSSetConstantBuffers(0, 1, m_psConstantBuffer.GetAddressOf());
	context.m_mainContext->VSSetConstantBuffers(1, 1, m_vsConstantBuffer.GetAddressOf());
	if (m_quadModel.HasIndicies())
	{
		context.m_mainContext->DrawIndexed(m_quadModel.GetIndiciesCount(), 0, 0);
	}
	else
	{
		context.m_mainContext->Draw(m_quadModel.GetVertexCount(), 0);
	}
	m_swapchain.Present();
}