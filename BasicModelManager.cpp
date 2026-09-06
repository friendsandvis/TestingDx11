#include"BasicModelManager.h"
struct PosUVVertex
{
	XMFLOAT3 pos;
	XMFLOAT2 uv;
};
PosUVVertex cubeverticies[]=
{
	// Front Face (Z = -0.5)
	{ {-0.5f,  0.5f, -0.5f}, {0.0f, 0.0f} }, // Top-Left
	{ { 0.5f,  0.5f, -0.5f}, {1.0f, 0.0f} }, // Top-Right
	{ { 0.5f, -0.5f, -0.5f}, {1.0f, 1.0f} }, // Bottom-Right
	{ {-0.5f, -0.5f, -0.5f}, {0.0f, 1.0f} }, // Bottom-Left

	// Back Face (Z = 0.5)
	{ { 0.5f,  0.5f,  0.5f}, {0.0f, 0.0f} }, // Top-Left
	{ {-0.5f,  0.5f,  0.5f}, {1.0f, 0.0f} }, // Top-Right
	{ {-0.5f, -0.5f,  0.5f}, {1.0f, 1.0f} }, // Bottom-Right
	{ { 0.5f, -0.5f,  0.5f}, {0.0f, 1.0f} }, // Bottom-Left

	// Top Face (Y = 0.5)
	{ {-0.5f,  0.5f,  0.5f}, {0.0f, 0.0f} }, // Top-Left
	{ { 0.5f,  0.5f,  0.5f}, {1.0f, 0.0f} }, // Top-Right
	{ { 0.5f,  0.5f, -0.5f}, {1.0f, 1.0f} }, // Bottom-Right
	{ {-0.5f,  0.5f, -0.5f}, {0.0f, 1.0f} }, // Bottom-Left

	// Bottom Face (Y = -0.5)
	{ {-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f} }, // Top-Left
	{ { 0.5f, -0.5f, -0.5f}, {1.0f, 0.0f} }, // Top-Right
	{ { 0.5f, -0.5f,  0.5f}, {1.0f, 1.0f} }, // Bottom-Right
	{ {-0.5f, -0.5f,  0.5f}, {0.0f, 1.0f} }, // Bottom-Left

	// Left Face (X = -0.5)
	{ {-0.5f,  0.5f,  0.5f}, {0.0f, 0.0f} }, // Top-Left
	{ {-0.5f,  0.5f, -0.5f}, {1.0f, 0.0f} }, // Top-Right
	{ {-0.5f, -0.5f, -0.5f}, {1.0f, 1.0f} }, // Bottom-Right
	{ {-0.5f, -0.5f,  0.5f}, {0.0f, 1.0f} }, // Bottom-Left

	// Right Face (X = 0.5)
	{ { 0.5f,  0.5f, -0.5f}, {0.0f, 0.0f} }, // Top-Left
	{ { 0.5f,  0.5f,  0.5f}, {1.0f, 0.0f} }, // Top-Right
	{ { 0.5f, -0.5f,  0.5f}, {1.0f, 1.0f} }, // Bottom-Right
	{ { 0.5f, -0.5f, -0.5f}, {0.0f, 1.0f} }  // Bottom-Left
};

unsigned int cubeIndices[] = {
	// Front Face
	0, 1, 2,
	0, 2, 3,

	// Back Face
	4, 5, 6,
	4, 6, 7,

	// Top Face
	8, 9, 10,
	8, 10, 11,

	// Bottom Face
	12, 13, 14,
	12, 14, 15,

	// Left Face
	16, 17, 18,
	16, 18, 19,

	// Right Face
	20, 21, 22,
	20, 22, 23
};
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
	for (unsigned int idx : cubeIndices)
	{
		outindicies.push_back(idx);
	}
	for (PosUVVertex& vert : cubeverticies)
	{
		VertexV0* vert0 = new VertexV0();
		vert0->m_position = vert.pos;
		vert0->m_uv = vert.uv;
		outverticies.push_back(vert0);
	}
}