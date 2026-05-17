#pragma once
#include"DX11Common.h"
#include<vector>

enum class VertexVersion
{
	//VertexV0
	UNKNOWN,
	VERTEXVERSION0,
	VERTEXVERSION1,
	VERTEXVERSION2,
	VERTEXVERSION3
};
struct VertexVersionInfo
{
	unsigned int stride;
};
class VertexBase
{
public:
	void setVertexType(VertexVersion type)
	{
		m_vertexType = type;
	}
	VertexVersion GetVertexType()
	{
		return m_vertexType;
	}
	static void BuildRawVertexBuffer(std::vector<VertexBase*> vertexData, std::vector<float>& outBuffer);
	static VertexVersionInfo GetVertexVersionInfo(VertexVersion vertVersion);
	static void BuildInputElementDesc(VertexVersion vertVersion, std::vector<D3D11_INPUT_ELEMENT_DESC>& outInputElementDescs);
protected:
	VertexVersion m_vertexType;
};
class VertexV0 : public VertexBase
{
public:
	XMFLOAT3 m_position;
	XMFLOAT2 m_uv;
	VertexV0();
	void setPosition(float x, float y, float z)
	{
		m_position.x = x;
		m_position.y = y;
		m_position.z = z;
	}
};

