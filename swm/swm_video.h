/*
  Simple Window Module
  Copyright (c) 2023 AlBuSoft (FürthORG) <support@fürth.org>

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.
*/

#include "swm_begincode.h"

BEGIN_NAMESPACE

typedef unsigned int Window;

typedef enum
{
	WINDOW_OPENGL = SWM_BIT(0),
	WINDOW_MINIMIZED = SWM_BIT(1),
	WINDOW_MAXIMIZED = SWM_BIT(2),
	WINDOW_FULLSCREEN = SWM_BIT(3),
	WINDOW_HIDDEN = SWM_BIT(4),
	WINDOW_BORDERLESS = SWM_BIT(5),
} WindowFlags;

#define SWM_WINDOWPOS_CENTERED ((int)0x888888)

/*
* \since This function is available since v1.0.0.
*/
SWM_API Window* InitWindow(const char* title, int x, int y, int width, int height, unsigned int flags);

typedef void* GLContext;

END_NAMESPACE

#include "swm_endcode.h"
