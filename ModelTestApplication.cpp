#include"ModelTestApplication.h"
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
	//m_primarycmdlist.Reset(false, true, m_frameIdx);
	bool uploadModelTextureData = false;
#if defined(USESPHONZAMODEL) || defined(USEREVOLVERMODEL)
	uploadModelTextureData = true;
#endif //defined(USESPHONZAMODEL) || defined(USEREVOLVERMODEL)



	//upload compoundmodel textures over frames or all at once
	const bool loadModelTextureDataOverFrames = false;
	if (uploadModelTextureData)
	{
			//need to do anything?
	}
	//XMMATRIX mvp = m_maincamera.GetMVP();
	/*XMMATRIX orthoproj = XMMatrixOrthographicLH(2.0f, 2.0f, -1.0f, 1.0f);
	XMMATRIX model = XMMatrixIdentity();
	XMMATRIX mvp = XMMatrixMultiply(model, orthoproj);
	XMMATRIX vpmat = m_maincamera.GetVP();
	//m_trianglemodel.Draw(m_primarycmdlist,vpmat);*/
	//a specialized way to test out model's material(diffuse textures) 
	if (m_loadedcompoundmodel.SupportMaterial())
	{
		/*DX12DESCHEAP& loadedcompoundmodelmatsrvheap = m_loadedcompoundmodel.GetResourceviewHeap();
		ID3D12DescriptorHeap* heapstoset[1] = { loadedcompoundmodelmatsrvheap.GetDescHeap() };
		m_primarycmdlist->SetDescriptorHeaps(1, heapstoset);
		m_primarycmdlist->SetGraphicsRootDescriptorTable(1, loadedcompoundmodelmatsrvheap.GetGPUHandleOffseted(0));*/
	}
#ifdef USETESTBASICMODELCUBE
	{
		//m_cubemodel.Draw(m_primarycmdlist, vpmat, 0, 2, true, true, true);
		m_primarycmdlist->SetGraphicsRootConstantBufferView(0, m_CamConstBuffer.GetResource()->GetGPUVirtualAddress());
		m_loadedmodel.Draw(m_primarycmdlist, m_maincamera.GetMatData(), m_CamConstBuffer, 2, true, true);
	}
	DXASSERT(m_primarycmdlist->Close())
		BasicRender();
	return;
#endif
	//we draw opaque non opaque with diffrent [pso only if compound model supports nonopaque otherwise all rendered by default pso.
	//constant buffer view set before draw function called from outside not inside the draw function.
	/*if (m_loadedcompoundmodel.SupportNonOpaqueMaterial())
	{
		//draw opaque models only with opaque pso and switch to alpha blending pso to render non opaque data
		//constant buffer set as root CBV before drawing and the buffer itself is updated inside draw
		m_primarycmdlist->SetGraphicsRootConstantBufferView(0, m_CamConstBuffer.GetResource()->GetGPUVirtualAddress());
		m_loadedcompoundmodel.Draw(m_primarycmdlist, m_maincamera.GetMatData(), m_CamConstBuffer, 2, true, false);
		m_primarycmdlist->SetPipelineState(m_pso_alphablending.GetPSO());
		m_primarycmdlist->SetGraphicsRootSignature(m_pso_alphablending.GetRootSignature());
		m_loadedcompoundmodel.Draw(m_primarycmdlist, m_maincamera.GetMatData(), m_CamConstBuffer, 2, false, true);
	}
	else
	{
		//m_loadedcompoundmodel.Draw(m_primarycmdlist, vpmat, 0, 2, true, true);//old way unsupported by shader.
		m_primarycmdlist->SetGraphicsRootConstantBufferView(0, m_CamConstBuffer.GetResource()->GetGPUVirtualAddress());
		m_loadedcompoundmodel.Draw(m_primarycmdlist, m_maincamera.GetMatData(), m_CamConstBuffer, 2, true, true);
	}

	DXASSERT(m_primarycmdlist->Close())*/
	//add rendering logic for model
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
	BasicModelManager::InitCamConstBuffer(device, m_CamConstBuffer);
	BasicModelManager::LoadModel(device, "models/cube.dae", m_loadedmodel, VERTEXVERSION2);
#ifdef USECONFERENCEROOMCOMPOUNDMODEL
	float scalefactor = 0.01f;
	XMMATRIX scalemat = XMMatrixScalingFromVector(XMVectorSet(scalefactor, scalefactor, scalefactor, 1.0f));
	BasicModelManager::LoadModel(device, "models/conference.obj", m_loadedcompoundmodel, VERTEXVERSION2);
	m_loadedcompoundmodel.Extratransform(scalemat);
#endif // USECONFERENCEROOMCOMPOUNDMODEL


#if defined(USESPHONZAMODEL)
	float scalefactor = 1.0f;
	XMMATRIX scalemat = XMMatrixScalingFromVector(XMVectorSet(scalefactor, scalefactor, scalefactor, 1.0f));
	BasicModelManager::LoadModel(device, "models/Sponza.gltf", m_loadedcompoundmodel, VERTEXVERSION3, L"textures/modeltextures/sponza/", true);
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






	BasicModelManager::InitTriangleModel(device, m_trianglemodel);
	BasicModelManager::InitPlaneModel(device, m_planemodel);
	BasicModelManager::InitCubeModel(device, m_cubemodel, VertexVersion::VERTEXVERSION3);
	Model::MaterialConstants cubeMaterialConstants = m_cubemodel.GetMaterialConstants();
	cubeMaterialConstants.texsrvidx = 0;//arbatary unused for test cube model.
	m_cubemodel.SetMaterialConstants(cubeMaterialConstants);

	m_planemodel.UploadModelDatatoBuffers();
	m_cubemodel.UploadModelDatatoBuffers();
	m_loadedmodel.UploadModelDatatoBuffers();
	m_loadedcompoundmodel.UploadModelDatatoBuffers();
}

void ModelTestApplication::ProcessWindowProcEvent(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{

	m_maincameracontroller.ProcessWindowProcEvent(hwnd, uMsg, wParam, lParam);

}