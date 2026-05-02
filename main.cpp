#include"Win32WindMaker.h"
#include"Dx11Manager.h"
#include"DX11ApplicationManagerBase.h"
#include"ClearScreenApplication.h"
#include"SimpleTriangleApplication.h"
#define WINWIDTH 1920
#define WINHEIGHT 1080
int main()
{
	int appToTest = 1;
	
	Win32WindMaker* winmaker = new Win32WindMaker();
	winmaker->CreateWind(WINWIDTH, WINHEIGHT, "DX11 Window");
	Dx11Manager dx11Manager;
	DX11ApplicationManagerBase* dx11AppManager = nullptr;
	switch (appToTest)
	{
		case 0:
		{
			dx11AppManager = new ClearScreenApplication();
			break;
		}
		case 1:
		{
			dx11AppManager = new SimpleTriangleApplication();
			break;
		}
	}
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