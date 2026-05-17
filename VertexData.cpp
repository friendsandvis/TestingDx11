#include"VertexData.h"
#include<cassert>

void VertexBase::BuildRawVertexBuffer(std::vector<VertexBase*> vertexData, std::vector<float>& outBuffer)
{
	assert(vertexData.size() > 0);
	//make sure type is consistent for each vertex in data passed
	VertexVersion verttype_expected = vertexData[0]->GetVertexType();
	outBuffer.clear();
	for (VertexBase* v : vertexData)
	{
		assert(v->GetVertexType() == verttype_expected);
			switch (verttype_expected)
			{
				case VertexVersion::VERTEXVERSION0:
			{
				VertexV0* vert = static_cast<VertexV0*>(v);
				outBuffer.push_back(vert->m_position.x);
				outBuffer.push_back(vert->m_position.y);
				outBuffer.push_back(vert->m_position.z);
				outBuffer.push_back(vert->m_uv.x);
				outBuffer.push_back(vert->m_uv.y);
				break;
				}
			default:
				break;
			}

	}
}
VertexV0::VertexV0()
{
	m_vertexType = VertexVersion::VERTEXVERSION0;
}
VertexVersionInfo VertexBase::GetVertexVersionInfo(VertexVersion vertVersion)
{
	VertexVersionInfo vertInfo = {};
	switch (vertVersion)
	{
	case VertexVersion::VERTEXVERSION0:
		vertInfo.stride = sizeof(float) * 5;//3f pos, 2f uv
		break;
	}
	return vertInfo;
}