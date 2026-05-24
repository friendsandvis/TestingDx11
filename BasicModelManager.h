#pragma once
#include<vector>
#include"VertexData.h"

class BasicModelManager
{
public:
	static void GetTriangleModelVerticies(std::vector<VertexBase*>& outverticies, VertexVersion vertexTypeToBuild = VertexVersion::VERTEXVERSION0);
};