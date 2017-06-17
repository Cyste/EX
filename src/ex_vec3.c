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

void ex_vec3_assign(ex_vec3* out, float x, float y, float z) {
	out->x = x;
	out->y = y;
	out->z = z;
}

void ex_vec3_neg(ex_vec3* out, ex_vec3* v) {
	out->x = -v->x;
	out->y = -v->y;
	out->z = -v->z;
}

void ex_vec3_add(ex_vec3* out, ex_vec3* a, ex_vec3* b) {
	out->x = a->x + b->x;
	out->y = a->y + b->y;
	out->z = a->z + b->z;
}

void ex_vec3_subtract(ex_vec3* out, ex_vec3* a, ex_vec3* b) {
	out->x = a->x - b->x;
	out->y = a->y - b->y;
	out->z = a->z - b->z;
}

void ex_vec3_multiply(ex_vec3* out, ex_vec3* a, ex_vec3* b) {
	out->x = a->x * b->x;
	out->y = a->y * b->y;
	out->z = a->z * b->z;
}

void ex_vec3_divide(ex_vec3* out, ex_vec3* a, ex_vec3* b) {
	out->x = a->x / b->x;
	out->y = a->y / b->y;
	out->z = a->z / b->z;
}

void ex_vec3_add_scalar(ex_vec3* out, ex_vec3* a, float b) {
	out->x = a->x + b;
	out->y = a->y + b;
	out->z = a->z + b;
}

void ex_vec3_subtract_scalar(ex_vec3* out, ex_vec3* a, float b) {
	out->x = a->x - b;
	out->y = a->y - b;
	out->z = a->z - b;
}

void ex_vec3_multiply_scalar(ex_vec3* out, ex_vec3* a, float b) {
	out->x = a->x * b;
	out->y = a->y * b;
	out->z = a->z * b;
}

void ex_vec3_divide_scalar(ex_vec3* out, ex_vec3* a, float b) {
	out->x = a->x / b;
	out->y = a->y / b;
	out->z = a->z / b;
}

float ex_vec3_length(ex_vec3* v) {
	return (float)sqrt(v->x * v->x + v->y * v->y + v->z * v->z);
}

void ex_vec3_normalize(ex_vec3* out, ex_vec3* v) {
	float length = (float)1.0 / ex_vec3_length(v);

	out->x = v->x * length;
	out->y = v->y * length;
	out->z = v->z * length;
}

void ex_vec3_direction(ex_vec3* out, ex_vec3* a, ex_vec3* b) {
	ex_vec3_subtract(out, b, a);
	ex_vec3_normalize(out, out);
}

float ex_vec3_distance(ex_vec3* a, ex_vec3* b) {
	ex_vec3 out;
	ex_vec3_subtract(&out, b, a);
	return ex_vec3_length(&out);
}

float ex_vec3_dot(ex_vec3* a, ex_vec3* b) {
	return a->x * b->x + a->y * b->y + a->z * b->z;
}

void ex_vec3_cross(ex_vec3* out, ex_vec3* a, ex_vec3* b) {
	out->x = a->y * b->z - a->z * b->y;
	out->y = a->z * b->x - a->x * b->z;
	out->z = a->x * b->y - a->y * b->x;
}