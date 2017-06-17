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

void ex_vec2_assign(ex_vec2* out, float x, float y) {
	out->x = x;
	out->y = y;
}

void ex_vec2_neg(ex_vec2* out, ex_vec2* v) {
	out->x = -v->x;
	out->y = -v->y;
}

void ex_vec2_add(ex_vec2* out, ex_vec2* a, ex_vec2* b) {
	out->x = a->x + b->x;
	out->y = a->y + b->y;
}

void ex_vec2_subtract(ex_vec2* out, ex_vec2* a, ex_vec2* b) {
	out->x = a->x - b->x;
	out->y = a->y - b->y;
}

void ex_vec2_multiply(ex_vec2* out, ex_vec2* a, ex_vec2* b) {
	out->x = a->x * b->x;
	out->y = a->y * b->y;
}

void ex_vec2_divide(ex_vec2* out, ex_vec2* a, ex_vec2* b) {
	out->x = a->x / b->x;
	out->y = a->y / b->y;
}

void ex_vec2_add_scalar(ex_vec2* out, ex_vec2* a, float b) {
	out->x = a->x + b;
	out->y = a->y + b;
}

void ex_vec2_subtract_scalar(ex_vec2* out, ex_vec2* a, float b) {
	out->x = a->x - b;
	out->y = a->y - b;
}

void ex_vec2_multiply_scalar(ex_vec2* out, ex_vec2* a, float b) {
	out->x = a->x * b;
	out->y = a->y * b;
}

void ex_vec2_divide_scalar(ex_vec2* out, ex_vec2* a, float b) {
	out->x = a->x / b;
	out->y = a->y / b;
}

float ex_vec2_length(ex_vec2* v) {
	return (float)sqrt(v->x * v->x + v->y * v->y);
}

void ex_vec2_normalize(ex_vec2* out, ex_vec2* v) {
	float length = (float)1.0 / ex_vec2_length(v);

	out->x = v->x * length;
	out->y = v->y * length;
}

void ex_vec2_direction(ex_vec2* out, ex_vec2* a, ex_vec2* b) {
	ex_vec2_subtract(out, b, a);
	ex_vec2_normalize(out, out);
}

float ex_vec2_distance(ex_vec2* a, ex_vec2* b) {
	ex_vec2 out;
	ex_vec2_subtract(&out, b, a);
	return ex_vec2_length(&out);
}

float ex_vec2_dot(ex_vec2* a, ex_vec2* b) {
	return a->x * b->x + a->y * b->y;
}

float ex_vec2_cross(ex_vec2* a, ex_vec2* b) {
	return a->x * b->y - a->y * b->x;
}