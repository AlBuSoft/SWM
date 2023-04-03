#include "../../swm_video.h"

#include "../../swm_event.h"

#include <Windows.h>
#include <vector>
#include <map>
#include <iostream>
#include <gl/GL.h>
#pragma comment(lib, "opengl32.lib")

#pragma warning(disable : 4996)

BEGIN_NAMESPACE

struct WindowData
{
	HWND handle = 0;
	const char* title = "";
	const wchar_t* wTitle = L"";
	int width = 0;
	int height = 0;
	int x = 0;
	int y = 0;

	struct
	{
		SIZEEVENTFUNCTION size = 0;
		MOVEEVENTFUNCTION move = 0;
		DRAWEVENTFUNCTION draw = 0;
	} functions;
};

extern LRESULT CALLBACK EventWndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

namespace
{
	std::map<unsigned int, WindowData> Windows;
	unsigned int NextWindowID{ 1 };
	std::map<HWND, unsigned int> WindowIDs;
	unsigned int CurrentWindowID = 0;

	const wchar_t* CharToWChar(const char* chr)
	{
		const size_t len = strlen(chr);
		std::vector<wchar_t> vec;
		vec.resize(len + 1);
		mbstowcs(&vec[0], chr, len);
		const wchar_t* WChr = &vec[0];
		return WChr;
	}

	LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
	{
		CurrentWindowID = WindowIDs[hwnd];
		switch (msg)
		{
		case WM_SIZE:
			Windows[WindowIDs[hwnd]].width = LOWORD(lparam);
			Windows[WindowIDs[hwnd]].height = HIWORD(lparam);
			if (Windows[WindowIDs[hwnd]].functions.size)
				Windows[WindowIDs[hwnd]].functions.size(WindowIDs[hwnd], wparam, LOWORD(lparam), HIWORD(lparam));
			break;

		case WM_MOVE:
			Windows[WindowIDs[hwnd]].x = LOWORD(lparam);
			Windows[WindowIDs[hwnd]].y = HIWORD(lparam);
			if (Windows[WindowIDs[hwnd]].functions.move)
				Windows[WindowIDs[hwnd]].functions.move(WindowIDs[hwnd], wparam, LOWORD(lparam), HIWORD(lparam));
			break;

		case WM_PAINT:
			if (Windows[WindowIDs[hwnd]].functions.draw)
				Windows[WindowIDs[hwnd]].functions.draw(WindowIDs[hwnd]);
			break;
		}

		return EventWndProc(hwnd, msg, wparam, lparam);
	}
} // End of anonymous namespace

void* GetWindowHandle(Window window)
{
	return Windows[window].handle;
}

unsigned int 
	get_window_id(HWND hwnd)
{
	return WindowIDs[hwnd];
}

void SetSizeEventFunction(unsigned int window, SIZEEVENTFUNCTION func)
{
	Windows[window].functions.size = func;
}

void SetMoveEventFunction(unsigned int window, MOVEEVENTFUNCTION func)
{
	Windows[window].functions.move = func;
}

void SetDrawEventFunction(unsigned int window, DRAWEVENTFUNCTION func)
{
	Windows[window].functions.draw = func;
}

Window InitWindow(const char* title, int x, int y, int width, int height, unsigned int flags)
{
	int pos_x{ x };
	int pos_y{ y };
	int size_x{ width };
	int size_y{ height };

	if (x == SWM_WINDOWPOS_CENTERED) pos_x = ((GetSystemMetrics(SM_CXSCREEN) - width) / 2);
	if (y == SWM_WINDOWPOS_CENTERED) pos_y = ((GetSystemMetrics(SM_CYSCREEN) - height) / 2);

	const wchar_t* wTitle = CharToWChar(title);

	WNDCLASSEXW wc{};
	ZeroMemory(&wc, sizeof(wc));
	wc.cbSize = sizeof(WNDCLASSEXW);
	wc.lpszClassName = wTitle;
	wc.hInstance = GetModuleHandleW(0);
	wc.lpfnWndProc = WndProc;
	wc.hbrBackground = CreateSolidBrush(RGB(255, 255, 255));

	ATOM result = RegisterClassExW(&wc);
	if (!result)
	{
		// TODO: ErrorLogging
		return 0;
	}

	WindowData data{};
	data.title = title;
	data.wTitle = wTitle;
	data.x = pos_x;
	data.y = pos_y;
	data.width = width;
	data.height = height;

	data.handle = CreateWindowExW(
		0, 
		wc.lpszClassName, 
		wTitle, 
		WS_OVERLAPPEDWINDOW, 
		pos_x, 
		pos_y, 
		size_x, 
		size_y, 
		0, 
		0, 
		wc.hInstance, 
		0
	);

	if (!data.handle)
	{
		// TODO: ErrorLogging
		return 0;
	}

	int show = SW_SHOWNORMAL;
	if (flags & WINDOW_HIDDEN)
	{
		show = SW_HIDE;
	}
	else if (flags & WINDOW_MINIMIZED)
	{
		show = SW_MINIMIZE;
	}
	else if (flags & WINDOW_MAXIMIZED)
	{
		show = SW_SHOWMAXIMIZED;
	}
	else if (flags & WINDOW_FULLSCREEN)
	{
		show = 3;
		// TODO: Implement SetFullscreen()
	}
	ShowWindow(data.handle, show);
	InvalidateRect(data.handle, nullptr, true);
	UpdateWindow(data.handle);

	Window window = NextWindowID;
	Windows[NextWindowID] = data;
	WindowIDs[data.handle] = NextWindowID;
	NextWindowID++;

	return window;
}

Window GetCurrentWindow()
{
	return CurrentWindowID;
}

GLContext CreateGLContext(Window window)
{
	PIXELFORMATDESCRIPTOR pfd{};
	ZeroMemory(&pfd, sizeof(PIXELFORMATDESCRIPTOR));
	pfd.nVersion = 1;
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_DRAW_TO_WINDOW | PFD_MAIN_PLANE | PFD_SUPPORT_OPENGL;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 24;

	HDC hdc = GetDC(Windows[window].handle);
	int index = ChoosePixelFormat(hdc, &pfd);
	SetPixelFormat(hdc, index, &pfd);
	HGLRC hglrc = wglCreateContext(hdc);
	wglMakeCurrent(hdc, hglrc);

	return hglrc;
}

GLContext GetCurrentGLContext(Window window)
{
	return wglGetCurrentContext();
}

void SwapBuffers(Window window)
{
	wglSwapLayerBuffers(GetDC(Windows[window].handle), WGL_SWAP_MAIN_PLANE);
}

END_NAMESPACE
