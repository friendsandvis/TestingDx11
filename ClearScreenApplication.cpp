#include"ClearScreenApplication.h"

void ClearScreenApplication::Render()
{
	float clearcolour[4] = { 1.0f,1.0f,1.0f,1.0f };
	ClearBackBuffer(clearcolour);
}