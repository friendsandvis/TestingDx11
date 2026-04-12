#include"windmaker.h"

WindowProcHook* ProcManager::s_prochook = nullptr;
Renderable* ProcManager::openglManager = nullptr;
WindMaker::WindMaker()
	:m_width(0),
	m_height(0),
	m_renderableWidth(0),
	m_renderableHeight(0)
{

}
WindMaker::~WindMaker()
{
}

LRESULT CALLBACK ProcManager::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (s_prochook != nullptr)
	{
		s_prochook->ProcessWindowProcEvent(hwnd, uMsg, wParam, lParam);
	}
	switch (uMsg)
	{
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		return 0;
	}
	case WM_PAINT:
	{
		//draw here
		if (openglManager)
		{
			openglManager->Render();
		}
		return 0;
	}
	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);

	}

	return 0;

}