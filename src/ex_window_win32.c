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

typedef struct ex_event_list {
	struct ex_event_list* next;

	ex_event event;
} ex_event_list;

struct ex_window {
	HWND hwnd;

	ex_event_list* event;
};

static int _window_count = 0;

static LRESULT CALLBACK window_proc(HWND, UINT, WPARAM, LPARAM);

ex_window* ex_window_create(const char* title, int width, int height, unsigned int flags) {
	ex_window* window = (ex_window*)malloc(sizeof(ex_window));

	window->event = NULL;
	window->hwnd = NULL;

	if (_window_count == 0) {
		WNDCLASS windowClass;
		windowClass.style = 0;
		windowClass.lpfnWndProc = window_proc;
		windowClass.cbClsExtra = 0;
		windowClass.cbWndExtra = 0;
		windowClass.hInstance = GetModuleHandle(NULL);
		windowClass.hIcon = NULL;
		windowClass.hCursor = 0;
		windowClass.hbrBackground = 0;
		windowClass.lpszMenuName = NULL;
		windowClass.lpszClassName = "ex";
		RegisterClass(&windowClass);
	}

	HDC screenDC = GetDC(NULL);
	int left = (GetDeviceCaps(screenDC, HORZRES) - width) / 2;
	int top = (GetDeviceCaps(screenDC, VERTRES) - height) / 2;
	ReleaseDC(NULL, screenDC);

	RECT rect;
	rect.left = rect.top = 0;
	rect.right = width;
	rect.bottom = height;

	DWORD style = 0;
	if (flags & EX_WINDOW_TITLEBAR)  style |= WS_CAPTION | WS_MINIMIZEBOX;
	if (flags & EX_WINDOW_RESIZABLE) style |= WS_THICKFRAME | WS_MAXIMIZEBOX;
	if (flags & EX_WINDOW_CLOSE)     style |= WS_SYSMENU;
	if (flags & EX_WINDOW_VISIBLE)   style |= WS_VISIBLE;

	AdjustWindowRect(&rect, style, FALSE);
	width = rect.right - rect.left;
	height = rect.bottom - rect.top;

	window->hwnd = CreateWindow("ex", title, style, left, top, width, height, NULL, NULL, GetModuleHandle(NULL), window);
	if (!window->hwnd) {
		if (_window_count == 0) {
			UnregisterClass("ex", GetModuleHandle(NULL));
		}

		free(window);
		return NULL;
	}

	_window_count++;
	return window;
}

void ex_window_destroy(ex_window* window) {
	while (window->event) {
		ex_event_list* next = window->event->next;
		free(window->event);
		window->event = next;
	}

	DestroyWindow(window->hwnd);

	_window_count--;

	if (_window_count == 0) {
		UnregisterClass("ex", GetModuleHandle(NULL));
	}

	free(window);
}

int ex_window_poll_events(ex_window* window, ex_event* event) {
	MSG message;
	while (PeekMessage(&message, window->hwnd, 0, 0, PM_REMOVE)) {
		TranslateMessage(&message);
		DispatchMessage(&message);
	}

	if (event && window->event) {
		*event = window->event->event;

		ex_event_list* node = window->event->next;
		free(window->event);
		window->event = node;

		return 1;
	}

	return 0;
}

void ex_window_push_event(ex_window* window, ex_event* event) {
	ex_event_list* node = (ex_event_list*)malloc(sizeof(ex_event_list));
	node->event = *event;
	node->next = window->event;
	window->event = node;
}

ex_window_handle ex_window_get_handle(ex_window* window) {
	return window->hwnd;
}

void ex_window_set_visible(ex_window* window, int visible) {
	ShowWindow(window->hwnd, visible ? SW_SHOW : SW_HIDE);
}

int ex_window_is_visible(ex_window* window) {
	return IsWindowVisible(window->hwnd);
}

LRESULT CALLBACK window_proc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	ex_window* window;

	if (msg == WM_CREATE) {
		SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG)((CREATESTRUCT*)(lParam))->lpCreateParams);
	}

	window = hwnd ? (ex_window*)(GetWindowLongPtr(hwnd, GWLP_USERDATA)) : NULL;
	if (window) {
		ex_event event;
		switch (msg) {
			case WM_CLOSE:
				event.type = EX_EVENT_CLOSE;
				ex_window_push_event(window, &event);
				break;
		}
	}

	if (msg == WM_CLOSE) {
		return 0;
	}

	if ((msg == WM_SYSCOMMAND) && (wParam == SC_KEYMENU)) {
		return 0;
	}

	return DefWindowProc(hwnd, msg, wParam, lParam);
}

#endif