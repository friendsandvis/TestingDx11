#include "Dx11Manager.h"
#include"Win32WindMaker.h"
#pragma comment(lib,"d3d11.lib")
#pragma comment(lib,"dxgi.lib")
//used for selecting hardware adaptor
//currently set to nvidia
#define HARDWAREVENDORID 4318

#define USEDEBUGLAYER
Dx11Manager::Dx11Manager()
	:m_appManager(nullptr),
	m_window(nullptr)
{
	//enum adapters and select NVIDIA hardware adapter by vendor ID
	DXASSERT(CreateDXGIFactory2(0,IID_PPV_ARGS(m_dxgiFactory.GetAddressOf())))
		//enum adapters
		EnumAdapters();
	//select correct adapter
	SelectAdapter();
	
}
Dx11Manager::~Dx11Manager()
{
}
void Dx11Manager::Init(WindMaker* window, DX11ApplicationManagerBase* appmanager)
{
	m_window = window;
	//make context and device
	UINT deviceFlags = 0;
	deviceFlags |= D3D11_CREATE_DEVICE_FLAG::D3D11_CREATE_DEVICE_BGRA_SUPPORT;
#ifdef USEDEBUGLAYER
	deviceFlags |= D3D11_CREATE_DEVICE_FLAG::D3D11_CREATE_DEVICE_DEBUG;
#endif //USEDEBUGLAYER
	D3D_FEATURE_LEVEL dx11FeatureLevels_requested[] =
	{
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0
	};
	D3D_FEATURE_LEVEL dx11FeatureLevel_received;
	DXASSERT(D3D11CreateDevice(m_alladapters[m_selectedAdapterIdx].Get(),D3D_DRIVER_TYPE::D3D_DRIVER_TYPE_UNKNOWN, 0, deviceFlags, dx11FeatureLevels_requested, ARRAYSIZE(dx11FeatureLevels_requested), D3D11_SDK_VERSION,m_mainDevice.GetAddressOf(), &dx11FeatureLevel_received, m_mainDeviceContext.GetAddressOf()))
	m_appManager = appmanager;
	if(m_appManager != nullptr)
	m_appManager->Init(m_mainDevice,m_dxgiFactory,m_window);
}

void Dx11Manager::Render()
{
	RenderContext renderContext = {};
	renderContext.m_mainDevice = m_mainDevice;
	renderContext.m_mainContext = m_mainDeviceContext;
	if (m_appManager)
	{
		m_appManager->PreRenderUpdate();
		m_appManager->Render(renderContext);
		m_appManager->PostRenderUpdate();
	}
}

void Dx11Manager::Destroy()
{
	if (m_appManager)
	{
		m_appManager->Destroy();
	}
}

void Dx11Manager::EnumAdapters()
{
	UINT adapterindex = 0;
	ComPtr<IDXGIAdapter1> anadapter;
	while (m_dxgiFactory->EnumAdapters1(adapterindex, anadapter.GetAddressOf()) == S_OK)
	{
		m_alladapters.push_back(anadapter);
		adapterindex++;
	}
}

void Dx11Manager::SelectAdapter()
{
	m_selectedAdapterIdx = 0;
	for (; m_selectedAdapterIdx < m_alladapters.size(); m_selectedAdapterIdx++)
	{
		ComPtr<IDXGIAdapter1> anadapter = m_alladapters[m_selectedAdapterIdx];
		DXGI_ADAPTER_DESC1 adapterdesc;
		anadapter->GetDesc1(&adapterdesc);
		if (adapterdesc.VendorId == HARDWAREVENDORID)
		{
			break;
		}
	}
}