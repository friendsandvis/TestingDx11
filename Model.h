#pragma once
#include<vector>
#include"VertexData.h"
#include"Dx11Buffer.h"

class Model
{
public:
	void Init(VertexVersion expectedvertVersion, bool hasIndicies = false);
	void SetVertexData(std::vector<VertexBase*>& verticies,bool buildRawVertexData = true);
	void SetIndexData(std::vector<unsigned int>& indicies);
	void CreateVertexBuffer(ComPtr<ID3D11Device> device);
	void CreateIndexBuffer(ComPtr<ID3D11Device> device);
	unsigned int GetVertexCount() { return static_cast<unsigned int>(m_verticies.size()); }
	unsigned int GetIndiciesCount();
	std::vector<float>& GetVerticiesRawData() { return m_verticiesDataRaw; }
	std::vector<unsigned int>& GetIndicies() { return m_indicies; }
	DX11Buffer& GetVertexBuffer() { return m_vertexBuffer; }
	DX11Buffer& GetIndexBuffer() { return m_indexBuffer; }
	void BuildInputElementDesc(std::vector<D3D11_INPUT_ELEMENT_DESC>& outInputElementDescs);
	bool HasIndicies() { return m_HasIndicies; }
protected:
	std::vector<VertexBase*> m_verticies;
	std::vector<unsigned int> m_indicies;
	std::vector<float> m_verticiesDataRaw;
	VertexVersion m_vertexVersion;
	DX11Buffer m_vertexBuffer;
	DX11Buffer m_indexBuffer;
	bool m_HasIndicies;
};