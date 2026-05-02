#pragma once
#include"DX11Common.h"
#include<vector>

enum class VertexType
{
	VertexV0
};
class VertexBase
{
public:
	void setVertexType(VertexType type)
	{
		m_vertexType = type;
	}
	VertexType GetVertexType()
	{
		return m_vertexType;
	}
	static void BuildRawVertexBuffer(std::vector<VertexBase*> vertexData, std::vector<float>& outBuffer);
private:
	VertexType m_vertexType;
};
class VertexV0 : public VertexBase
{
public:
	XMFLOAT3 m_position;
	XMFLOAT2 m_uv;
	void setPosition(float x, float y, float z)
	{
		m_position.x = x;
		m_position.y = y;
		m_position.z = z;
	}
};

