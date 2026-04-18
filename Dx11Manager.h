#pragma once
#include"Renderable.h"
#include"DX11ApplicationManagerBase.h"

class WindMaker;
class OpenglApplicationManagerBase;
class Dx11Manager : public Renderable
{
public:
	Dx11Manager();
	~Dx11Manager();
	void Init(WindMaker* window, DX11ApplicationManagerBase* appmanager);
	void Render() override;
	void Destroy();
	DX11ApplicationManagerBase* m_appManager;
private:
	WindMaker* m_window;
};