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
#ifndef EX_TEXTURE_H_
#define EX_TEXTURE_H_

typedef struct ex_texture_t ex_texture_t;

EX_API ex_texture_t* ex_texture_create(void* data, int width, int height, int components);

EX_API ex_texture_t* ex_texture_load(const char* file_name);

EX_API void ex_texture_destroy(ex_texture_t* texture);

EX_API void ex_texture_generate_mipmaps(ex_texture_t* texture);

EX_API unsigned int ex_texture_get_id(ex_texture_t* texture);

EX_API int ex_texture_get_width(ex_texture_t* texture);

EX_API int ex_texture_get_height(ex_texture_t* texture);

#endif