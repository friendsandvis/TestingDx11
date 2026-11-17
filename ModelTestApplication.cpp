#include"ModelTestApplication.h"
#include"BasicModelManager.h"
//only 1 model define to be active at a time
//conference.obj model cannot be submitted need to copy it manually in models directory from web everytime taking a fresh project code setup
//#define USECONFERENCEROOMCOMPOUNDMODEL
//#define USETESTBASICMODELCUBE
#define USESPHONZAMODEL
//#define USEREVOLVERMODEL
//#define USECUBEMODEL


ModelTestApplication::ModelTestApplication()
	:m_planemodel(ModelDataUploadMode::COPY),
	m_cubemodel(ModelDataUploadMode::COPY),
	m_loadedmodel(ModelDataUploadMode::COPY),
	m_trianglemodel(ModelDataUploadMode::COPY),
	m_loadedcompoundmodel(ModelDataUploadMode::COPY)
{
}
ModelTestApplication::~ModelTestApplication()
{

}
void ModelTestApplication::PreRenderUpdate()
{
	m_maincameracontroller.Update();
	DX11ApplicationManagerBase::PreRenderUpdate();
}

void ModelTestApplication::Render(RenderContext context)
{
	//update vertex constants
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
	context.m_mainContext->OMSetRenderTargets(1, m_swapchain.GetBackBufferRTV().GetAddressOf(), m_depthStencilView.Get());
	D3D11_RECT scissorRect = GetScissorRect();
	context.m_mainContext->RSSetScissorRects(1, &scissorRect);
	D3D11_VIEWPORT viewport = GetViewport();
	context.m_mainContext->RSSetViewports(1, &viewport);
	float clearcolour[4] = { 0.0f,1.0f,1.0f,1.0f };
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
	//context.m_mainContext->PSSetConstantBuffers(0, 1, m_psConstantBuffer.GetAddressOf());
	context.m_mainContext->VSSetConstantBuffers(1, 1, m_vsConstantBuffer.GetAddressOf());
	//add rendering logic for model
	m_loadedcompoundmodel.Draw(&context);
	m_swapchain.Present();
}

void ModelTestApplication::InitExtras(ComPtr<ID3D11Device> device)
{
	//camera setup
	{
		DirectX::XMVECTOR camPos = DirectX::XMVectorSet(0.0f, 0.0f, -3.0f, 1.0f);
		DirectX::XMVECTOR targetPos = DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f);
		float nearPlane = 0.01f;
		float farPlane = 100.0f;
		float viewWidth = static_cast<float>(m_swapchain.GetWidth());
		float viewHeight = static_cast<float>(m_swapchain.GetHeight());
		m_Maincamera.Reset(camPos, targetPos, viewWidth, viewHeight, nearPlane, farPlane);
		m_maincameracontroller.SetCameratoControl(&m_Maincamera);
	}

	{
		m_VertexConstantBufferData.viewMat = DirectX::XMMatrixIdentity();
		m_VertexConstantBufferData.projMat = DirectX::XMMatrixIdentity();
		m_VertexConstantBufferData.modelMat = DirectX::XMMatrixIdentity();
		m_VertexConstantBufferData.viewMat = m_Maincamera.GetViewMat();
		m_VertexConstantBufferData.viewMat = ProcessMatrixForShaderUse(m_VertexConstantBufferData.viewMat);
		m_VertexConstantBufferData.projMat = m_Maincamera.GetProjectionMat(false);
		m_VertexConstantBufferData.projMat = ProcessMatrixForShaderUse(m_VertexConstantBufferData.projMat);
		XMMATRIX scaleMat = DirectX::XMMatrixScaling(5.0f, 5.0f, 5.0f);
		m_VertexConstantBufferData.modelMat = scaleMat;
		D3D11_BUFFER_DESC vsConstantBufferDesc = { 0 };
		vsConstantBufferDesc.ByteWidth = sizeof(VertexConstantBuffer);
		vsConstantBufferDesc.Usage = D3D11_USAGE::D3D11_USAGE_DYNAMIC;
		vsConstantBufferDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_CONSTANT_BUFFER;
		vsConstantBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_WRITE;
		vsConstantBufferDesc.MiscFlags = 0;
		vsConstantBufferDesc.StructureByteStride = sizeof(VertexConstantBuffer);
		D3D11_SUBRESOURCE_DATA vsConstantB8ufferSubresData = { 0 };
		vsConstantB8ufferSubresData.pSysMem = &m_VertexConstantBufferData;
		vsConstantB8ufferSubresData.SysMemPitch = 0;
		vsConstantB8ufferSubresData.SysMemSlicePitch = 0;
		DXASSERT(device->CreateBuffer(&vsConstantBufferDesc, &vsConstantB8ufferSubresData, m_vsConstantBuffer.GetAddressOf()))
	}

	BasicModelManager_Old::LoadModel(device, "models/cubes2.dae", m_loadedcompoundmodel, VERTEXVERSION2);
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
		m_quadModel.Init(VertexVersion::VERTEXVERSION0, true);
	}
	//create shaders
	m_simplePixelShader.Init(device, L"shaders/modeltesting/PS.hlsl", ShaderType::PS, "main");
	m_simpleVertexShader.Init(device, L"shaders/modeltesting/VS.hlsl", ShaderType::VS, "main");

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
	//BasicModelManager::LoadModel(device, "models/cube.dae", m_loadedmodel, VERTEXVERSION2);
