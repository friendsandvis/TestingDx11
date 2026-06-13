#pragma once
#include<vector>
#include"VertexData.h"

class BasicModelManager
{
public:
	static void GetTriangleModelVerticies(std::vector<VertexBase*>& outverticies, VertexVersion vertexTypeToBuild = VertexVersion::VERTEXVERSION0);
	static void GetQuadModelVerticies(std::vector<VertexBase*>& outverticies, VertexVersion vertexTypeToBuild = VertexVersion::VERTEXVERSION0);
	static void GetQuadModelVerticiesIndexed(std::vector<VertexBase*>& outverticies, std::vector<unsigned int>& outindicies, VertexVersion vertexTypeToBuild = VertexVersion::VERTEXVERSION0);
	static void GetCubeModelVerticiesIndexed(std::vector<VertexBase*>& outverticies,std::vector<unsigned int>& outindicies, VertexVersion vertexTypeToBuild = VertexVersion::VERTEXVERSION0);
};