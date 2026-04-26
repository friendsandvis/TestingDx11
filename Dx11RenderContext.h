#pragma once
#include"DX11Common.h"

struct RenderContext
{
	ComPtr<ID3D11Device> m_mainDevice;
	ComPtr<ID3D11DeviceContext> m_mainContext;
};
