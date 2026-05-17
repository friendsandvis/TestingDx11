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

void VertexBase::BuildInputElementDesc(VertexVersion vertVersion, std::vector<D3D11_INPUT_ELEMENT_DESC>& outInputElementDescs)
{
	outInputElementDescs.clear();
	switch (vertVersion)
	{
	case VertexVersion::VERTEXVERSION0:
	{
		{
			D3D11_INPUT_ELEMENT_DESC inputElementDescPos = {};
			inputElementDescPos.InputSlot = 0;
			inputElementDescPos.SemanticName = "POS";
			inputElementDescPos.SemanticIndex = 0;
			inputElementDescPos.Format = DXGI_FORMAT::DXGI_FORMAT_R32G32B32_FLOAT;
			inputElementDescPos.InputSlotClass = D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA;
			inputElementDescPos.AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
			outInputElementDescs.push_back(inputElementDescPos);
		}
		{
			D3D11_INPUT_ELEMENT_DESC inputElementDescVUV = {};
			inputElementDescVUV.InputSlot = 0;
			inputElementDescVUV.SemanticName = "VUV";
			inputElementDescVUV.SemanticIndex = 0;
			inputElementDescVUV.Format = DXGI_FORMAT::DXGI_FORMAT_R32G32_FLOAT;
			inputElementDescVUV.InputSlotClass = D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA;
			inputElementDescVUV.AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
			outInputElementDescs.push_back(inputElementDescVUV);

		}
	}
	break;
	}
}