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

#include <stdlib.h>

void ex_vector_init(ex_vector_t* vector, unsigned int capacity) {
	vector->capacity = capacity;
	vector->size     = 0;
	vector->data     = (capacity > 0) ? (void**)ex_malloc(capacity * sizeof(void*)) : NULL;
}

void ex_vector_release(ex_vector_t* vector) {
	ex_free(vector->data);
}

void ex_vector_push(ex_vector_t* vector, void* object) {
	while (vector->size >= vector->capacity) {
		vector->capacity = (vector->capacity > 0) ? (vector->capacity << 1) : 1;
		vector->data = (void**)ex_realloc(vector->data, vector->capacity * sizeof(void*));
	}

	vector->data[vector->size++] = object;
}

void* ex_vector_pop(ex_vector_t* vector) {
	ex_assert(vector->size > 0);
		
	return vector->data[--vector->size];
}

void ex_vector_flush(ex_vector_t* vector) {
	if (vector->capacity > vector->size) {
		vector->capacity = vector->size;
		vector->data = (void**)ex_realloc(vector->data, vector->capacity * sizeof(void*));
	}
}