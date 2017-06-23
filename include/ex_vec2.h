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
#ifndef EX_VECTOR2_H_
#define EX_VECTOR2_H_

typedef struct ex_vec2_t {
	float x;
	float y;
} ex_vec2_t;

EX_API void ex_vec2_assign(ex_vec2_t* out, float x, float y);

EX_API void ex_vec2_neg(ex_vec2_t* out, ex_vec2_t* v);

EX_API void ex_vec2_add(ex_vec2_t* out, ex_vec2_t* a, ex_vec2_t* b);

EX_API void ex_vec2_subtract(ex_vec2_t* out, ex_vec2_t* a, ex_vec2_t* b);

EX_API void ex_vec2_multiply(ex_vec2_t* out, ex_vec2_t* a, ex_vec2_t* b);

EX_API void ex_vec2_divide(ex_vec2_t* out, ex_vec2_t* a, ex_vec2_t* b);

EX_API void ex_vec2_add_scalar(ex_vec2_t* out, ex_vec2_t* a, float b);

EX_API void ex_vec2_subtract_scalar(ex_vec2_t* out, ex_vec2_t* a, float b);

EX_API void ex_vec2_multiply_scalar(ex_vec2_t* out, ex_vec2_t* a, float b);

EX_API void ex_vec2_divide_scalar(ex_vec2_t* out, ex_vec2_t* a, float b);

EX_API float ex_vec2_length(ex_vec2_t* v);

EX_API void ex_vec2_normalize(ex_vec2_t* out, ex_vec2_t* v);

EX_API void ex_vec2_direction(ex_vec2_t* out, ex_vec2_t* a, ex_vec2_t* b);

EX_API float ex_vec2_distance(ex_vec2_t* a, ex_vec2_t* b);

EX_API float ex_vec2_dot(ex_vec2_t* a, ex_vec2_t* b);

EX_API float ex_vec2_cross(ex_vec2_t* a, ex_vec2_t* b);

#endif