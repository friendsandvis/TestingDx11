#include"Win32WindMaker.h"
#include"Dx11Manager.h"
#include"DX11ApplicationManagerBase.h"
#include"ClearScreenApplication.h"
#define WINWIDTH 1920
#define WINHEIGHT 1080
int main()
{
	Win32WindMaker* winmaker = new Win32WindMaker();
	winmaker->CreateWind(WINWIDTH, WINHEIGHT, "DX11 Window");
	Dx11Manager dx11Manager;
	DX11ApplicationManagerBase* dx11AppManager = nullptr;
	dx11AppManager = new ClearScreenApplication();
	WindowProcHook* windhook = dynamic_cast<WindowProcHook*>(dx11AppManager);
	ProcManager::SetProcHook(windhook);
	dx11Manager.Init(winmaker, dx11AppManager);
	//run loop with app manager
	winmaker->RunLoop(&dx11Manager);
	if (dx11AppManager)
	{
		delete dx11AppManager;
	}
	if(winmaker)
	{
		delete winmaker;
	}
	return 0;
}