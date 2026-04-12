#pragma once
#include"windmaker.h"
#include<cassert>
#include"WindowProcHook.h"


class Renderable;
class Win32WindMaker : public WindMaker
{
public:
	Win32WindMaker();
	~Win32WindMaker();
	void CreateWind(unsigned width, unsigned height, std::string windowname) override;
	void RunLoop(Renderable* openglManager) override;
	void SwapBuffers();
	inline HWND Gethwnd() { return m_hwnd; }
private:
	HWND m_hwnd;

};