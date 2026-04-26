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
	m_swapchain.Init(device, factory, width, height, hwnd);
	
}
D3D11_VIEWPORT DX11ApplicationManagerBase::GetViewport()
{
	D3D11_VIEWPORT viewPort = {};
	viewPort.TopLeftX = 0;
	viewPort.TopLeftY = 0;
	viewPort.Width = static_cast<FLOAT>(m_swapchain.GetWidth());
	viewPort.Height = static_cast<FLOAT>(m_swapchain.GetHeight());
	return viewPort;
}
D3D11_RECT DX11ApplicationManagerBase::GetScissorRect()
{
	D3D11_RECT rect;
	rect.left = 0;
	rect.top = 0;
	rect.right = m_swapchain.GetWidth();
	rect.bottom = m_swapchain.GetHeight();
	return rect;
}