#include "Window.h"
#include "Graphics.h"
#include "Engine.h"
#include "Input.h"

bool InitEngine(int width, int height, const char* title_name)
{
	if (MakeWindow(width, height, title_name) == false)
	{
		return false;
	}

	if (InitGraphics() == false)
	{
		return false;
	}
	if (InitInput() == false)
	{
		return false;
	}

	//InitTexture();

	return true;
}

void EndEngine()
{
	ReleaseGraphics();
	
}