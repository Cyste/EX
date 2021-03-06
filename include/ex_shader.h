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
#ifndef EX_SHADER_H_
#define EX_SHADER_H_

typedef struct ex_shader_t ex_shader_t;

EX_API ex_shader_t* ex_shader_compile(const char* code);

EX_API ex_shader_t* ex_shader_load(const char* file_name);

EX_API void ex_shader_destroy(ex_shader_t* shader);

EX_API unsigned int ex_shader_get_id(ex_shader_t* shader);

EX_API void ex_shader_use(ex_shader_t* shader);

EX_API int ex_shader_get_uniform(ex_shader_t* shader, const char* name);

#endif