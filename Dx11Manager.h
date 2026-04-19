#pragma once
#include"Renderable.h"
#include"DX11Common.h"
#include"DX11ApplicationManagerBase.h"
#include<vector>

using namespace std;

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
	ComPtr<IDXGIFactory2> m_dxgiFactory;
	vector<ComPtr<IDXGIAdapter1>> m_alladapters;
	UINT m_selectedAdapterIdx;
	ComPtr<ID3D11Device> m_mainDevice;
	ComPtr<ID3D11DeviceContext> m_mainDeviceContext;

	void EnumAdapters();
	void SelectAdapter();
};