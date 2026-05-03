#pragma once
#include"DX11Common.h"

class DX11Buffer
{
public:
	void Init(ComPtr<ID3D11Device> device, D3D11_BUFFER_DESC desc,D3D11_SUBRESOURCE_DATA initData);
	ComPtr<ID3D11Buffer> GetDXBuffer()const { return m_buffer; }
private:
	ComPtr<ID3D11Buffer> m_buffer;
};