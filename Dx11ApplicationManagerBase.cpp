#include"DX11ApplicationManagerBase.h"
#include"windmaker.h"
#include"Win32WindMaker.h"

DX11ApplicationManagerBase::DX11ApplicationManagerBase()
{
	m_imguiAllowed = false;
}
DX11ApplicationManagerBase::~DX11ApplicationManagerBase()
{

}

void DX11ApplicationManagerBase::Init(WindMaker* window)
{
	InitExtras();
}

void DX11ApplicationManagerBase::RenderBase()
{
}

void DX11ApplicationManagerBase::ClearBackBuffer(float clearcolour[4], bool ClearDepth)
{
	//to do
}

void DX11ApplicationManagerBase::InitBase(WindMaker* window)
{

}
