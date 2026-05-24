#pragma once
#include"DX11ApplicationManagerBase.h"
#include<vector>
#include"Dx11Buffer.h"
#include"VertexData.h"
#include"DX11Shader.h"
#include"Model.h"


class SimpleTriangleApplication : public DX11ApplicationManagerBase
{
public:
	void Render(RenderContext context) override;
	void InitExtras(ComPtr<ID3D11Device> device) override;

private:
	struct TestConstantBuffer
	{
		DirectX::XMFLOAT4 colour;
	};
	Model m_triangleModel;
	DX11Shader m_simpleVertexShader;
	DX11Shader m_simplePixelShader;
	ComPtr<ID3D11RasterizerState> m_rasterState;
	ComPtr<ID3D11InputLayout> m_inputLayout;
	ComPtr<ID3D11BlendState> m_blendState;
	ComPtr<ID3D11Buffer> m_testConstantBuffer;

};