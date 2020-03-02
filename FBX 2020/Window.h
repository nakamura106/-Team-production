#ifndef WINDOW
#define WINDOW

#include<Windows.h>

#define WINDOW_CLASS_NAME "Window"	//!< ウィンドウクラス名

bool MakeWindow(int width, int height, const char* title);
HWND GetWindowHandle();
#endif