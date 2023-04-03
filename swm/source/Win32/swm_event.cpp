#include "../../swm_event.h"

#include <Windows.h>
#include <iostream>

BEGIN_NAMESPACE

namespace
{
	Event current_events{};

	short current_key_states[256] = {};
	short old_key_states[256] = {};
} // End of anonymous namespace

extern unsigned int get_window_id(HWND hwnd);

LRESULT CALLBACK EventWndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	switch (msg)
	{
	case WM_DESTROY: return 0;

	case WM_CLOSE: current_events.window.type = WINDOW_CLOSE;  return 0;
	case WM_QUIT: current_events.window.type = WINDOW_QUIT;  return 0;
	case WM_SIZE: current_events.window.type = WINDOW_SIZE; return 0;
	case WM_MOVE: current_events.window.type = WINDOW_MOVE; return 0;
	case WM_SETFOCUS: current_events.window.type = WINDOW_SETFOCUS; return 0;
	case WM_KILLFOCUS: current_events.window.type = WINDOW_KILLFOCUS; return 0;
	}

	return DefWindowProcW(hwnd, msg, wparam, lparam);
}

void UpdateKeyStates()
{
	memcpy(old_key_states, current_key_states, sizeof(short) * 256);
	for (int i{ 0 }; i < 256; i++)
	{
		current_key_states[i] = GetKeyState(i);
	}
}

bool PollEvents(Event& e)
{
	MSG msg{};
	BOOL result = PeekMessageW(&msg, 0, 0, 0, PM_REMOVE);
	
	memcpy(current_events.keys.key_states, current_key_states, sizeof(current_key_states));
	memcpy(current_events.keys.old_key_states, old_key_states, sizeof(old_key_states));

	current_events.window.wnd = get_window_id(msg.hwnd);
	current_events.window.type = 0;

	if (result)
	{
		TranslateMessage(&msg);
		DispatchMessageW(&msg);

		UpdateKeyStates();
		e = current_events;
	}

	return result;
}

bool
KeyIsDown(Keys key)
{
	if (current_key_states[(short)key] & 0x80)
	{
		return true;
	}

	return false;
}

bool
KeyIsUp(Keys key)
{
	if (!(current_key_states[(short)key] & 0x80))
	{
		return true;
	}

	return false;
}

bool
OnKeyDown(Keys key)
{
	if (current_key_states[(short)key] & 0x80)
	{
		if (current_key_states[(short)key] != old_key_states[(short)key])
		{
			return true;
		}
	}

	return false;
}

bool
OnKeyUp(Keys key)
{
	if (!(current_key_states[(short)key] & 0x80))
	{
		if (current_key_states[(short)key] != old_key_states[(short)key])
		{
			return true;
		}
	}

	return false;
}

END_NAMESPACE
