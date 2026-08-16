#include"SimpleCubeApplication.h"
#include"BasicModelManager.h"
/*
* quick notes on depth testing in dx11 depth clip needed to cull if not in frustum set for projection
* note the cam position when specifing z translates for model matrix viewmatrix also translate to bring cam to 0.0( so negitice for cam z is added.
* not forget viewport depth min/max as they are used to map depth from Vertex shader to a final depth value used further in pipe till wtrie.
* 
*/
//TODO: shader used here is used elsewhere to make other places used matrix preupload processing too.
void SimpleCubeApplication::InitExtras(ComPtr<ID3D11Device> device)
{
	//create shaders
	m_simplePixelShader.Init(device, L"shaders/simplecube/PS.hlsl", ShaderType::PS, "main");
	m_simpleVertexShader.Init(device, L"shaders/simplecube/VS.hlsl", ShaderType::VS, "main");
	//create quad model data
	{
		std::vector<VertexBase*> verticies;
		std::vector<unsigned int> indicies;
		BasicModelManager::GetQuadModelVerticiesIndexed(verticies, indicies, VertexVersion::VERTEXVERSION0);
		m_quadModel.Init(VertexVersion::VERTEXVERSION0, true);
		m_quadModel.SetVertexData(verticies, true);
		m_quadModel.SetIndexData(indicies);
		m_quadModel.CreateVertexBuffer(device);
		m_quadModel.CreateIndexBuffer(device);
	}
	//create cube model data
	{
		std::vector<VertexBase*> verticies;
		std::vector<unsigned int> indicies;
		BasicModelManager::GetCubeModelVerticiesIndexed(verticies, indicies, VertexVersion::VERTEXVERSION0);
		m_cubeModel.Init(VertexVersion::VERTEXVERSION0, true);
		m_cubeModel.SetVertexData(verticies, true);
		m_cubeModel.SetIndexData(indicies);
		m_cubeModel.CreateVertexBuffer(device);
		m_cubeModel.CreateIndexBuffer(device);
	}
	//raster state
	D3D11_RASTERIZER_DESC rasterDesc = {};
	rasterDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
	rasterDesc.DepthClipEnable = FALSE;
	rasterDesc.ScissorEnable = FALSE;
	rasterDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_NONE;
	rasterDesc.FrontCounterClockwise = FALSE;
	rasterDesc.DepthClipEnable = TRUE;
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
		//camera setup
	{
		DirectX::XMVECTOR camPos = DirectX::XMVectorSet(0.0f, 0.0f, -3.0f, 1.0f);
		DirectX::XMVECTOR targetPos = DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f);
		float nearPlane = 0.01f;
		float farPlane = 100.0f;
		float viewWidth = static_cast<float>(m_swapchain.GetWidth());
		float viewHeight = static_cast<float>(m_swapchain.GetHeight());
		m_Maincamera.Reset(camPos,targetPos, viewWidth, viewHeight, nearPlane, farPlane);
		m_maincameracontroller.SetCameratoControl(&m_Maincamera);
	}
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
		m_VertexConstantBufferData.viewMat = m_Maincamera.GetViewMat();
		m_VertexConstantBufferData.viewMat = ProcessMatrixForShaderUse(m_VertexConstantBufferData.viewMat);
		m_VertexConstantBufferData.projMat = m_Maincamera.GetProjectionMat(false);
		m_VertexConstantBufferData.projMat = ProcessMatrixForShaderUse(m_VertexConstantBufferData.projMat);
		XMMATRIX scaleMat = DirectX::XMMatrixScaling(50.0f, 50.0f, 1.0f);
		m_VertexConstantBufferData.modelMat = scaleMat;
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
	//create depth stencil resource and dsv
	{
		D3D11_TEXTURE2D_DESC depthStencilTexDesc = {};
		depthStencilTexDesc.Format = DXGI_FORMAT::DXGI_FORMAT_D32_FLOAT;
		depthStencilTexDesc.Width = m_swapchain.GetWidth();
		depthStencilTexDesc.Height = m_swapchain.GetHeight();
		depthStencilTexDesc.MipLevels = 1;
		depthStencilTexDesc.ArraySize = 1;
		depthStencilTexDesc.SampleDesc.Count = 1;
		depthStencilTexDesc.SampleDesc.Quality = 0;
		depthStencilTexDesc.Usage = D3D11_USAGE::D3D11_USAGE_DEFAULT;
		depthStencilTexDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_DEPTH_STENCIL;
		depthStencilTexDesc.CPUAccessFlags = 0;
		depthStencilTexDesc.MiscFlags = 0;
		DXASSERT(device->CreateTexture2D(&depthStencilTexDesc, nullptr, m_depthStencilTex.GetAddressOf()))
			DXASSERT(device->CreateDepthStencilView(m_depthStencilTex.Get(), nullptr, m_depthStencilView.GetAddressOf()))
	}
	//depth stencil state
	{
		D3D11_DEPTH_STENCIL_DESC depthStencilStateDesc = {};
		depthStencilStateDesc.DepthEnable = TRUE;
		depthStencilStateDesc.StencilEnable = FALSE;
		depthStencilStateDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK::D3D11_DEPTH_WRITE_MASK_ALL;
		depthStencilStateDesc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS;
		device->CreateDepthStencilState(&depthStencilStateDesc, m_depthStencilState.GetAddressOf());

	}

}
void SimpleCubeApplication::Render(RenderContext context)
{
	context.m_mainContext->OMSetRenderTargets(1, m_swapchain.GetBackBufferRTV().GetAddressOf(), m_depthStencilView.Get());
	D3D11_RECT scissorRect = GetScissorRect();
	context.m_mainContext->RSSetScissorRects(1, &scissorRect);
	D3D11_VIEWPORT viewport = GetViewport();
	context.m_mainContext->RSSetViewports(1, &viewport);
	float clearcolour[4] = { 0.0f,1.0f,0.0f,1.0f };
	context.m_mainContext->ClearRenderTargetView(m_swapchain.GetBackBufferRTV().Get(), clearcolour);
	context.m_mainContext->ClearDepthStencilView(m_depthStencilView.Get(), D3D11_CLEAR_FLAG::D3D11_CLEAR_DEPTH, 1.0f, 0);
	context.m_mainContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	//common states setup
	context.m_mainContext->IASetInputLayout(m_inputLayout.Get());
	context.m_mainContext->RSSetState(m_rasterState.Get());
	context.m_mainContext->OMSetBlendState(m_blendState.Get(), nullptr, 0xffffffff);
	context.m_mainContext->OMSetDepthStencilState(m_depthStencilState.Get(), 0);
	//shader
	context.m_mainContext->VSSetShader(m_simpleVertexShader.GetVertexShader().Get(), NULL, 0);
	context.m_mainContext->PSSetShader(m_simplePixelShader.GetPixelShader().Get(), NULL, 0);
	//draw
	context.m_mainContext->PSSetConstantBuffers(0, 1, m_psConstantBuffer.GetAddressOf());
	context.m_mainContext->VSSetConstantBuffers(1, 1, m_vsConstantBuffer.GetAddressOf());
	RenderCube(context);//RenderTestQuadsDepthCheck(context);
	m_swapchain.Present();
}

