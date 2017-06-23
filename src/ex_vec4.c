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

void ex_vec4_assign(ex_vec4_t* out, float x, float y, float z, float w) {
	out->x = x;
	out->y = y;
	out->z = z;
	out->w = w;
}

void ex_vec4_assign_vec3(ex_vec4_t* out, ex_vec3_t* v, float w) {
	out->x = v->x;
	out->y = v->y;
	out->z = v->z; 
	out->w = w;
}

void ex_vec4_neg(ex_vec4_t* out, ex_vec4_t* v) {
	out->x = -v->x;
	out->y = -v->y;
	out->z = -v->z;
	out->w = -v->w;
}

void ex_vec4_add(ex_vec4_t* out, ex_vec4_t* a, ex_vec4_t* b) {
	out->x = a->x + b->x;
	out->y = a->y + b->y;
	out->z = a->z + b->z;
	out->w = a->w + b->w;
}

void ex_vec4_subtract(ex_vec4_t* out, ex_vec4_t* a, ex_vec4_t* b) {
	out->x = a->x - b->x;
	out->y = a->y - b->y;
	out->z = a->z - b->z;
	out->w = a->w - b->w;
}

void ex_vec4_multiply(ex_vec4_t* out, ex_vec4_t* a, ex_vec4_t* b) {
	out->x = a->x * b->x;
	out->y = a->y * b->y;
	out->z = a->z * b->z;
	out->w = a->w * b->w;
}

void ex_vec4_divide(ex_vec4_t* out, ex_vec4_t* a, ex_vec4_t* b) {
	out->x = a->x / b->x;
	out->y = a->y / b->y;
	out->z = a->z / b->z;
	out->w = a->w / b->w;
}

void ex_vec4_add_scalar(ex_vec4_t* out, ex_vec4_t* a, float b) {
	out->x = a->x + b;
	out->y = a->y + b;
	out->z = a->z + b;
	out->w = a->w + b;
}

void ex_vec4_subtract_scalar(ex_vec4_t* out, ex_vec4_t* a, float b) {
	out->x = a->x - b;
	out->y = a->y - b;
	out->z = a->z - b;
	out->w = a->w - b;
}

void ex_vec4_multiply_scalar(ex_vec4_t* out, ex_vec4_t* a, float b) {
	out->x = a->x * b;
	out->y = a->y * b;
	out->z = a->z * b;
	out->w = a->w * b;
}

void ex_vec4_divide_scalar(ex_vec4_t* out, ex_vec4_t* a, float b) {
	out->x = a->x / b;
	out->y = a->y / b;
	out->z = a->z / b;
	out->w = a->w / b;
}

float ex_vec4_length(ex_vec4_t* v) {
	return (float)sqrt(v->x * v->x + v->y * v->y + v->z * v->z + v->w * v->w);
}

void ex_vec4_normalize(ex_vec4_t* out, ex_vec4_t* v) {
	float length = (float)1.0 / ex_vec4_length(v);

	out->x = v->x * length;
	out->y = v->y * length;
	out->z = v->z * length;
	out->w = v->w * length;
}

void ex_vec4_direction(ex_vec4_t* out, ex_vec4_t* a, ex_vec4_t* b) {
	ex_vec4_subtract(out, b, a);
	ex_vec4_normalize(out, out);
}

float ex_vec4_distance(ex_vec4_t* a, ex_vec4_t* b) {
	ex_vec4_t out;
	ex_vec4_subtract(&out, b, a);
	return ex_vec4_length(&out);
}

float ex_vec4_dot(ex_vec4_t* a, ex_vec4_t* b) {
	return a->x * b->x + a->y * b->y + a->z * b->z + a->w * b->w;
}

void ex_vec4_cross(ex_vec4_t* out, ex_vec4_t* a, ex_vec4_t* b) {
	out->x = a->y * b->z - a->z * b->y;
	out->y = a->z * b->x - a->x * b->z;
	out->z = a->x * b->y - a->y * b->x;
}