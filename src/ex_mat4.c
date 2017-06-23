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

#include <math.h>
#include <string.h>

void ex_mat4_identity(ex_mat4_t* mat) {
	mat->m[0] = 1; mat->m[1] = 0; mat->m[2] = 0; mat->m[3] = 0;
	mat->m[4] = 0; mat->m[5] = 1; mat->m[6] = 0; mat->m[7] = 0;
	mat->m[8] = 0; mat->m[9] = 0; mat->m[10] = 1; mat->m[11] = 0;
	mat->m[12] = 0; mat->m[13] = 0; mat->m[14] = 0; mat->m[15] = 1;
}

void ex_mat4_scaling(ex_mat4_t* out, float x, float y, float z) {
	out->m[0] = x; out->m[1] = 0; out->m[2] = 0; out->m[3] = 0;
	out->m[4] = 0; out->m[5] = y; out->m[6] = 0; out->m[7] = 0;
	out->m[8] = 0; out->m[9] = 0; out->m[10] = z; out->m[11] = 0;
	out->m[12] = 0; out->m[13] = 0; out->m[14] = 0; out->m[15] = 1;
}

void ex_mat4_rotation_x(ex_mat4_t* out, float angle) {
	out->m[0] = 1; out->m[1] = 0; out->m[2] = 0; out->m[3] = 0;
	out->m[4] = 0; out->m[5] = cosf(angle); out->m[6] = sinf(angle); out->m[7] = 0;
	out->m[8] = 0; out->m[9] = -sinf(angle); out->m[10] = cosf(angle); out->m[11] = 0;
	out->m[12] = 0; out->m[13] = 0; out->m[14] = 0; out->m[15] = 1;
}

void ex_mat4_rotation_y(ex_mat4_t* out, float angle) {
	out->m[0] = cosf(angle); out->m[1] = 0; out->m[2] = -sinf(angle); out->m[3] = 0;
	out->m[4] = 0; out->m[5] = 1; out->m[6] = 0; out->m[7] = 0;
	out->m[8] = sinf(angle); out->m[9] = 0; out->m[10] = cosf(angle); out->m[11] = 0;
	out->m[12] = 0; out->m[13] = 0; out->m[14] = 0; out->m[15] = 1;
}

void ex_mat4_rotation_z(ex_mat4_t* out, float angle) {
	out->m[0] = cosf(angle); out->m[1] = sinf(angle); out->m[2] = 0; out->m[3] = 0;
	out->m[4] = -sinf(angle); out->m[5] = cosf(angle); out->m[6] = 0; out->m[7] = 0;
	out->m[8] = 0; out->m[9] = 0; out->m[10] = 1; out->m[11] = 0;
	out->m[12] = 0; out->m[13] = 0; out->m[14] = 0; out->m[15] = 1;
}

void ex_mat4_translation(ex_mat4_t* out, float x, float y, float z) {
	out->m[0] = 1; out->m[1] = 0; out->m[2] = 0; out->m[3] = 0;
	out->m[4] = 0; out->m[5] = 1; out->m[6] = 0; out->m[7] = 0;
	out->m[8] = 0; out->m[9] = 0; out->m[10] = 1; out->m[11] = 0;
	out->m[12] = x; out->m[13] = y; out->m[14] = z; out->m[15] = 1;
}

void ex_mat4_perspective(ex_mat4_t* out, float fovY, float aspect, float minZ, float maxZ) {
	float r = (fovY * 0.5f) * (EX_PI / 180.0f);

	float deltaZ = minZ - maxZ;
	float s = (float)sin(r);
	float cotangent = 0;

	if (deltaZ == 0 || s == 0 || aspect == 0) {
		ex_mat4_identity(out);
		return;
	}

	cotangent = (float)cos(r) / s;

	out->m[0] = cotangent / aspect; out->m[1] = 0; out->m[2] = 0; out->m[3] = 0;
	out->m[4] = 0; out->m[5] = cotangent; out->m[6] = 0; out->m[7] = 0;
	out->m[8] = 0; out->m[9] = 0; out->m[10] = (maxZ + minZ) / deltaZ; out->m[11] = -1;
	out->m[12] = 0; out->m[13] = 0; out->m[14] = (2 * maxZ * minZ) / deltaZ; out->m[15] = 1;
}

