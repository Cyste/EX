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
#ifndef EX_CONTEXT_H_
#define EX_CONTEXT_H_

#define EX_INTERVAL_NONE           (0)
#define EX_INTERVAL_VSYNC          (1)
#define EX_INTERVAL_ADAPTIVE_VSYNC (-1)

typedef struct ex_context ex_context;

ex_context* ex_context_create(ex_window* window);

int ex_context_interval(ex_context* context, int interval);

int ex_context_swap(ex_context* context);

int ex_context_make_current(ex_context* context);

int ex_context_is_current(ex_context* context);

void ex_context_destroy(ex_context* context);

#endif