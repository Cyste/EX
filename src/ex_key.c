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

#include <string.h>

static char keys[EX_KEY_COUNT];

void ex_keyboard_init(void) {
	memset(keys, 0, sizeof(keys));
}

int ex_keyboard_get_state(int key) {
	ex_assert(key >= 0 && key < EX_KEY_COUNT);

	return keys[key];
}

void ex_keyboard_set_state(int key, int state) {
	ex_assert(key >= 0 && key < EX_KEY_COUNT);

	keys[key] = (char)state;
}