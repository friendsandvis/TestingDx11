#include"Dx11Buffer.h"

void DX11Buffer::Init(ComPtr<ID3D11Device> device,D3D11_BUFFER_DESC desc, D3D11_SUBRESOURCE_DATA initData)
{
	DXASSERT(device->CreateBuffer(&desc,&initData, m_buffer.GetAddressOf()))
}