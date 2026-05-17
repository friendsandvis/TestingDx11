#pragma once
#include<vector>
#include"VertexData.h"
#include"Dx11Buffer.h"

class Model
{
public:
	void Init(VertexVersion expectedvertVersion);
	void SetVertexData(std::vector<VertexBase*>& verticies,bool buildRawVertexData = true);
	void CreateVertexBuffer(ComPtr<ID3D11Device> device);
	unsigned int GetVertexCount() { return static_cast<unsigned int>(m_verticies.size()); }
	std::vector<float>& GetVerticiesRawData() { return m_verticiesDataRaw; }
	DX11Buffer& GetVertexBuffer() { return m_vertexBuffer; }
	void BuildInputElementDesc(std::vector<D3D11_INPUT_ELEMENT_DESC>& outInputElementDescs);
protected:
	std::vector<VertexBase*> m_verticies;
	std::vector<float> m_verticiesDataRaw;
	VertexVersion m_vertexVersion;
	DX11Buffer m_vertexBuffer;
};