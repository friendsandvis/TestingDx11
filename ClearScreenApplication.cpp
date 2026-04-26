#include"ClearScreenApplication.h"

void ClearScreenApplication::Render(RenderContext context)
{
	context.m_mainContext->OMSetRenderTargets(1, m_swapchain.GetBackBufferRTV().GetAddressOf(),nullptr);
	D3D11_RECT scissorRect = GetScissorRect();
	context.m_mainContext->RSSetScissorRects(1, &scissorRect);
	D3D11_VIEWPORT viewport = GetViewport();
	context.m_mainContext->RSSetViewports(1, &viewport);
	float clearcolour[4] = { 0.0f,0.0f,1.0f,1.0f };
	context.m_mainContext->ClearRenderTargetView(m_swapchain.GetBackBufferRTV().Get(), clearcolour);
	m_swapchain.Present();
}