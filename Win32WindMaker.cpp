#include"Win32WindMaker.h"
#include <codecvt>

Win32WindMaker::Win32WindMaker()
	:m_hwnd(NULL)
{

}
Win32WindMaker::~Win32WindMaker()
{}
void Win32WindMaker::CreateWind(unsigned width, unsigned height, std::string windowname)
{
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
	std::wstring windowName_wstr = converter.from_bytes(windowname.c_str());
	m_width = width;
	m_height = height;
	wchar_t CLASS_NAME[] = L" Window Class";
	WNDCLASS wndclass = { 0 };
	wndclass.hInstance = GetModuleHandle(nullptr);
	wndclass.lpszClassName = CLASS_NAME;
	wndclass.lpfnWndProc = ProcManager::WindowProc;
	wndclass.style = CS_OWNDC;
	ATOM atomres = RegisterClass(&wndclass);
	assert(atomres != 0);
	m_hwnd =
		CreateWindowEx(0, CLASS_NAME, windowName_wstr.c_str(), WS_OVERLAPPEDWINDOW, 0, 0, width, height, NULL, NULL, wndclass.hInstance, NULL);
	assert(m_hwnd != NULL);
	ShowWindow(m_hwnd, SW_SHOW);
	RECT clientRect = {0};
	GetClientRect(m_hwnd, &clientRect);
	m_renderableWidth = static_cast<unsigned int>(clientRect.right - clientRect.left);
	m_renderableHeight = static_cast<unsigned int>(clientRect.bottom - clientRect.top);

}
void Win32WindMaker::RunLoop(Renderable* openglManager)
{
	ProcManager::openglManager = openglManager;


	//using hwnd here instead of null causes window created to be in stuck state
	MSG msg = { 0 };
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				bool requestquit = true;
			}
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	







}
void Win32WindMaker::SwapBuffers()
{
}