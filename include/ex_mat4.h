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

typedef struct ex_mat4 {
	float m[16];
} ex_mat4;

void ex_mat4_identity(ex_mat4* mat);

void ex_mat4_scaling(ex_mat4* out, float x, float y, float z);

void ex_mat4_rotation_x(ex_mat4* out, float angle);

void ex_mat4_rotation_y(ex_mat4* out, float angle);

void ex_mat4_rotation_z(ex_mat4* out, float angle);

void ex_mat4_translation(ex_mat4* out, float x, float y, float z);

void ex_mat4_perspective(ex_mat4* out, float fovY, float aspect, float minZ, float maxZ);

void ex_mat4_multiply(ex_mat4* out, ex_mat4* a, ex_mat4* b);

void ex_mat4_multiply_vec4(ex_vec4* out, ex_mat4* a, ex_vec4* b);

void ex_mat4_transpose(ex_mat4* out, ex_mat4* mat);

void ex_mat4_inverse(ex_mat4* out, ex_mat4* mat);

void ex_mat4_extract_position(ex_vec3* out, ex_mat4* mat);

#endif