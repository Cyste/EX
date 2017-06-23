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
#ifndef EX_VECTOR4_H_
#define EX_VECTOR4_H_

typedef struct ex_vec4_t {
	float x;
	float y;
	float z;
	float w;
} ex_vec4_t;

EX_API void ex_vec4_assign(ex_vec4_t* out, float x, float y, float z, float w);

EX_API void ex_vec4_assign_vec3(ex_vec4_t* out, ex_vec3_t* v, float w);

EX_API void ex_vec4_neg(ex_vec4_t* out, ex_vec4_t* v);

EX_API void ex_vec4_add(ex_vec4_t* out, ex_vec4_t* a, ex_vec4_t* b);

EX_API void ex_vec4_subtract(ex_vec4_t* out, ex_vec4_t* a, ex_vec4_t* b);

EX_API void ex_vec4_multiply(ex_vec4_t* out, ex_vec4_t* a, ex_vec4_t* b);

EX_API void ex_vec4_divide(ex_vec4_t* out, ex_vec4_t* a, ex_vec4_t* b);

EX_API void ex_vec4_add_scalar(ex_vec4_t* out, ex_vec4_t* a, float b);

EX_API void ex_vec4_subtract_scalar(ex_vec4_t* out, ex_vec4_t* a, float b);

EX_API void ex_vec4_multiply_scalar(ex_vec4_t* out, ex_vec4_t* a, float b);

EX_API void ex_vec4_divide_scalar(ex_vec4_t* out, ex_vec4_t* a, float b);

EX_API float ex_vec4_length(ex_vec4_t* v);

EX_API void ex_vec4_normalize(ex_vec4_t* out, ex_vec4_t* v);

EX_API void ex_vec4_direction(ex_vec4_t* out, ex_vec4_t* a, ex_vec4_t* b);

EX_API float ex_vec4_distance(ex_vec4_t* a, ex_vec4_t* b);

EX_API float ex_vec4_dot(ex_vec4_t* a, ex_vec4_t* b);

EX_API void ex_vec4_cross(ex_vec4_t* out, ex_vec4_t* a, ex_vec4_t* b);

#endif