#pragma once
#include"WindowProcHook.h"
#include"windmaker.h"
#include"DX11Common.h"
#include"Dx11Swapchain.h"
#include"Dx11RenderContext.h"
class DX11ApplicationManagerBase : public WindowProcHook
{
public:
	void Init(ComPtr<ID3D11Device> device, ComPtr<IDXGIFactory2> factory,WindMaker* window);
	virtual void InitBase(ComPtr<ID3D11Device> device,WindMaker* window);
	//returns the default viewport based on the current swapchain properties
	D3D11_VIEWPORT GetViewport();
	//returns the default scissor rect based on the current swapchain properties
	D3D11_RECT GetScissorRect();
	//basic necessary initialization of 
	virtual void Render(RenderContext context) = 0;
	virtual void PreRenderUpdate() {}
	virtual void PostRenderUpdate() {}
	virtual void Destroy() {}
	virtual void IMGUIRenderAdditional() {}
	inline bool IsIMGUIAllowed()
	{
		return m_imguiAllowed;
	}
	void InitSwapchain(ComPtr<ID3D11Device> device, ComPtr<IDXGIFactory2> factory, unsigned width, unsigned height, HWND hwnd);
	void RenderBase();
	void ClearBackBuffer(float clearcolour[4], bool ClearDepth = true);
	DX11ApplicationManagerBase();
	virtual ~DX11ApplicationManagerBase();

protected:
	//a camera object representing the main camera for a basic application

	virtual void InitExtras() {}
	//imgui related
	bool m_imguiAllowed;
	DX11Swapchain m_swapchain;
};
