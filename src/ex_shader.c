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
#include <stdio.h>
#include <string.h>

#define GLEW_STATIC
#include "gl/glew.h"

#define EX_SHADER_VERTEX   (1 << 0)
#define EX_SHADER_FRAGMENT (1 << 1)
#define EX_SHADER_GEOMETRY (1 << 2)

struct ex_shader_t {
	unsigned int id;
};

ex_shader_t* ex_shader_compile(const char* code) {
	ex_shader_t* shader;
	unsigned int id;
	unsigned int code_size = strlen(code);


	const char* parts[3];

	unsigned int flags = 0;
	if (code[0] == '1') flags |= EX_SHADER_VERTEX;
	if (code[1] == '1') flags |= EX_SHADER_FRAGMENT;
	if (code[2] == '1') flags |= EX_SHADER_GEOMETRY;

	if (flags == 0) {
		return NULL;
	}

	parts[0] = "#version 330 core\n";
	parts[2] = &code[3];

	GLuint vertex = 0,
		fragment = 0,
		geometry = 0;

	GLint success;

#ifdef _DEBUG
	GLchar info[512];
#endif

	if (flags & EX_SHADER_VERTEX) {
		parts[1] = "#define VERTEX_PROGRAM\n";

		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 3, parts, 0);
		glCompileShader(vertex);
		glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
		if (!success) {
#ifdef _DEBUG
			glGetShaderInfoLog(vertex, sizeof(info), 0, info);
			printf("%s\n", info);
#endif
			glDeleteShader(vertex);
			return NULL;
		}
	}

	if (flags & EX_SHADER_FRAGMENT) {
		parts[1] = "#define PIXEL_PROGRAM\n";

		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 3, parts, 0);
		glCompileShader(fragment);
		glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
		if (!success) {
#ifdef _DEBUG
			glGetShaderInfoLog(fragment, sizeof(info), 0, info);
			printf("%s\n", info);
#endif
			glDeleteShader(vertex);
			glDeleteShader(fragment);
			return NULL;
		}
	}

	if (flags & EX_SHADER_GEOMETRY) {
		parts[1] = "#define GEOMETRY_PROGRAM\n";

		geometry = glCreateShader(GL_GEOMETRY_SHADER);
		glShaderSource(geometry, 3, parts, 0);
		glCompileShader(geometry);
		glGetShaderiv(geometry, GL_COMPILE_STATUS, &success);
		if (!success)
		{
#ifdef _DEBUG
			glGetShaderInfoLog(geometry, sizeof(info), 0, info);
			printf("%s\n", info);
#endif
			glDeleteShader(vertex);
			glDeleteShader(fragment);
			glDeleteShader(geometry);
			return NULL;
		}
	}

	id = glCreateProgram();
	glAttachShader(id, vertex);
	glAttachShader(id, fragment);
	glLinkProgram(id);
	glGetProgramiv(id, GL_LINK_STATUS, &success);
	if (!success) {
#ifdef _DEBUG
		glGetProgramInfoLog(id, sizeof(info), 0, info);
		printf("%s\n", info);
#endif
		glDeleteShader(vertex);
		glDeleteShader(fragment);
		glDeleteShader(geometry);
		glDeleteProgram(id);
		return NULL;
	}

	glDeleteShader(vertex);
	glDeleteShader(fragment);
	glDeleteShader(geometry);

	shader = (ex_shader_t*)ex_malloc(sizeof(ex_shader_t));
	shader->id = id;
	return shader;
}

ex_shader_t* ex_shader_load(const char* file_name) {
	FILE* file = fopen(file_name, "rb");
	if (file) {
		fseek(file, 0, SEEK_END);
		unsigned int length = ftell(file);
		fseek(file, 0, SEEK_SET);

		char* buffer = (char*)ex_malloc(length + 1);
		fread(buffer, 1, length, file);
		buffer[length] = 0;

		fclose(file);

		ex_shader_t* shader = ex_shader_compile(buffer);
		ex_free(buffer);
		return shader;
	}
	return NULL;
}

void ex_shader_destroy(ex_shader_t* shader) {
	glDeleteProgram(shader->id);

	ex_free(shader);
}

unsigned int ex_shader_get_id(ex_shader_t* shader) {
	return shader->id;
}

void ex_shader_use(ex_shader_t* shader) {
	glUseProgram(shader ? shader->id : 0);
}

int ex_shader_get_uniform(ex_shader_t* shader, const char* name) {
	return glGetUniformLocation(shader->id, name);
}