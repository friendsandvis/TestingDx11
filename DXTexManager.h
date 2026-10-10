#pragma once
#include"DXtexUtils.h"
//does not represents a generic dx12 texture but just a dx12 texture resource representing a directxtex loaded textre(the init creates commited resource as it calls DXTex createtexture fuction)
class DXTexture
{
	DXImageData m_texdata;
	//DX12Buffer m_uploadbuffer;
	//vector< D3D12_SUBRESOURCE_DATA> m_uploadsubresdata;
	std::wstring m_TextureFileName = L"";

public:
	DXTexture(std::wstring externalTexfileName);
	DXTexture() {}
	DXImageData& GetDXImageData() { return m_texdata; }
	size_t GetTotalMipCount() { return m_texdata.m_imagemetadata.mipLevels; }
	//void CreateSRV(ComPtr< ID3D12Device> creationdevice, D3D12_SHADER_RESOURCE_VIEW_DESC srvdesc, D3D12_CPU_DESCRIPTOR_HANDLE srvhandle);

	bool Init(ComPtr<ID3D11Device> creationdevice);
	void UploadTexture();
	std::wstring GetExternalTextureFileName() { return m_TextureFileName; }
};
class DXTexManager
{
public:
	DXTexManager();
	~DXTexManager();
	static bool LoadTexture(const wchar_t* imagefile, DXImageData& outloadedImagedata, bool ignoreSRGB = false);
	static bool IsTextureTransparent(const wchar_t* imagefile);

private:

};