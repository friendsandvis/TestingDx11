#pragma once
#include"DX11ApplicationManagerBase.h"

class ClearScreenApplication : public DX11ApplicationManagerBase
{
public:
	void Render(RenderContext context) override;
};
