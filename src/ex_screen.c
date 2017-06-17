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

typedef struct ex_light_buffer {
	GLuint frame_buffer;

	GLuint acc_texture;
} ex_light_buffer;

typedef struct ex_geometry_buffer {
	GLuint frame_buffer;

	GLuint diffuse_texture;
	GLuint normals_texture;
	GLuint depth_texture;
} ex_geometry_buffer;

struct ex_screen {
	ex_geometry_buffer geometry_buffer;
	ex_light_buffer light_buffer;
};

static
int init_light_buffer(ex_light_buffer* light_buffer, int width, int height, unsigned int flags) {
	glGenFramebuffers(1, &light_buffer->frame_buffer);
	glBindFramebuffer(GL_FRAMEBUFFER, light_buffer->frame_buffer);

	glGenTextures(1, &light_buffer->acc_texture);
	glBindTexture(GL_TEXTURE_2D, light_buffer->acc_texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, light_buffer->acc_texture, 0);

	GLenum draw_buffer = GL_COLOR_ATTACHMENT0;
	glDrawBuffers(1, &draw_buffer);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		return 0;
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	return 1;
}

static
int init_geometry_buffer(ex_geometry_buffer* geometry_buffer, int width, int height, unsigned int flags) {
	glGenFramebuffers(1, &geometry_buffer->frame_buffer);
	glBindFramebuffer(GL_FRAMEBUFFER, geometry_buffer->frame_buffer);

	glGenTextures(1, &geometry_buffer->diffuse_texture);
	glBindTexture(GL_TEXTURE_2D, geometry_buffer->diffuse_texture);
	glTexImage2D(GL_TEXTURE_2D, 0, (flags & EX_RENDERER_HDR) ? GL_RGBA16F : GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, geometry_buffer->diffuse_texture, 0);

	glGenTextures(1, &geometry_buffer->normals_texture);
	glBindTexture(GL_TEXTURE_2D, geometry_buffer->normals_texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_FLOAT, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, geometry_buffer->normals_texture, 0);

	glGenTextures(1, &geometry_buffer->depth_texture);
	glBindTexture(GL_TEXTURE_2D, geometry_buffer->depth_texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, width, height, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, geometry_buffer->depth_texture, 0);

	GLenum draw_buffers[2] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1 };
	glDrawBuffers(2, draw_buffers);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		return 0;
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	return 1;
}

ex_screen* ex_screen_create(int width, int height, unsigned int flags) {
	ex_screen* screen = (ex_screen*)malloc(sizeof(ex_screen));

	init_geometry_buffer(&screen->geometry_buffer, width, height, flags);
	init_light_buffer(&screen->light_buffer, width, height, flags);

	return screen;
}

void ex_screen_destroy(ex_screen* screen) {
	glDeleteFramebuffers(1, &screen->geometry_buffer.frame_buffer);
	glDeleteFramebuffers(1, &screen->light_buffer.frame_buffer);

	glDeleteTextures(1, &screen->geometry_buffer.diffuse_texture);
	glDeleteTextures(1, &screen->geometry_buffer.normals_texture);
	glDeleteTextures(1, &screen->geometry_buffer.depth_texture);

	glDeleteTextures(1, &screen->light_buffer.acc_texture);

	free(screen);
}

void ex_screen_bind_geometry_buffer(ex_screen* screen) {
	glBindFramebuffer(GL_FRAMEBUFFER, screen->geometry_buffer.frame_buffer);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void ex_screen_bind_light_buffer(ex_screen* screen) {
	glBindFramebuffer(GL_FRAMEBUFFER, screen->light_buffer.frame_buffer);
}

void ex_screen_send_to_light_pass(ex_screen* screen, ex_shader* shader) {
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, screen->geometry_buffer.diffuse_texture);
	glUniform1i(ex_shader_get_uniform(shader, "color_map"), 1);

	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, screen->geometry_buffer.normals_texture);
	glUniform1i(ex_shader_get_uniform(shader, "normal_map"), 2);

	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, screen->geometry_buffer.depth_texture);
	glUniform1i(ex_shader_get_uniform(shader, "depth_map"), 3);
}

void ex_screen_send_to_present(ex_screen* screen, ex_shader* shader) {
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, screen->geometry_buffer.diffuse_texture);
	glUniform1i(ex_shader_get_uniform(shader, "color_map"), 1);

	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, screen->light_buffer.acc_texture);
	glUniform1i(ex_shader_get_uniform(shader, "light_map"), 2);
}