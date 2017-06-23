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
#ifndef EX_VECTOR_H_
#define EX_VECTOR_H_

typedef struct ex_vector_t {
	unsigned int capacity;
	unsigned int size;
	void** data;
} ex_vector_t;

EX_API void ex_vector_init(ex_vector_t* vector, unsigned int capacity);

EX_API void ex_vector_release(ex_vector_t* vector);

EX_API void ex_vector_push(ex_vector_t* vector, void* object);

EX_API void* ex_vector_pop(ex_vector_t* vector);

EX_API void ex_vector_flush(ex_vector_t* vector);

#define ex_vector_empty(vector) ((vector)->size == 0)

#define ex_vector_clear(vector) ((vector)->size = 0)

#define ex_vector_begin(vector) ((vector)->data)

#define ex_vector_end(vector) ((vector)->data + (vector)->size)

#define ex_vector_at(vector, index) (ex_assert(index < (vector)->size), (vector)->data[index])

#define ex_vector_size(vector) ((vector)->size)

#define ex_vector_capacity(vector) ((vector)->capacity)

#endif