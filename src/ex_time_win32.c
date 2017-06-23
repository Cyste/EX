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

static
int start_time = 0;

static LARGE_INTEGER start_ticks;
static LARGE_INTEGER ticks_per_second;

unsigned int ex_get_time(void) {
	LARGE_INTEGER performance;

	if (start_time == 0) {
		QueryPerformanceFrequency(&ticks_per_second);
		QueryPerformanceCounter(&start_ticks);
		start_time = 1;
	}

	QueryPerformanceCounter(&performance);

	performance.QuadPart -= start_ticks.QuadPart;
	performance.QuadPart *= 1000;
	performance.QuadPart /= ticks_per_second.QuadPart;

	return (unsigned int)performance.QuadPart;
}

void ex_sleep(unsigned int ms) {
	Sleep(ms);
}

#endif