#pragma once
#include"DXtexUtils.h"
class DXTexManager
{
public:
	DXTexManager();
	~DXTexManager();
	static bool LoadTexture(const wchar_t* imagefile, DXImageData& outloadedImagedata, bool ignoreSRGB = false);
	static bool IsTextureTransparent(const wchar_t* imagefile);

private:

};