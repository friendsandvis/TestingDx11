#include"DX11ApplicationManagerBase.h"
#include"windmaker.h"
#include"Win32WindMaker.h"

DX11ApplicationManagerBase::DX11ApplicationManagerBase()
{
	m_imguiAllowed = false;
}
DX11ApplicationManagerBase::~DX11ApplicationManagerBase()
{

}

void DX11ApplicationManagerBase::Init(ComPtr<ID3D11Device> device, ComPtr<IDXGIFactory2> factory, WindMaker* window)
{
	//swapchain init
	Win32WindMaker* win32Window = dynamic_cast<Win32WindMaker*>(window);
	assert(win32Window != nullptr);
	InitSwapchain(device,factory,window->GetWidth(), window->GetHeight(),win32Window->GetHWND());
	InitBase(device,window);
	InitExtras();
}

void DX11ApplicationManagerBase::RenderBase()
{
}

void DX11ApplicationManagerBase::ClearBackBuffer(float clearcolour[4], bool ClearDepth)
{
	//to do
}

void DX11ApplicationManagerBase::InitBase(ComPtr<ID3D11Device> device, WindMaker* window)
{
	
}
void DX11ApplicationManagerBase::InitSwapchain(ComPtr<ID3D11Device> device,ComPtr<IDXGIFactory2> factory, unsigned width, unsigned height, HWND hwnd)
{
	DXGI_SWAP_CHAIN_DESC swapchainDesc = {};
	swapchainDesc.Windowed = TRUE;
	swapchainDesc.OutputWindow = hwnd;
	swapchainDesc.BufferCount = BACKBUFFER_COUNT;
	swapchainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapchainDesc.BufferDesc.Width = width;
	swapchainDesc.BufferDesc.Height = height;
	swapchainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapchainDesc.SampleDesc.Count = 1;
	swapchainDesc.SampleDesc.Quality = 0;
	DXASSERT(factory->CreateSwapChain(device.Get(), &swapchainDesc,m_swapchain.GetAddressOf()))
	
}
