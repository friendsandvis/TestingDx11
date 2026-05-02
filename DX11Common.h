#pragma once
#include<d3d11.h>
#include<dxgi1_3.h>
#include<wrl/client.h>
#include<cassert>
#include<DirectXMath.h>
#define BACKBUFFER_COUNT 2
#define DXASSERT(EXP)	{HRESULT res = EXP; assert(res == S_OK);}

using namespace Microsoft::WRL;
using namespace DirectX;