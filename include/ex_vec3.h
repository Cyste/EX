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
#ifndef EX_VECTOR3_H_
#define EX_VECTOR3_H_

typedef struct ex_vec3_t {
	float x;
	float y;
	float z;
} ex_vec3_t;

EX_API void ex_vec3_assign(ex_vec3_t* out, float x, float y, float z);

EX_API void ex_vec3_neg(ex_vec3_t* out, ex_vec3_t* v);

EX_API void ex_vec3_add(ex_vec3_t* out, ex_vec3_t* a, ex_vec3_t* b);

EX_API void ex_vec3_subtract(ex_vec3_t* out, ex_vec3_t* a, ex_vec3_t* b);

EX_API void ex_vec3_multiply(ex_vec3_t* out, ex_vec3_t* a, ex_vec3_t* b);

EX_API void ex_vec3_divide(ex_vec3_t* out, ex_vec3_t* a, ex_vec3_t* b);

EX_API void ex_vec3_add_scalar(ex_vec3_t* out, ex_vec3_t* a, float b);

EX_API void ex_vec3_subtract_scalar(ex_vec3_t* out, ex_vec3_t* a, float b);

EX_API void ex_vec3_multiply_scalar(ex_vec3_t* out, ex_vec3_t* a, float b);

EX_API void ex_vec3_divide_scalar(ex_vec3_t* out, ex_vec3_t* a, float b);

EX_API float ex_vec3_length(ex_vec3_t* v);

EX_API void ex_vec3_normalize(ex_vec3_t* out, ex_vec3_t* v);

EX_API void ex_vec3_direction(ex_vec3_t* out, ex_vec3_t* a, ex_vec3_t* b);

EX_API float ex_vec3_distance(ex_vec3_t* a, ex_vec3_t* b);

EX_API float ex_vec3_dot(ex_vec3_t* a, ex_vec3_t* b);

EX_API void ex_vec3_cross(ex_vec3_t* out, ex_vec3_t* a, ex_vec3_t* b);


#endif