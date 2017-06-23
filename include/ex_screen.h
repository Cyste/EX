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
#ifndef EX_SCREEN_H_
#define EX_SCREEN_H_

typedef struct ex_screen_t ex_screen_t;

EX_API ex_screen_t* ex_screen_create(int width, int height, unsigned int flags);

EX_API void ex_screen_destroy(ex_screen_t* screen);

EX_API void ex_screen_resize(ex_screen_t* screen, int width, int height);

EX_API void ex_screen_bind_geometry_buffer(ex_screen_t* screen);

EX_API void ex_screen_bind_light_buffer(ex_screen_t* screen);

EX_API void ex_screen_send_to_light_pass(ex_screen_t* screen, ex_shader_t* point, ex_shader_t* directional);

EX_API void ex_screen_send_to_present(ex_screen_t* screen, ex_shader_t* shader);

#endif