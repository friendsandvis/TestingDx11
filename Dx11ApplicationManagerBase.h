#pragma once
#include"WindowProcHook.h"
#include"windmaker.h"
class DX11ApplicationManagerBase : public WindowProcHook
{
public:
	void Init(WindMaker* window);
	void InitBase(WindMaker* window);
	//basic necessary initialization of 
	virtual void Render() = 0;
	virtual void PreRenderUpdate() {}
	virtual void PostRenderUpdate() {}
	virtual void Destroy() {}
	virtual void IMGUIRenderAdditional() {}
	inline bool IsIMGUIAllowed()
	{
		return m_imguiAllowed;
	}
	void RenderBase();
	void ClearBackBuffer(float clearcolour[4], bool ClearDepth = true);
	DX11ApplicationManagerBase();
	virtual ~DX11ApplicationManagerBase();

protected:
	//a camera object representing the main camera for a basic application

	virtual void InitExtras() {}
	//imgui related
	bool m_imguiAllowed;
};
