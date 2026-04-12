#pragma once
#include<string>
#include"Renderable.h"
#include"WindowProcHook.h"

class ProcManager
{
public:

	static WindowProcHook* s_prochook;
	static Renderable* openglManager;
	inline static void SetProcHook(WindowProcHook* ahook) { s_prochook = ahook; }
	static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
};

class WindMaker
{
public:
	WindMaker();
	~WindMaker();
	virtual void CreateWind(unsigned width, unsigned height, std::string windowname) = 0;
	virtual void RunLoop(Renderable* openglManager) = 0;
	unsigned int GetWidth() { return m_width; }
	unsigned int GetHeight() { return m_height; }
	unsigned int GetRenderableWidth() { return m_renderableWidth; }
	unsigned int GetRenderableHeight() { return m_renderableHeight; }
protected:
	unsigned int m_width;
	unsigned int m_height;
	unsigned int m_renderableWidth;
	unsigned int m_renderableHeight;
	

};
