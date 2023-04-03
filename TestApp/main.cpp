#include "../swm/swm.h"
#include "../swmpng/swmpng.h"

#include <iostream>
#include <Windows.h>

#include <gl/GL.h>
#pragma comment(lib, "opengl32.lib")

int main()
{
	swm::Window window = swm::InitWindow("Test Window", SWM_WINDOWPOS_CENTERED, SWM_WINDOWPOS_CENTERED, 800, 600, swm::WINDOW_OPENGL);
	swm::GLContext context = swm::CreateGLContext(window);
	
	bool IsRunning = true;
	while (IsRunning)
	{
		swm::Event Event{};
		while (swm::PollEvents(Event))
		{
			if (Event.window.type == swm::WINDOW_CLOSE)
			{
				IsRunning = false;
			}
		}
		
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
		glClearColor(0.f, 0.f, 0.f, 1.f);
		swm::SwapBuffers(window);
	}

	return 0;
}
