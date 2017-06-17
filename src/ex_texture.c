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

#define GLEW_STATIC
#include "gl/glew.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

struct ex_texture {
	unsigned int id;
	int width;
	int height;
	int mipmaps;
};

static GLint _internalformats[4] = { GL_R8, GL_RG8, GL_RGB8, GL_RGBA8 };
static GLenum _formats[4] = { GL_LUMINANCE, GL_LUMINANCE_ALPHA, GL_RG, GL_RGB };

ex_texture* ex_texture_create(void* data, int width, int height, int components) {
	ex_assert(components >= 1 && components <= 4);
	ex_texture* texture = (ex_texture*)malloc(sizeof(ex_texture));

	texture->width = width;
	texture->height = height;
	texture->mipmaps = 0;

	glGenTextures(1, &texture->id);
	glBindTexture(GL_TEXTURE_2D, texture->id);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, _internalformats[components], width, height, 0, _formats[components], GL_UNSIGNED_BYTE, data);

	glBindTexture(GL_TEXTURE_2D, 0);
	return texture;
}

ex_texture* ex_texture_load(const char* file_name) {
	ex_texture* texture;
	stbi_uc* data;
	int width, height, components;

	data = stbi_load(file_name, &width, &height, &components, 4);
	if (!data) {
		return NULL;
	}

	texture = ex_texture_create(data, width, height, 4);
	stbi_image_free(data);
	return texture;
}

void ex_texture_destroy(ex_texture* texture) {
	glDeleteTextures(1, &texture->id);
	free(texture);
}

void ex_texture_generate_mipmaps(ex_texture* texture) {
	if (!texture->mipmaps) {
		glBindTexture(GL_TEXTURE_2D, texture->id);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

		glGenerateMipmap(GL_TEXTURE_2D);

		glBindTexture(GL_TEXTURE_2D, 0);
		texture->mipmaps = 1;
	}
}


unsigned int ex_texture_get_id(ex_texture* texture) {
	return texture->id;
}

int ex_texture_get_width(ex_texture* texture) {
	return texture->width;
}

int ex_texture_get_height(ex_texture* texture) {
	return texture->height;
}