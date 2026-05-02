#pragma once
#include"DX11ApplicationManagerBase.h"
#include<vector>
#include"Dx11Buffer.h"
#include"VertexData.h"


class SimpleTriangleApplication : public DX11ApplicationManagerBase
{
public:
	void Render(RenderContext context) override;
	void InitExtras(ComPtr<ID3D11Device> device) override;

private:
	void GetTriangleVertices(std::vector<VertexBase*>& outverticies);
	DX11Buffer m_triangle_vertexBuffer;
};