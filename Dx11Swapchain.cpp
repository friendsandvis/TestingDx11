#include"Dx11Swapchain.h"

void DX11Swapchain::Init(ComPtr<ID3D11Device> device, ComPtr<IDXGIFactory2> factory, unsigned int width, unsigned int height, HWND hwnd)
{
	
	DXGI_SWAP_CHAIN_DESC1 swapchainDesc = {};
	swapchainDesc.BufferCount = BACKBUFFER_COUNT;
	swapchainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_TEARING;
	swapchainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapchainDesc.Width = 0;
	swapchainDesc.Height = 0;
	swapchainDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	swapchainDesc.SampleDesc.Count = 1;
	swapchainDesc.SampleDesc.Quality = 0;
	swapchainDesc.SwapEffect = DXGI_SWAP_EFFECT::DXGI_SWAP_EFFECT_FLIP_DISCARD;
	swapchainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_FRAME_LATENCY_WAITABLE_OBJECT;
	swapchainDesc.Scaling = DXGI_SCALING_STRETCH;
	DXASSERT(factory->CreateSwapChainForHwnd(device.Get(), hwnd, &swapchainDesc, nullptr, nullptr, m_swapchain.GetAddressOf()))
	{
		DXGI_SWAP_CHAIN_DESC1 swapchainDesc_retrived = {};
		m_swapchain->GetDesc1(&swapchainDesc_retrived);
		m_width = swapchainDesc_retrived.Width;
		m_height = swapchainDesc_retrived.Height;
	}
		CreateBackBufferRTV(device);
}

void DX11Swapchain::CreateBackBufferRTV(ComPtr<ID3D11Device> device)
{
	//in dx11 even with flipmodel for swap effect cannot access > 0th buffer
		ComPtr<ID3D11Texture2D> backbuffer;
		DXASSERT(m_swapchain->GetBuffer(0, IID_PPV_ARGS(backbuffer.GetAddressOf())))
			DXASSERT(device.Get()->CreateRenderTargetView(backbuffer.Get(),nullptr, m_backBufferRtv.GetAddressOf()))

}
void DX11Swapchain::Present()
{
	DXASSERT(m_swapchain->Present(0, 0))
}