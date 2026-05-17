#include"BasicModelManager.h"

void BasicModelManager::GetTriangleModelVerticies_NDC(std::vector<VertexBase*>& outverticies,VertexVersion vertexTypeToBuild)
{
	assert(vertexTypeToBuild == VertexVersion::VERTEXVERSION0);
	//0(center-top)
	VertexV0* vert = new VertexV0();
	vert->m_position = { 0.0f, 1.0f, 0.0f };
	vert->m_uv = { 0.5f,1.0f };
	outverticies.push_back(vert);
	//1(left-bottom)
	vert = new VertexV0();
	vert->m_position = { -1.0f,-1.0f,0.0f };
	vert->m_uv = { 0.0f,0.0f };
	outverticies.push_back(vert);
	//2(right-bottom)
	vert = new VertexV0();
	vert->m_position = { 1.0f,-1.0f,0.0f };
	vert->m_uv = { 1.0f,0.0f };
	outverticies.push_back(vert);
}