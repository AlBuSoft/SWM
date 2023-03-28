#include "../../swm_video.h"

#include <Windows.h>
#include <vector>
#include <map>

#pragma warning(disable : 4996)

BEGIN_NAMESPACE

struct WindowData
{
	const char* title;
	const wchar_t* wTitle;
	HWND handle;
};

namespace
{
	std::map<unsigned int, WindowData> Windows;
	unsigned int NextWindowID{ 1 };

	const wchar_t* CharToWChar(const char* chr)
	{
		const size_t len = strlen(chr);
		std::vector<wchar_t> vec;
		vec.resize(len + 1);
		mbstowcs(&vec[0], chr, len);
		const wchar_t* WChr = &vec[0];
		return WChr;
	}
} // End of anonymous namespace

Window* InitWindow(const char* title, int x, int y, int width, int height, unsigned int flags)
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
	wc.lpfnWndProc = DefWindowProcW;

	ATOM result = RegisterClassExW(&wc);
	if (!result)
	{
		// TODO: ErrorLogging
		return 0;
	}

	WindowData data{};
	data.title = title;
	data.wTitle = wTitle;
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
	UpdateWindow(data.handle);

	Window* window = &NextWindowID;
	Windows[NextWindowID] = data;
	NextWindowID++;

	return window;
}

END_NAMESPACE
