#include"SimpleTriangleApplication.h"

void SimpleTriangleApplication::InitExtras(ComPtr<ID3D11Device> device)
{
	//create shaders
	m_simpleVertexShader.Init(device,L"shaders/simpletriangle/VS.hlsl",ShaderType::VS,"main");
	//create triangle model data
	//vertexbuffer
	std::vector<VertexBase*> verticies;
	GetTriangleVertices(verticies);
	std::vector<float> verticiesDataRaw;
	VertexBase::BuildRawVertexBuffer(verticies, verticiesDataRaw);
	assert(verticiesDataRaw.size() > 0);
	D3D11_BUFFER_DESC vertexBufferDesc = {};
	//only vertex v0 used in here for test
	vertexBufferDesc.ByteWidth = sizeof(verticiesDataRaw[0]) * verticiesDataRaw.size();
	vertexBufferDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.Usage = D3D11_USAGE::D3D11_USAGE_IMMUTABLE;
	D3D11_SUBRESOURCE_DATA vertexBufferInitData = {};
	vertexBufferInitData.pSysMem = reinterpret_cast<void*>(verticiesDataRaw.data());
	vertexBufferInitData.SysMemPitch = 0;
	vertexBufferInitData.SysMemSlicePitch = 0;
	m_triangle_vertexBuffer.Init(device, vertexBufferDesc,vertexBufferInitData);
}
void SimpleTriangleApplication::Render(RenderContext context)
{
	context.m_mainContext->OMSetRenderTargets(1, m_swapchain.GetBackBufferRTV().GetAddressOf(), nullptr);
	D3D11_RECT scissorRect = GetScissorRect();
	context.m_mainContext->RSSetScissorRects(1, &scissorRect);
	D3D11_VIEWPORT viewport = GetViewport();
	context.m_mainContext->RSSetViewports(1, &viewport);
	float clearcolour[4] = { 0.0f,1.0f,0.0f,1.0f };
	context.m_mainContext->ClearRenderTargetView(m_swapchain.GetBackBufferRTV().Get(), clearcolour);
	//----pipeline states
	context.m_mainContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	//calculate  add stride and offset based on hardcoded assumption of using VertexVersion0 get from vertexdata used for triangle rendering.
	UINT v_stride = sizeof(sizeof(VertexV0));
	UINT v_offset = 0;

	context.m_mainContext->IASetVertexBuffers(0, 1, m_triangle_vertexBuffer.GetDXBuffer().GetAddressOf(),&v_stride, &v_offset);
	//input layout
	//raster state
	// blend state
	//shader
	//draw
	m_swapchain.Present();
}
void SimpleTriangleApplication::GetTriangleVertices(std::vector<VertexBase*>& outverticies)
{
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