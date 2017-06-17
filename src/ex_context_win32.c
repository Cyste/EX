/*
	Copyright 2015 Mariusz Dzikowski

	Licensed under the Apache License, Version 2.0 (the "License");
	you may not use this file except in compliance with the License.
	You may obtain a copy of the License at

	http://www.apache.org/licenses/LICENSE-2.0

	Unless required by applicable law or agreed to in writing, software
	distributed under the License is distributed on an "AS IS" BASIS,
	WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
	See the License for the specific language governing permissions and
	limitations under the License.
*/
#include <ex.h>

#ifdef EX_OS_WINDOWS

#include <stdlib.h>
#include <Windows.h>

#define GLEW_STATIC
#include "gl/glew.h"
#include "gl/wglew.h"

struct ex_context {
	HWND hwnd;
	HDC hdc;
	HGLRC hglrc;
};

ex_context* ex_context_create(ex_window* window) {
	ex_assert(window);

	ex_context* context = (ex_context*)malloc(sizeof(ex_context));

	PIXELFORMATDESCRIPTOR pfd = {
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,    //Flags
		PFD_TYPE_RGBA,            //The kind of framebuffer. RGBA or palette.
		32,                        //Colordepth of the framebuffer.
		0, 0, 0, 0, 0, 0,
		0,
		0,
		0,
		0, 0, 0, 0,
		24,                        //Number of bits for the depthbuffer
		8,                        //Number of bits for the stencilbuffer
		0,                        //Number of Aux buffers in the framebuffer.
		PFD_MAIN_PLANE,
		0,
		0, 0, 0
	};

	context->hwnd = ex_window_get_handle(window);
	ex_assert(context->hwnd);

	context->hdc = GetDC(context->hwnd);
	ex_assert(context->hdc);

	int pixel = ChoosePixelFormat(context->hdc, &pfd);
	SetPixelFormat(context->hdc, pixel, &pfd);

	context->hglrc = wglCreateContext(context->hdc);
	ex_assert(context->hglrc);

	ex_verify(ex_context_make_current(context));

	ex_verify(glewInit() == GLEW_OK);

	ex_verify(wglewInit() == GLEW_OK);

	return context;
}

int ex_context_interval(ex_context* context, int interval) {
	if (WGLEW_EXT_swap_control) {
		int result = wglSwapIntervalEXT(interval);
		if (!result && interval == EX_INTERVAL_ADAPTIVE_VSYNC) {
			return ex_context_interval(context, EX_INTERVAL_VSYNC);
		}
		return result;
	}
	return 0;
}

int ex_context_swap(ex_context* context) {
	return SwapBuffers(context->hdc);
}

int ex_context_make_current(ex_context* context) {
	return wglMakeCurrent(context->hdc, context->hglrc);
}

int ex_context_is_current(ex_context* context) {
	return wglGetCurrentContext() == context->hglrc;
}

void ex_context_destroy(ex_context* context) {
	ReleaseDC(context->hwnd, context->hdc);

	wglDeleteContext(context->hglrc);

	free(context);
}

#endif