void SimpleCubeApplication::RenderTestQuadsDepthCheck(RenderContext& context)
{
	//draw front quad  1 for depth testing checks(z at 3))red
	{
		//change constant buffer data for quad 1
		{
			D3D11_MAPPED_SUBRESOURCE vertexConstBufferMapped = {};
			DXASSERT(context.m_mainContext->Map(m_vsConstantBuffer.Get(), 0, D3D11_MAP::D3D11_MAP_WRITE_DISCARD, 0, &vertexConstBufferMapped))
				XMMATRIX scaleMat = DirectX::XMMatrixScaling(10.0f, 10.0f, 1.0f);
			XMMATRIX translateMat = DirectX::XMMatrixTranslation(0.0f, 0.0f, 3.0f);
			m_VertexConstantBufferData.modelMat = scaleMat * translateMat;
			m_VertexConstantBufferData.modelMat = ProcessMatrixForShaderUse(m_VertexConstantBufferData.modelMat);
			memcpy(vertexConstBufferMapped.pData, &m_VertexConstantBufferData, sizeof(VertexConstantBuffer));
			context.m_mainContext->Unmap(m_vsConstantBuffer.Get(), 0);
		}
		{
			PSConstantBuffer pixelConstantBufferData;
			pixelConstantBufferData.colour = { 1.0f,0.0f,0.0f,1.0f };
			D3D11_MAPPED_SUBRESOURCE pixelConstBufferMapped = {};
			DXASSERT(context.m_mainContext->Map(m_psConstantBuffer.Get(), 0, D3D11_MAP::D3D11_MAP_WRITE_DISCARD, 0, &pixelConstBufferMapped))
				memcpy(pixelConstBufferMapped.pData, &pixelConstantBufferData, sizeof(PSConstantBuffer));
			context.m_mainContext->Unmap(m_psConstantBuffer.Get(), 0);
		}
		m_quadModel.Draw(&context);
	}
	//draw quad 2(white)
	{
		//update constant buffer for quad 2(z at 2)
		{
			{
				D3D11_MAPPED_SUBRESOURCE vertexConstBufferMapped = {};
				DXASSERT(context.m_mainContext->Map(m_vsConstantBuffer.Get(), 0, D3D11_MAP::D3D11_MAP_WRITE_DISCARD, 0, &vertexConstBufferMapped))
					XMMATRIX scaleMat = DirectX::XMMatrixScaling(5.0f, 5.0f, 1.0f);
				//translation diffrent from quad 1 just by z to test depth testing(render only based on depth validity)
				XMMATRIX translateMat = DirectX::XMMatrixTranslation(-0.3f, 0.5f, 2.0f);
				m_VertexConstantBufferData.modelMat = scaleMat * translateMat;
				m_VertexConstantBufferData.modelMat = ProcessMatrixForShaderUse(m_VertexConstantBufferData.modelMat);
				memcpy(vertexConstBufferMapped.pData, &m_VertexConstantBufferData, sizeof(VertexConstantBuffer));
				context.m_mainContext->Unmap(m_vsConstantBuffer.Get(), 0);
			}
			{
				PSConstantBuffer pixelConstantBufferData;
				pixelConstantBufferData.colour = { 1.0f,1.0f,1.0f,1.0f };
				D3D11_MAPPED_SUBRESOURCE pixelConstBufferMapped = {};
				DXASSERT(context.m_mainContext->Map(m_psConstantBuffer.Get(), 0, D3D11_MAP::D3D11_MAP_WRITE_DISCARD, 0, &pixelConstBufferMapped))
					memcpy(pixelConstBufferMapped.pData, &pixelConstantBufferData, sizeof(PSConstantBuffer));
				context.m_mainContext->Unmap(m_psConstantBuffer.Get(), 0);
			}
		}
		m_quadModel.Draw(&context);
	}
}

