#include"DXVertexManager.h"

void DXVertexManager::BuildDefaultInputelementdesc(VertexVersion vtype)
{
	switch (vtype)
	{
	case VertexVersion::VERTEXVERSION0:
	{
	}
	break;
	case VertexVersion::VERTEXVERSION1:
	{}
	break;
	case VertexVersion::VERTEXVERSION2:
	{
	}
	break;
	case VertexVersion::VERTEXVERSION3:
	{
	}
	break;
	default:
		break;
	}
}

unsigned DXVertexManager::GetVertexSize(VertexVersion vtype)
{
	switch (vtype)
	{
	case VERTEXVERSION0:
		return(5 * sizeof(float)); break;
	case VERTEXVERSION2:
		return(6 * sizeof(float)); break;
	case VERTEXVERSION3:
		return(8 * sizeof(float)); break;
	default:
		return 0;
	}
}

void DXVertexManager::RetriveRawVertexData(std::vector<float>& outverticiesrawdata, VertexBase* avertex)
{
	switch (avertex->m_vertversion)
	{
	case VERTEXVERSION0:
	{
		VetexV0* vert = static_cast<VetexV0*>(avertex);
		outverticiesrawdata.push_back(vert->m_position.x);
		outverticiesrawdata.push_back(vert->m_position.y);
		outverticiesrawdata.push_back(vert->m_position.z);
		outverticiesrawdata.push_back(vert->m_uv.x);
		outverticiesrawdata.push_back(vert->m_uv.y);
		break;
	}
	case VERTEXVERSION2:
	{
		VetexV2* vert = static_cast<VetexV2*>(avertex);
		outverticiesrawdata.push_back(vert->m_position.x);
		outverticiesrawdata.push_back(vert->m_position.y);
		outverticiesrawdata.push_back(vert->m_position.z);
		outverticiesrawdata.push_back(vert->m_normal.x);
		outverticiesrawdata.push_back(vert->m_normal.y);
		outverticiesrawdata.push_back(vert->m_normal.z);
		break;
	}
	case VERTEXVERSION3:
	{
		VertexV3* vert = static_cast<VertexV3*>(avertex);
		outverticiesrawdata.push_back(vert->m_position.x);
		outverticiesrawdata.push_back(vert->m_position.y);
		outverticiesrawdata.push_back(vert->m_position.z);
		outverticiesrawdata.push_back(vert->m_normal.x);
		outverticiesrawdata.push_back(vert->m_normal.y);
		outverticiesrawdata.push_back(vert->m_normal.z);
		outverticiesrawdata.push_back(vert->m_uv.x);
		outverticiesrawdata.push_back(vert->m_uv.y);


	}
	default:
		break;
	}

}