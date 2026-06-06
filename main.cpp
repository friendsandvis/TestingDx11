#include"Win32WindMaker.h"
#include"Dx11Manager.h"
#include"DX11ApplicationManagerBase.h"
#include"ClearScreenApplication.h"
#include"SimpleTriangleApplication.h"
#include"SimpleQuadApplication.h"
#include"SimpleCubeApplication.h"
#include<iostream>
#define WINWIDTH 1920
#define WINHEIGHT 1080
int main()
{
	std::cout << "0.clearscreen.\n";
	std::cout << "1.triangleApplication.\n";
	std::cout << "2.quadApplication.\n";
	std::cout << "3.cubeApplication.\n";
	std::cout << "Enter App Number to run:-\n";
	int appnumber;
	std::cin >> appnumber;
	
	Win32WindMaker* winmaker = new Win32WindMaker();
	winmaker->CreateWind(WINWIDTH, WINHEIGHT, "DX11 Window");
	Dx11Manager dx11Manager;
	DX11ApplicationManagerBase* dx11AppManager = nullptr;
	switch (appnumber)
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
		case 2:
		{
			dx11AppManager = new SimpleQuadApplication();
			break;
		}
		case 3:
		{
			dx11AppManager = new SimpleCubeApplication();
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