#include "Dx11Manager.h"
#include"Win32WindMaker.h"
Dx11Manager::Dx11Manager()
	:m_appManager(nullptr),
	m_window(nullptr)
{

}
Dx11Manager::~Dx11Manager()
{

}
void Dx11Manager::Init(WindMaker* window, DX11ApplicationManagerBase* appmanager)
{
	m_window = window;
	m_appManager = appmanager;
	Win32WindMaker* win32Window = dynamic_cast<Win32WindMaker*>(m_window);
	if(m_appManager != nullptr)
	m_appManager->Init(window);
}

void Dx11Manager::Render()
{
	if (m_appManager)
	{
		m_appManager->PreRenderUpdate();
		m_appManager->Render();
		m_appManager->PostRenderUpdate();
	}
}

void Dx11Manager::Destroy()
{
	if (m_appManager)
	{
		m_appManager->Destroy();
	}
}