void ex_mat4_multiply(ex_mat4_t* out, const ex_mat4_t* a, const ex_mat4_t* b) {
	const float* m1 = a->m, *m2 = b->m;
	ex_mat4_t temp;

	temp.m[0] = m1[0] * m2[0] + m1[4] * m2[1] + m1[8] * m2[2] + m1[12] * m2[3];
	temp.m[1] = m1[1] * m2[0] + m1[5] * m2[1] + m1[9] * m2[2] + m1[13] * m2[3];
	temp.m[2] = m1[2] * m2[0] + m1[6] * m2[1] + m1[10] * m2[2] + m1[14] * m2[3];
	temp.m[3] = m1[3] * m2[0] + m1[7] * m2[1] + m1[11] * m2[2] + m1[15] * m2[3];

	temp.m[4] = m1[0] * m2[4] + m1[4] * m2[5] + m1[8] * m2[6] + m1[12] * m2[7];
	temp.m[5] = m1[1] * m2[4] + m1[5] * m2[5] + m1[9] * m2[6] + m1[13] * m2[7];
	temp.m[6] = m1[2] * m2[4] + m1[6] * m2[5] + m1[10] * m2[6] + m1[14] * m2[7];
	temp.m[7] = m1[3] * m2[4] + m1[7] * m2[5] + m1[11] * m2[6] + m1[15] * m2[7];

	temp.m[8] = m1[0] * m2[8] + m1[4] * m2[9] + m1[8] * m2[10] + m1[12] * m2[11];
	temp.m[9] = m1[1] * m2[8] + m1[5] * m2[9] + m1[9] * m2[10] + m1[13] * m2[11];
	temp.m[10] = m1[2] * m2[8] + m1[6] * m2[9] + m1[10] * m2[10] + m1[14] * m2[11];
	temp.m[11] = m1[3] * m2[8] + m1[7] * m2[9] + m1[11] * m2[10] + m1[15] * m2[11];

	temp.m[12] = m1[0] * m2[12] + m1[4] * m2[13] + m1[8] * m2[14] + m1[12] * m2[15];
	temp.m[13] = m1[1] * m2[12] + m1[5] * m2[13] + m1[9] * m2[14] + m1[13] * m2[15];
	temp.m[14] = m1[2] * m2[12] + m1[6] * m2[13] + m1[10] * m2[14] + m1[14] * m2[15];
	temp.m[15] = m1[3] * m2[12] + m1[7] * m2[13] + m1[11] * m2[14] + m1[15] * m2[15];

	memcpy(out->m, temp.m, sizeof(ex_mat4_t));
}

void ex_mat4_multiply_vec4(ex_vec4_t* out, const ex_mat4_t* a, const ex_vec4_t* b) {
	ex_vec4_assign(out,
		b->x * a->m[0] + b->y * a->m[4] + b->z * a->m[8] + b->w * a->m[12],
		b->x * a->m[1] + b->y * a->m[5] + b->z * a->m[9] + b->w * a->m[13],
		b->x * a->m[2] + b->y * a->m[6] + b->z * a->m[10] + b->w * a->m[14],
		b->x * a->m[3] + b->y * a->m[7] + b->z * a->m[11] + b->w * a->m[15]);
}

