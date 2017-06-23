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
#ifndef EX_MATRIX4_H_
#define EX_MATRIX4_H_

typedef struct ex_mat4_t {
	float m[16];
} ex_mat4_t;

EX_API void ex_mat4_identity(ex_mat4_t* mat);

EX_API void ex_mat4_scaling(ex_mat4_t* out, float x, float y, float z);

EX_API void ex_mat4_rotation_x(ex_mat4_t* out, float angle);

EX_API void ex_mat4_rotation_y(ex_mat4_t* out, float angle);

EX_API void ex_mat4_rotation_z(ex_mat4_t* out, float angle);

EX_API void ex_mat4_translation(ex_mat4_t* out, float x, float y, float z);

EX_API void ex_mat4_perspective(ex_mat4_t* out, float fovY, float aspect, float minZ, float maxZ);

EX_API void ex_mat4_multiply(ex_mat4_t* out, const ex_mat4_t* a, const ex_mat4_t* b);

EX_API void ex_mat4_multiply_vec4(ex_vec4_t* out, const ex_mat4_t* a, const ex_vec4_t* b);

EX_API void ex_mat4_transpose(ex_mat4_t* out, const ex_mat4_t* mat);

EX_API void ex_mat4_inverse(ex_mat4_t* out, const ex_mat4_t* mat);

EX_API void ex_mat4_extract_position(ex_vec3_t* out, const ex_mat4_t* mat);

#endif