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
#ifndef EX_WINDOW_H_
#define EX_WINDOW_H_

#define EX_WINDOW_TITLEBAR   (1 << 0)
#define EX_WINDOW_RESIZABLE  (1 << 1)
#define EX_WINDOW_CLOSE      (1 << 2)
#define EX_WINDOW_VISIBLE    (1 << 3)
#define EX_WINDOW_FULLSCREEN (1 << 4)
#define EX_WINDOW_DEFAULT    (EX_WINDOW_VISIBLE | EX_WINDOW_CLOSE | EX_WINDOW_TITLEBAR)

#ifdef EX_OS_WINDOWS
	typedef struct HWND__* ex_window_handle;
#elif defined(EX_OS_UNIX)
	typedef unsigned long ex_window_handle;
#endif

typedef struct ex_window ex_window;

ex_window* ex_window_create(const char* title, int width, int height, unsigned int flags);

void ex_window_destroy(ex_window* window);

int ex_window_poll_events(ex_window* window, ex_event* event);

void ex_window_push_event(ex_window* window, ex_event* event);

ex_window_handle ex_window_get_handle(ex_window* window);

void ex_window_set_visible(ex_window* window, int visible);

int ex_window_is_visible(ex_window* window);

#endif