void ex_mat4_transpose(ex_mat4_t* out, const ex_mat4_t* mat) {
	ex_mat4_t tmp;
	tmp.m[0] = mat->m[0];  tmp.m[1] = mat->m[4];  tmp.m[2] = mat->m[8]; tmp.m[3] = mat->m[12];
	tmp.m[4] = mat->m[1];  tmp.m[5] = mat->m[5];  tmp.m[6] = mat->m[9]; tmp.m[7] = mat->m[13];
	tmp.m[8] = mat->m[2];  tmp.m[9] = mat->m[6];  tmp.m[10] = mat->m[10]; tmp.m[11] = mat->m[14];
	tmp.m[12] = mat->m[3]; tmp.m[13] = mat->m[7]; tmp.m[14] = mat->m[11]; tmp.m[15] = mat->m[15];
	memcpy(out->m, tmp.m, sizeof(ex_mat4_t));
}

void ex_mat4_inverse(ex_mat4_t* out, const ex_mat4_t* mat) {
	ex_mat4_t tmp;
	float det;
	int i;

	tmp.m[0] = mat->m[5] * mat->m[10] * mat->m[15] -
		mat->m[5] * mat->m[11] * mat->m[14] -
		mat->m[9] * mat->m[6] * mat->m[15] +
		mat->m[9] * mat->m[7] * mat->m[14] +
		mat->m[13] * mat->m[6] * mat->m[11] -
		mat->m[13] * mat->m[7] * mat->m[10];

	tmp.m[4] = -mat->m[4] * mat->m[10] * mat->m[15] +
		mat->m[4] * mat->m[11] * mat->m[14] +
		mat->m[8] * mat->m[6] * mat->m[15] -
		mat->m[8] * mat->m[7] * mat->m[14] -
		mat->m[12] * mat->m[6] * mat->m[11] +
		mat->m[12] * mat->m[7] * mat->m[10];

	tmp.m[8] = mat->m[4] * mat->m[9] * mat->m[15] -
		mat->m[4] * mat->m[11] * mat->m[13] -
		mat->m[8] * mat->m[5] * mat->m[15] +
		mat->m[8] * mat->m[7] * mat->m[13] +
		mat->m[12] * mat->m[5] * mat->m[11] -
		mat->m[12] * mat->m[7] * mat->m[9];

	tmp.m[12] = -mat->m[4] * mat->m[9] * mat->m[14] +
		mat->m[4] * mat->m[10] * mat->m[13] +
		mat->m[8] * mat->m[5] * mat->m[14] -
		mat->m[8] * mat->m[6] * mat->m[13] -
		mat->m[12] * mat->m[5] * mat->m[10] +
		mat->m[12] * mat->m[6] * mat->m[9];

	tmp.m[1] = -mat->m[1] * mat->m[10] * mat->m[15] +
		mat->m[1] * mat->m[11] * mat->m[14] +
		mat->m[9] * mat->m[2] * mat->m[15] -
		mat->m[9] * mat->m[3] * mat->m[14] -
		mat->m[13] * mat->m[2] * mat->m[11] +
		mat->m[13] * mat->m[3] * mat->m[10];

	tmp.m[5] = mat->m[0] * mat->m[10] * mat->m[15] -
		mat->m[0] * mat->m[11] * mat->m[14] -
		mat->m[8] * mat->m[2] * mat->m[15] +
		mat->m[8] * mat->m[3] * mat->m[14] +
		mat->m[12] * mat->m[2] * mat->m[11] -
		mat->m[12] * mat->m[3] * mat->m[10];

	tmp.m[9] = -mat->m[0] * mat->m[9] * mat->m[15] +
		mat->m[0] * mat->m[11] * mat->m[13] +
		mat->m[8] * mat->m[1] * mat->m[15] -
		mat->m[8] * mat->m[3] * mat->m[13] -
		mat->m[12] * mat->m[1] * mat->m[11] +
		mat->m[12] * mat->m[3] * mat->m[9];

	tmp.m[13] = mat->m[0] * mat->m[9] * mat->m[14] -
		mat->m[0] * mat->m[10] * mat->m[13] -
		mat->m[8] * mat->m[1] * mat->m[14] +
		mat->m[8] * mat->m[2] * mat->m[13] +
		mat->m[12] * mat->m[1] * mat->m[10] -
		mat->m[12] * mat->m[2] * mat->m[9];

	tmp.m[2] = mat->m[1] * mat->m[6] * mat->m[15] -
		mat->m[1] * mat->m[7] * mat->m[14] -
		mat->m[5] * mat->m[2] * mat->m[15] +
		mat->m[5] * mat->m[3] * mat->m[14] +
		mat->m[13] * mat->m[2] * mat->m[7] -
		mat->m[13] * mat->m[3] * mat->m[6];

	tmp.m[6] = -mat->m[0] * mat->m[6] * mat->m[15] +
		mat->m[0] * mat->m[7] * mat->m[14] +
		mat->m[4] * mat->m[2] * mat->m[15] -
		mat->m[4] * mat->m[3] * mat->m[14] -
		mat->m[12] * mat->m[2] * mat->m[7] +
		mat->m[12] * mat->m[3] * mat->m[6];

	tmp.m[10] = mat->m[0] * mat->m[5] * mat->m[15] -
		mat->m[0] * mat->m[7] * mat->m[13] -
		mat->m[4] * mat->m[1] * mat->m[15] +
		mat->m[4] * mat->m[3] * mat->m[13] +
		mat->m[12] * mat->m[1] * mat->m[7] -
		mat->m[12] * mat->m[3] * mat->m[5];

	tmp.m[14] = -mat->m[0] * mat->m[5] * mat->m[14] +
		mat->m[0] * mat->m[6] * mat->m[13] +
		mat->m[4] * mat->m[1] * mat->m[14] -
		mat->m[4] * mat->m[2] * mat->m[13] -
		mat->m[12] * mat->m[1] * mat->m[6] +
		mat->m[12] * mat->m[2] * mat->m[5];

	tmp.m[3] = -mat->m[1] * mat->m[6] * mat->m[11] +
		mat->m[1] * mat->m[7] * mat->m[10] +
		mat->m[5] * mat->m[2] * mat->m[11] -
		mat->m[5] * mat->m[3] * mat->m[10] -
		mat->m[9] * mat->m[2] * mat->m[7] +
		mat->m[9] * mat->m[3] * mat->m[6];

	tmp.m[7] = mat->m[0] * mat->m[6] * mat->m[11] -
		mat->m[0] * mat->m[7] * mat->m[10] -
		mat->m[4] * mat->m[2] * mat->m[11] +
		mat->m[4] * mat->m[3] * mat->m[10] +
		mat->m[8] * mat->m[2] * mat->m[7] -
		mat->m[8] * mat->m[3] * mat->m[6];

	tmp.m[11] = -mat->m[0] * mat->m[5] * mat->m[11] +
		mat->m[0] * mat->m[7] * mat->m[9] +
		mat->m[4] * mat->m[1] * mat->m[11] -
		mat->m[4] * mat->m[3] * mat->m[9] -
		mat->m[8] * mat->m[1] * mat->m[7] +
		mat->m[8] * mat->m[3] * mat->m[5];

	tmp.m[15] = mat->m[0] * mat->m[5] * mat->m[10] -
		mat->m[0] * mat->m[6] * mat->m[9] -
		mat->m[4] * mat->m[1] * mat->m[10] +
		mat->m[4] * mat->m[2] * mat->m[9] +
		mat->m[8] * mat->m[1] * mat->m[6] -
		mat->m[8] * mat->m[2] * mat->m[5];

	det = mat->m[0] * tmp.m[0] + mat->m[1] * tmp.m[4] + mat->m[2] * tmp.m[8] + mat->m[3] * tmp.m[12];

	if (det != 0) {
		det = 1.0f / det;

		for (i = 0; i < 16; i++) {
			out->m[i] = tmp.m[i] * det;
		}
	}
}

void ex_mat4_extract_position(ex_vec3_t* out, const ex_mat4_t* mat) {
	out->x = mat->m[12];
	out->y = mat->m[13];
	out->z = mat->m[14];
}
