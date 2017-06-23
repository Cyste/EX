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

#ifdef EX_OS_WINDOWS

#include <Windows.h>

struct ex_mutex_t {
	CRITICAL_SECTION section;
};

ex_mutex_t* ex_mutex_create(void) {
	ex_mutex_t* mutex = ex_malloc(sizeof(ex_mutex_t));

	InitializeCriticalSection(&mutex->section);

	return mutex;
}

void ex_mutex_destroy(ex_mutex_t* mutex) {
	DeleteCriticalSection(&mutex->section);
	ex_free(mutex);
}

void ex_mutex_lock(ex_mutex_t* mutex) {
	EnterCriticalSection(&mutex->section);
}

void ex_mutex_unlock(ex_mutex_t* mutex) {
	LeaveCriticalSection(&mutex->section);
}

#endif
