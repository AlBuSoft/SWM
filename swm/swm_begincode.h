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

#ifdef SWM_BEGIN_CODE
#error Dublicate include
#endif
#define SWM_BEGIN_CODE

#include "swm_config.h"

#ifndef SWM_API
#if _WIN32
#if SWM_DLL
#if SWM_DLL_EXPORT
#define SWM_API __declspec(dllexport)
#else
#define SWM_API __declspec(dllimport)
#endif
#else
#define SWM_API
#endif
#else
#endif
#endif

#ifndef BEGIN_NAMESPACE
#define BEGIN_NAMESPACE namespace swm {
#endif

#ifndef END_NAMESPACE
#define END_NAMESPACE }
#endif

#ifndef SWM_BIT
#define SWM_BIT(x) (1 << x)
#endif

#ifndef SWM_NORETURN
#if defined(_MSC_VER)
#define SWM_NORETURN __declspec(noreturn)
#endif
#endif

#ifndef NULL
#ifdef __cplusplus
#define NULL 0
#endif
#endif