#ifdef USECONFERENCEROOMCOMPOUNDMODEL
	float scalefactor = 0.01f;
	XMMATRIX scalemat = XMMatrixScalingFromVector(XMVectorSet(scalefactor, scalefactor, scalefactor, 1.0f));
	BasicModelManager::LoadModel(device, "models/conference.obj", m_loadedcompoundmodel, VERTEXVERSION2);
	m_loadedcompoundmodel.Extratransform(scalemat);
#endif // USECONFERENCEROOMCOMPOUNDMODEL
#if defined(USESPHONZAMODEL)
	float scalefactor = 1.0f;
	XMMATRIX scalemat = XMMatrixScalingFromVector(XMVectorSet(scalefactor, scalefactor, scalefactor, 1.0f));
	//BasicModelManager::LoadModel(device, "models/Sponza.gltf", m_loadedcompoundmodel, VERTEXVERSION3, L"textures/modeltextures/sponza/", true);
#endif//defined(USESPHONZAMODEL)
#ifdef USECUBEMODEL
	BasicModelManager::LoadModel(device, "models/cubes2.dae", m_loadedcompoundmodel, VERTEXVERSION2);
#endif // USECUBEMODEL
#if defined(USEREVOLVERMODEL)
	float scalefactor = 0.15f;
	XMMATRIX scalemat = XMMatrixScalingFromVector(XMVectorSet(scalefactor, scalefactor, scalefactor, 1.0f));
	BasicModelManager::LoadModel(device, "models/revolver/scene.gltf", m_loadedcompoundmodel, VERTEXVERSION3, L"textures/modeltextures/revolver/", true);
	//revolver model has albedo as png but it is not expected to be rendered by alphablending.
	m_loadedcompoundmodel.m_supportNonOpaqueMaterial = false;

	m_loadedcompoundmodel.Extratransform(scalemat);
#endif//defined(USEREVOLVERMODEL)






	//BasicModelManager::InitTriangleModel(device, m_trianglemodel);
	//BasicModelManager::InitPlaneModel(device, m_planemodel);
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
	Model::MaterialConstants cubeMaterialConstants = m_cubemodel.GetMaterialConstants();
	cubeMaterialConstants.texsrvidx = 0;//arbatary unused for test cube model.
	m_cubemodel.SetMaterialConstants(cubeMaterialConstants);

}

void ModelTestApplication::ProcessWindowProcEvent(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{

	m_maincameracontroller.ProcessWindowProcEvent(hwnd, uMsg, wParam, lParam);

}