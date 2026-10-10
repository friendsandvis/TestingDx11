#include "DXTexManager.h"
//the solution used to build directxtex: DirectXTex_Desktop_2022_Win10.sln as it is the one with dx12 support else dx11 support.
#pragma comment(lib,"DirectXTex.lib")
//these are needed for windows only extension retrival function used(PathFindExtension)
#include<shlwapi.h>
#pragma comment(lib,"Shlwapi.lib")
#include<memory>
#include<string>
using namespace std;

bool DXTexManager::IsTextureTransparent(const wchar_t* imagefile)
{
	//for now assuming every .png texture file is transparent until we find a better way(ahould work for sfonza model
	wstring extension = PathFindExtension(imagefile);
	assert(!extension.empty());
	if (extension == L".png")
	{
		return true;
	}
	return false;
}

DXTexManager::DXTexManager()
{
}

DXTexManager::~DXTexManager()
{
}

bool DXTexManager::LoadTexture(const wchar_t* imagefile, DXImageData& outloadedImagedata, bool ignoreSRGB)
{
	HRESULT res = S_OK;
	wstring extension = PathFindExtension(imagefile);
	assert(!extension.empty());
	if (extension == L".dds")
	{
		res = LoadFromDDSFile(imagefile, DDS_FLAGS_ALLOW_LARGE_FILES, &outloadedImagedata.m_imagemetadata, outloadedImagedata.m_image);
	}
	else
	{
		WIC_FLAGS wicFlags = WIC_FLAGS::WIC_FLAGS_NONE;
		if (ignoreSRGB)
		{
			wicFlags |= WIC_FLAGS::WIC_FLAGS_IGNORE_SRGB;
		}
		res = LoadFromWICFile(imagefile, wicFlags, &outloadedImagedata.m_imagemetadata, outloadedImagedata.m_image);
	}


	return(res == S_OK);
}

DXTexture::DXTexture(std::wstring externalTexfileName)
{
	m_TextureFileName = externalTexfileName;
}
bool DXTexture::Init(ComPtr<ID3D11Device> creationdevice)
{

}