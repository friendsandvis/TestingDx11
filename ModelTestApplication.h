#pragma once
#include"DXUtils.h"
#include"DX11ApplicationManagerBase.h"
#include"AssetManager.h"
#include"DXCamera.h"
#include"CameraMovementManager.h"
using namespace DirectX;
class ModelTestApplication :public DX11ApplicationManagerBase
{
public:
	ModelTestApplication();
	~ModelTestApplication();
	void PreRenderUpdate()override;
	void Render(RenderContext context)override;
	void ProcessWindowProcEvent(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)override;

protected:
	void InitExtras(ComPtr<ID3D11Device> device) override;

private:
	struct GeneralConstants
	{
		unsigned int usematerialtextures;
	};
	Model m_planemodel, m_trianglemodel;
	Model m_cubemodel;
	Model m_loadedmodel;
	CompoundModel m_loadedcompoundmodel;
	DXCamera m_Maincamera;
	DXFPSCameraController m_maincameracontroller;
	DX11Buffer m_CamConstBuffer;
};