#include"BasicModelManager.h"

void BasicModelManager::GetTriangleModelVerticies(std::vector<VertexBase*>& outverticies,VertexVersion vertexTypeToBuild)
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

void BasicModelManager::GetQuadModelVerticies(std::vector<VertexBase*>& outverticies, VertexVersion vertexTypeToBuild)
{
	assert(vertexTypeToBuild == VertexVersion::VERTEXVERSION0);
	//0(left-top)
	VertexV0* vert = new VertexV0();
	vert->m_position = { -1.0f, 1.0f, 0.0f };
	vert->m_uv = { 0.0f,1.0f };
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
	//3(right-top)
	vert = new VertexV0();
	vert->m_position = { 1.0f,1.0f,0.0f };
	vert->m_uv = { 1.0f,1.0f };
	outverticies.push_back(vert);
	//4(left-top)
	vert = new VertexV0();
	vert->m_position = { -1.0f, 1.0f, 0.0f };
	vert->m_uv = { 0.0f,1.0f };
	outverticies.push_back(vert);
	//5(right-bottom)
	vert = new VertexV0();
	vert->m_position = { 1.0f,-1.0f,0.0f };
	vert->m_uv = { 1.0f,0.0f };
	outverticies.push_back(vert);
}

void BasicModelManager::GetQuadModelVerticiesIndexed(std::vector<VertexBase*>& outverticies, std::vector<unsigned int>& outindicies, VertexVersion vertexTypeToBuild)
{
	assert(vertexTypeToBuild == VertexVersion::VERTEXVERSION0);
	//0(left-top)
	VertexV0* vert = new VertexV0();
	vert->m_position = { -1.0f, 1.0f, 0.0f };
	vert->m_uv = { 0.0f,1.0f };
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
	//3(right-top)
	vert = new VertexV0();
	vert->m_position = { 1.0f,1.0f,0.0f };
	vert->m_uv = { 1.0f,1.0f };
	outverticies.push_back(vert);
	//set indicies for quad
	outindicies.push_back(0);
	outindicies.push_back(1);
	outindicies.push_back(2);
	outindicies.push_back(3);
	outindicies.push_back(0);
	outindicies.push_back(2);
}
void BasicModelManager::GetCubeModelVerticiesIndexed(std::vector<VertexBase*>& outverticies, std::vector<unsigned int>& outindicies, VertexVersion vertexTypeToBuild)
{
	assert(vertexTypeToBuild == VertexVersion::VERTEXVERSION0);

	//verticies
	//0
	VertexV0* vert = new VertexV0();
	vert->m_position = { -1.0f, -1.0f, -1.0f };
	vert->m_uv = { 0.0,0.0f };
	outverticies.push_back(vert);
	//1
	vert = new VertexV0();
	vert->m_position = { -1.0f,  1.0f, -1.0f };
	vert->m_uv = { 0.0,0.0f };
	outverticies.push_back(vert);
	//2
	vert = new VertexV0();
	vert->m_position = { 1.0f,  1.0f, -1.0f };
	vert->m_uv = { 0.0,0.0f };
	outverticies.push_back(vert);
	//3
	vert = new VertexV0();
	vert->m_position = { 1.0f, -1.0f, -1.0f };
	vert->m_uv = { 0.0,0.0f };
	outverticies.push_back(vert);
	//4
	vert = new VertexV0();
	vert->m_position = { -1.0f,-1.0f, 1.0f };
	vert->m_uv = { 0.0,0.0f };
	outverticies.push_back(vert);
	//5
	vert = new VertexV0();
	vert->m_position = { -1.0f, 1.0f, 1.0f };
	vert->m_uv = { 0.0,0.0f };
	outverticies.push_back(vert);
	//6
	vert = new VertexV0();
	vert->m_position = { 1.0f, 1.0f, 1.0f };
	vert->m_uv = { 0.0,0.0f };
	outverticies.push_back(vert);
	//7
	vert = new VertexV0();
	vert->m_position = { 1.0f,-1.0f, 1.0f };
	vert->m_uv = { 0.0,0.0f };
	outverticies.push_back(vert);

	//indicies
	std::vector<unsigned>cubeindicies =
	{
		0, 1, 2, 0, 2, 3,
		4, 6, 5, 4, 7, 6,
		4, 5, 1, 4, 1, 0,
		3, 2, 6, 3, 6, 7,
		1, 5, 6, 1, 6, 2,
		4, 0, 3, 4, 3, 7
	};
	outindicies = cubeindicies;
}