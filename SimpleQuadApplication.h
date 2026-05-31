#pragma once
#include"DX11ApplicationManagerBase.h"
#include<vector>
#include"Dx11Buffer.h"
#include"VertexData.h"
#include"DX11Shader.h"
#include"Model.h"


class SimpleQuadApplication : public DX11ApplicationManagerBase
{
public:
	void Render(RenderContext context) override;
	void InitExtras(ComPtr<ID3D11Device> device) override;

private:
	struct PSConstantBuffer
	{
		DirectX::XMFLOAT4 colour;
	};
	struct VertexConstantBuffer
	{
		DirectX::XMMATRIX viewMat;
		DirectX::XMMATRIX projMat;
		DirectX::XMMATRIX modelMat;
	};
	Model m_quadModel;
	DX11Shader m_simpleVertexShader;
	DX11Shader m_simplePixelShader;
	ComPtr<ID3D11RasterizerState> m_rasterState;
	ComPtr<ID3D11InputLayout> m_inputLayout;
	ComPtr<ID3D11BlendState> m_blendState;
	ComPtr<ID3D11Buffer> m_psConstantBuffer;
	ComPtr<ID3D11Buffer> m_vsConstantBuffer;
	VertexConstantBuffer m_VertexConstantBufferData;
	ComPtr<ID3D11Texture2D> m_depthStencilTex;
	ComPtr<ID3D11DepthStencilView> m_depthStencilView;
	ComPtr<ID3D11DepthStencilState> m_depthStencilState;

};