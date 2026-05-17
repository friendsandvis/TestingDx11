#include"Model.h"

void Model::SetVertexData(std::vector<VertexBase*>& verticies, bool buildRawVertexData)
{
	m_verticies = verticies;
	//make sure each vertex is of expected type
	for (VertexBase* vert : m_verticies)
	{
		assert(vert->GetVertexType() == m_vertexVersion);
	}
	if (buildRawVertexData)
	{
		VertexBase::BuildRawVertexBuffer(m_verticies, m_verticiesDataRaw);
	}
}
void Model::Init(VertexVersion expectedvertVersion)
{
	m_vertexVersion = expectedvertVersion;
}
void Model::CreateVertexBuffer(ComPtr<ID3D11Device> device)
{
	assert(m_verticiesDataRaw.size() > 0);
	D3D11_BUFFER_DESC vertexBufferDesc = {};
	vertexBufferDesc.ByteWidth = sizeof(m_verticiesDataRaw[0]) * m_verticiesDataRaw.size();
	vertexBufferDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.Usage = D3D11_USAGE::D3D11_USAGE_IMMUTABLE;
	D3D11_SUBRESOURCE_DATA vertexBufferInitData = {};
	vertexBufferInitData.pSysMem = reinterpret_cast<void*>(m_verticiesDataRaw.data());
	vertexBufferInitData.SysMemPitch = 0;
	vertexBufferInitData.SysMemSlicePitch = 0;
	m_vertexBuffer.Init(device, vertexBufferDesc, vertexBufferInitData);
}
void Model::BuildInputElementDesc(std::vector<D3D11_INPUT_ELEMENT_DESC>& outInputElementDescs)
{
	VertexBase::BuildInputElementDesc(m_vertexVersion, outInputElementDescs);
}