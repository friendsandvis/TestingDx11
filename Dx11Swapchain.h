#pragma once
#include"DX11Common.h"

class DX11Swapchain
{
public:
	ComPtr<ID3D11RenderTargetView> GetBackBufferRTV() { return m_backBufferRtv; }
	void Init(ComPtr<ID3D11Device> device, ComPtr<IDXGIFactory2> factory, unsigned int width, unsigned int height, HWND hwnd);
	UINT GetWidth() { return m_width; }
	UINT GetHeight() { return m_height; }
	void Present();
protected:
	void CreateBackBufferRTV(ComPtr<ID3D11Device> device);

	ComPtr<IDXGISwapChain1> m_swapchain;
	//in dx11 even with flipmodel for swap effect cannot access > 0th buffer
	ComPtr<ID3D11RenderTargetView> m_backBufferRtv;
	UINT m_width;
	UINT m_height;
};
