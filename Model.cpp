#include"Model.h"
#include"Dx11RenderContext.h"
void SimpleDXModel::SetVertexData(std::vector<VertexBase*>& verticies, bool buildRawVertexData)
{
	m_verticies = verticies;
	//make sure each vertex is of expected type
	for (VertexBase* vert : m_verticies)
	{
		assert(vert->GetVertexType() == m_vertexVersion);
	}
	if (buildRawVertexData)
	{
		DXVertexManager::BuildRawVertexBuffer(m_verticies, m_verticiesDataRaw);
	}
}

void SimpleDXModel::SetIndexData(std::vector<unsigned int>& indicies)
{
	assert(m_HasIndicies);
	m_indicies = indicies;
}
void SimpleDXModel::Init(VertexVersion expectedvertVersion, bool hasIndicies)
{
	m_HasIndicies = hasIndicies;
	m_vertexVersion = expectedvertVersion;
}
void SimpleDXModel::CreateVertexBuffer(ComPtr<ID3D11Device> device)
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

void SimpleDXModel::CreateIndexBuffer(ComPtr<ID3D11Device> device)
{
	assert(m_indicies.size() > 0);
	D3D11_BUFFER_DESC indexBufferDesc = {};
	indexBufferDesc.ByteWidth = sizeof(m_indicies[0]) * m_indicies.size();
	indexBufferDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.Usage = D3D11_USAGE::D3D11_USAGE_IMMUTABLE;
	D3D11_SUBRESOURCE_DATA indexBufferInitData = {};
	indexBufferInitData.pSysMem = reinterpret_cast<void*>(m_indicies.data());
	indexBufferInitData.SysMemPitch = 0;
	indexBufferInitData.SysMemSlicePitch = 0;
	m_indexBuffer.Init(device, indexBufferDesc, indexBufferInitData);
}
void SimpleDXModel::BuildInputElementDesc(std::vector<D3D11_INPUT_ELEMENT_DESC>& outInputElementDescs)
{
	DXVertexManager::BuildInputElementDesc(m_vertexVersion, outInputElementDescs);
}

unsigned int SimpleDXModel::GetIndiciesCount()
{
	if (m_HasIndicies)
	{
		return m_indicies.size();
	}
	return 0;
}

void SimpleDXModel::Draw(RenderContext* context)
{
	if (context == nullptr)
	{
		return;
	}
	//setup vertex index buffer and layout
	VertexVersionInfo vertInfo = DXVertexManager::GetVertexVersionInfo(m_vertexVersion);
	UINT v_stride = vertInfo.stride;
	UINT v_offset = 0;
	context->m_mainContext->IASetVertexBuffers(0, 1, GetVertexBuffer().GetDXBuffer().GetAddressOf(), &v_stride, &v_offset);
	if (HasIndicies())
	{
		context->m_mainContext->IASetIndexBuffer(GetIndexBuffer().GetDXBuffer().Get(), DXGI_FORMAT_R32_UINT, 0);
	}
	
	if (HasIndicies())
	{
		context->m_mainContext->DrawIndexed(GetIndiciesCount(), 0, 0);
	}
	else
	{
		context->m_mainContext->Draw(GetVertexCount(), 0);
	}
}