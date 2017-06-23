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

typedef struct ex_event_list_t {
	struct ex_event_list_t* next;

	ex_event_t event;
} ex_event_list_t;

struct ex_window_t {
	HWND hwnd;

	ex_event_list_t* event;

	int resizing;
};

static int _window_count = 0;

static LRESULT CALLBACK window_proc(HWND, UINT, WPARAM, LPARAM);

ex_window_t* ex_window_create(const char* title, int width, int height, unsigned int flags) {
	ex_window_t* window = (ex_window_t*)ex_malloc(sizeof(ex_window_t));

	window->event = NULL;
	window->hwnd = NULL;
	window->resizing = 0;

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

		ex_free(window);
		return NULL;
	}

	_window_count++;
	return window;
}

void ex_window_destroy(ex_window_t* window) {
	while (window->event) {
		ex_event_list_t* next = window->event->next;
		ex_free(window->event);
		window->event = next;
	}

	DestroyWindow(window->hwnd);

	_window_count--;

	if (_window_count == 0) {
		UnregisterClass("ex", GetModuleHandle(NULL));
	}

	ex_free(window);
}

int ex_window_poll_events(ex_window_t* window, ex_event_t* event) {
	MSG message;
	while (PeekMessage(&message, window->hwnd, 0, 0, PM_REMOVE)) {
		TranslateMessage(&message);
		DispatchMessage(&message);
	}

	if (event && window->event) {
		*event = window->event->event;

		ex_event_list_t* node = window->event->next;
		ex_free(window->event);
		window->event = node;

		return 1;
	}

	return 0;
}

void ex_window_push_event(ex_window_t* window, ex_event_t* event) {
	ex_event_list_t* node = (ex_event_list_t*)ex_malloc(sizeof(ex_event_list_t));
	ex_event_list_t* list = window->event;

	node->event = *event;
	node->next = NULL;

	if (list) {
		while (list->next) {
			list = list->next;
		}
		list->next = node;
	} else {
		window->event = node;
	}
}

ex_window_handle_t ex_window_get_handle(ex_window_t* window) {
	return window->hwnd;
}

void ex_window_set_visible(ex_window_t* window, int visible) {
	ShowWindow(window->hwnd, visible ? SW_SHOW : SW_HIDE);
}

int ex_window_is_visible(ex_window_t* window) {
	return IsWindowVisible(window->hwnd);
}

void ex_window_get_size(ex_window_t* window, int* width, int* height) {
	RECT rect;
	GetClientRect(window->hwnd, &rect);

	if (width) {
		*width = rect.right - rect.left;
	}

	if (height) {
		*height = rect.bottom - rect.top;
	}
}