void SimpleCubeApplication::RenderCube(RenderContext& context)
{
	{
		D3D11_MAPPED_SUBRESOURCE vertexConstBufferMapped = {};
		DXASSERT(context.m_mainContext->Map(m_vsConstantBuffer.Get(), 0, D3D11_MAP::D3D11_MAP_WRITE_DISCARD, 0, &vertexConstBufferMapped))
			XMMATRIX scaleMat = DirectX::XMMatrixScaling(1.0f, 1.0f, 1.0f);
		//translation diffrent from quad 1 just by z to test depth testing(render only based on depth validity)
		XMMATRIX translateMat = DirectX::XMMatrixTranslation(-0.3f, 0.5f, 2.0f);
		m_VertexConstantBufferData.modelMat = scaleMat * translateMat;
		m_VertexConstantBufferData.modelMat = ProcessMatrixForShaderUse(m_VertexConstantBufferData.modelMat);
		m_VertexConstantBufferData.viewMat = m_Maincamera.GetViewMat();
		m_VertexConstantBufferData.viewMat = ProcessMatrixForShaderUse(m_VertexConstantBufferData.viewMat);
		m_VertexConstantBufferData.projMat = m_Maincamera.GetProjectionMat(false);
		m_VertexConstantBufferData.projMat = ProcessMatrixForShaderUse(m_VertexConstantBufferData.projMat);
		memcpy(vertexConstBufferMapped.pData, &m_VertexConstantBufferData, sizeof(VertexConstantBuffer));
		context.m_mainContext->Unmap(m_vsConstantBuffer.Get(), 0);
	}
	{
		PSConstantBuffer pixelConstantBufferData;
		pixelConstantBufferData.colour = { 1.0f,1.0f,1.0f,1.0f };
		D3D11_MAPPED_SUBRESOURCE pixelConstBufferMapped = {};
		DXASSERT(context.m_mainContext->Map(m_psConstantBuffer.Get(), 0, D3D11_MAP::D3D11_MAP_WRITE_DISCARD, 0, &pixelConstBufferMapped))
			memcpy(pixelConstBufferMapped.pData, &pixelConstantBufferData, sizeof(PSConstantBuffer));
		context.m_mainContext->Unmap(m_psConstantBuffer.Get(), 0);
	}
	m_cubeModel.Draw(&context);
}

void SimpleCubeApplication::ProcessWindowProcEvent(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	m_maincameracontroller.ProcessWindowProcEvent(hwnd, uMsg, wParam, lParam);
}

void SimpleCubeApplication::PreRenderUpdate()
{
	m_maincameracontroller.Update();
}