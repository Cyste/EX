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

#include <stdio.h>
#include <ctype.h>
#include <string.h>

typedef struct ex_key_t {
	char* name;
	char* value;
} ex_key_t;

typedef struct ex_section_t {
	char* name;
	ex_vector_t keys;
} ex_section_t;

struct ex_config_t {
	ex_vector_t sections;
};

static
void trim(char* text) {
	int i;

	while (text[0] == ' ') {
		for (i = 0; text[i]; ++i) {
			text[i] = text[i + 1];
		}
	}

	i = 0;
	while (text[i] != ' ') {
		++i;
	}

	text[i] = '\0';
}

ex_config_t* ex_config_load(const char* filename) {
	char buffer[512];

	ex_config_t* config = (ex_config_t*)ex_malloc(sizeof(ex_config_t));

	FILE* file = fopen(filename, "rb");
	ex_assert(file);

	ex_vector_init(&config->sections, 0);

	ex_key_t*     key     = NULL;
	ex_section_t* section = NULL;

	buffer[0] = '\0';

	int c, i = 0;
	while ((c = fgetc(file)) != EOF) {
		if (c == '[') {
			section = (ex_section_t*)ex_malloc(sizeof(ex_section_t));
			section->name = NULL;
			ex_vector_init(&section->keys, 0);
		} else if (c == ']') {
			trim(buffer);

			ex_assert(strlen(buffer) > 0);

			section->name = (char*)ex_malloc(strlen(buffer) + 1);
			strcpy(section->name, buffer);
		} else if (c == '=') {
			trim(buffer);

			ex_assert(strlen(buffer) > 0);

			key = (ex_key_t*)ex_malloc(sizeof(ex_key_t));
			key->name = (char*)ex_malloc(strlen(buffer) + 1);
			strcpy(key->name, buffer);
		} else if (c == '\n') {
			if (key) {
				ex_assert(section);

				trim(buffer);

				ex_assert(strlen(buffer) > 0);

				key->value = (char*)ex_malloc(strlen(buffer) + 1);
				strcpy(key->value, buffer);

				ex_vector_push(&section->keys, key);

				key = NULL;
			}
		} else {
			buffer[i++] = tolower(c);
		}
	}

	if (key) {
		ex_assert(section);

		trim(buffer);

		ex_assert(strlen(buffer) > 0);

		key->value = (char*)ex_malloc(strlen(buffer) + 1);
		strcpy(key->value, buffer);

		ex_vector_push(&section->keys, key);

		key = NULL;
	}

	fclose(file);
	return config;
}

void ex_config_destroy(ex_config_t* config) {
	unsigned int i, j;
	for (i = 0; i < ex_vector_size(&config->sections); ++i) {
		ex_section_t* section = (ex_section_t*)ex_vector_at(&config->sections, i);
		for (j = 0; j < ex_vector_size(&section->keys); ++j) {
			ex_key_t* key = (ex_key_t*)ex_vector_at(&section->keys, j);
			ex_free(key->name);
			ex_free(key->value);
			ex_free(key);
		}
		ex_vector_release(&section->keys);
	}
	ex_vector_release(&config->sections);

	ex_free(config);
}

const char* ex_config_get(ex_config_t* config, const char* sectionname, const char* keyname) {
	unsigned int i, j;
	for (i = 0; i < ex_vector_size(&config->sections); ++i) {
		ex_section_t* section = (ex_section_t*)ex_vector_at(&config->sections, i);
		if (strcmp(section->name, sectionname) == 0) {
			for (j = 0; j < ex_vector_size(&section->keys); ++j) {
				ex_key_t* key = (ex_key_t*)ex_vector_at(&section->keys, j);

				if (strcmp(key->name, keyname) == 0) {
					return key->value;
				}
			}
		}
	}
	return NULL;
}