static
int to_ex_key(WPARAM  key, LPARAM flags) {
	switch (key) {
		case VK_SHIFT: {
			UINT lShift = MapVirtualKey(VK_LSHIFT, MAPVK_VK_TO_VSC);
			UINT scancode = (UINT)((flags & (0xFF << 16)) >> 16);
			return (scancode == lShift) ? EX_KEY_LSHIFT : EX_KEY_RSHIFT;
		}

		case VK_MENU:
			return (HIWORD(flags) & KF_EXTENDED) ? EX_KEY_RALT : EX_KEY_LALT;

		case VK_CONTROL:
			return (HIWORD(flags) & KF_EXTENDED) ? EX_KEY_RCONTROL : EX_KEY_LCONTROL;

		case VK_LWIN:       return EX_KEY_LSYSTEM;
		case VK_RWIN:       return EX_KEY_RSYSTEM;
		case VK_APPS:       return EX_KEY_MENU;
		case VK_OEM_1:      return EX_KEY_SEMICOLON;
		case VK_OEM_2:      return EX_KEY_SLASH;
		case VK_OEM_PLUS:   return EX_KEY_EQUAL;
		case VK_OEM_MINUS:  return EX_KEY_DASH;
		case VK_OEM_4:      return EX_KEY_LBRACKET;
		case VK_OEM_6:      return EX_KEY_RBRACKET;
		case VK_OEM_COMMA:  return EX_KEY_COMMA;
		case VK_OEM_PERIOD: return EX_KEY_PERIOD;
		case VK_OEM_7:      return EX_KEY_QUOTE;
		case VK_OEM_5:      return EX_KEY_BACKSLASH;
		case VK_OEM_3:      return EX_KEY_TILDE;
		case VK_ESCAPE:     return EX_KEY_ESCAPE;
		case VK_SPACE:      return EX_KEY_SPACE;
		case VK_RETURN:     return EX_KEY_RETURN;
		case VK_BACK:       return EX_KEY_BACKSPACE;
		case VK_TAB:        return EX_KEY_TAB;
		case VK_PRIOR:      return EX_KEY_PAGEUP;
		case VK_NEXT:       return EX_KEY_PAGEDOWN;
		case VK_END:        return EX_KEY_END;
		case VK_HOME:       return EX_KEY_HOME;
		case VK_INSERT:     return EX_KEY_INSERT;
		case VK_DELETE:     return EX_KEY_DELETE;
		case VK_ADD:        return EX_KEY_ADD;
		case VK_SUBTRACT:   return EX_KEY_SUBTRACT;
		case VK_MULTIPLY:   return EX_KEY_MULTIPLY;
		case VK_DIVIDE:     return EX_KEY_DIVIDE;
		case VK_PAUSE:      return EX_KEY_PAUSE;
		case VK_F1:         return EX_KEY_F1;
		case VK_F2:         return EX_KEY_F2;
		case VK_F3:         return EX_KEY_F3;
		case VK_F4:         return EX_KEY_F4;
		case VK_F5:         return EX_KEY_F5;
		case VK_F6:         return EX_KEY_F6;
		case VK_F7:         return EX_KEY_F7;
		case VK_F8:         return EX_KEY_F8;
		case VK_F9:         return EX_KEY_F9;
		case VK_F10:        return EX_KEY_F10;
		case VK_F11:        return EX_KEY_F11;
		case VK_F12:        return EX_KEY_F12;
		case VK_F13:        return EX_KEY_F13;
		case VK_F14:        return EX_KEY_F14;
		case VK_F15:        return EX_KEY_F15;
		case VK_LEFT:       return EX_KEY_LEFT;
		case VK_RIGHT:      return EX_KEY_RIGHT;
		case VK_UP:         return EX_KEY_UP;
		case VK_DOWN:       return EX_KEY_DOWN;
		case VK_NUMPAD0:    return EX_KEY_NUMPAD0;
		case VK_NUMPAD1:    return EX_KEY_NUMPAD1;
		case VK_NUMPAD2:    return EX_KEY_NUMPAD2;
		case VK_NUMPAD3:    return EX_KEY_NUMPAD3;
		case VK_NUMPAD4:    return EX_KEY_NUMPAD4;
		case VK_NUMPAD5:    return EX_KEY_NUMPAD5;
		case VK_NUMPAD6:    return EX_KEY_NUMPAD6;
		case VK_NUMPAD7:    return EX_KEY_NUMPAD7;
		case VK_NUMPAD8:    return EX_KEY_NUMPAD8;
		case VK_NUMPAD9:    return EX_KEY_NUMPAD9;
		case 'A':           return EX_KEY_A;
		case 'Z':           return EX_KEY_Z;
		case 'E':           return EX_KEY_E;
		case 'R':           return EX_KEY_R;
		case 'T':           return EX_KEY_T;
		case 'Y':           return EX_KEY_Y;
		case 'U':           return EX_KEY_U;
		case 'I':           return EX_KEY_I;
		case 'O':           return EX_KEY_O;
		case 'P':           return EX_KEY_P;
		case 'Q':           return EX_KEY_Q;
		case 'S':           return EX_KEY_S;
		case 'D':           return EX_KEY_D;
		case 'F':           return EX_KEY_F;
		case 'G':           return EX_KEY_G;
		case 'H':           return EX_KEY_H;
		case 'J':           return EX_KEY_J;
		case 'K':           return EX_KEY_K;
		case 'L':           return EX_KEY_L;
		case 'M':           return EX_KEY_M;
		case 'W':           return EX_KEY_W;
		case 'X':           return EX_KEY_X;
		case 'C':           return EX_KEY_C;
		case 'V':           return EX_KEY_V;
		case 'B':           return EX_KEY_B;
		case 'N':           return EX_KEY_N;
		case '0':           return EX_KEY_NUM0;
		case '1':           return EX_KEY_NUM1;
		case '2':           return EX_KEY_NUM2;
		case '3':           return EX_KEY_NUM3;
		case '4':           return EX_KEY_NUM4;
		case '5':           return EX_KEY_NUM5;
		case '6':           return EX_KEY_NUM6;
		case '7':           return EX_KEY_NUM7;
		case '8':           return EX_KEY_NUM8;
		case '9':           return EX_KEY_NUM9;
	}

	return EX_KEY_UNKNOWN;
}

LRESULT CALLBACK window_proc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	ex_window_t* window;

	if (msg == WM_CREATE) {
		SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG)((CREATESTRUCT*)(lParam))->lpCreateParams);
	}

	window = hwnd ? (ex_window_t*)(GetWindowLongPtr(hwnd, GWLP_USERDATA)) : NULL;
	if (window) {
		ex_event_t event;
		switch (msg) {
			case WM_SIZE:
				if (!window->resizing) {
					event.type = EX_EVENT_RESIZE;
					ex_window_get_size(window, &event.resize.width, &event.resize.height);
					if (event.resize.width > 0 && event.resize.height > 0) {
						ex_window_push_event(window, &event);
					}
				}
				break;
			case WM_ENTERSIZEMOVE:
				window->resizing = 1;
				break;
			case WM_EXITSIZEMOVE:
				window->resizing = 0;
				event.type = EX_EVENT_RESIZE;
				ex_window_get_size(window, &event.resize.width, &event.resize.height);
				if (event.resize.width > 0 && event.resize.height > 0) {
					ex_window_push_event(window, &event);
				}
				break;
			case WM_CLOSE:
				event.type = EX_EVENT_CLOSE;
				ex_window_push_event(window, &event);
				break; 
			
			case WM_KEYUP:
			case WM_SYSKEYUP: {
				event.type = EX_EVENT_KEY_UP;
				event.key.key = to_ex_key(wParam, lParam);
				if (event.key.key >= 0 && event.key.key < EX_KEY_COUNT) {
					ex_window_push_event(window, &event);

					ex_keyboard_set_state(event.key.key, 0);
				}
				break;
			}

			case WM_KEYDOWN:
			case WM_SYSKEYDOWN: {
				event.type = EX_EVENT_KEY_DOWN;
				event.key.key = to_ex_key(wParam, lParam);
				if (event.key.key >= 0 && event.key.key < EX_KEY_COUNT) {
					ex_window_push_event(window, &event);

					ex_keyboard_set_state(event.key.key, 1);
				}
				break;
			}
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