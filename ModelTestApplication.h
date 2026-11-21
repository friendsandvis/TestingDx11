#pragma once
#include"DXUtils.h"
#include"DX11ApplicationManagerBase.h"
#include"AssetManager.h"
#include"DXCamera.h"
#include"CameraMovementManager.h"
#include"DX11Shader.h"
#include "Model.h"
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
	SimpleDXModel m_quadModel;
	SimpleDXModel m_cubeModel;
	CompoundModel m_loadedcompoundmodel;
	DXCamera m_Maincamera;
	DXFPSCameraController m_maincameracontroller;
	ComPtr<ID3D11InputLayout> m_inputLayout;
	ComPtr<ID3D11DepthStencilView> m_depthStencilView;
	DX11Shader m_simpleVertexShader;
	DX11Shader m_simplePixelShader;
	ComPtr<ID3D11RasterizerState> m_rasterState;
	ComPtr<ID3D11BlendState> m_blendState;
	ComPtr<ID3D11DepthStencilState> m_depthStencilState;
	ComPtr<ID3D11Texture2D> m_depthStencilTex;
	SHADERTRANSFORMCONSTANTSSTRUCT m_TransformConstantBufferData;
	ComPtr<ID3D11Buffer> m_transformConstantBuffer;
	ComPtr<ID3D11SamplerState> m_LinerSamplerState;
};