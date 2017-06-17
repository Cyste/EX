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

struct ex_renderer {
	ex_screen* screen;

	ex_mesh* quad;
	ex_mesh* sphere;

	ex_shader* shader;
	ex_shader* point_light;
	ex_shader* geometry;
	ex_shader* present;

	ex_mat4 proj_view;
	ex_mat4 inv_proj_view;
};

ex_renderer* ex_renderer_create(int width, int height, unsigned int flags) {
	ex_renderer* renderer = (ex_renderer*)malloc(sizeof(ex_renderer));

	renderer->screen = ex_screen_create(width, height, flags);
	renderer->quad = ex_mesh_create_fullscreen_quad();
	renderer->sphere = ex_mesh_create_sphere(1.0f, 32, 32);

	renderer->shader = ex_shader_load("../data/internal/shaders/clear.glsl");
	renderer->point_light = ex_shader_load("../data/internal/shaders/point_light.glsl");
	renderer->geometry = ex_shader_load("../data/internal/shaders/geometry.glsl");
	renderer->present = ex_shader_load("../data/internal/shaders/present.glsl");

	glEnable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);

	return renderer;
}

void ex_renderer_destroy(ex_renderer* renderer) {
	ex_shader_destroy(renderer->present);
	ex_shader_destroy(renderer->geometry);
	ex_shader_destroy(renderer->point_light);
	ex_shader_destroy(renderer->shader);

	ex_mesh_destroy(renderer->sphere);
	ex_mesh_destroy(renderer->quad);

	ex_screen_destroy(renderer->screen);

	free(renderer);
}

void ex_renderer_clear(ex_renderer* renderer) {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void ex_renderer_begin(ex_renderer* renderer, ex_mat4* view, ex_mat4* proj) {
	ex_mat4_multiply(&renderer->proj_view, proj, view);
	ex_mat4_inverse(&renderer->inv_proj_view, &renderer->proj_view);

	ex_vec3 camera_position;
	ex_mat4_extract_position(&camera_position, view);
	ex_vec3_neg(&camera_position, &camera_position);

	ex_shader_use(renderer->point_light);
	glUniformMatrix4fv(ex_shader_get_uniform(renderer->point_light, "proj_view"), 1, GL_FALSE, renderer->proj_view.m);
	glUniformMatrix4fv(ex_shader_get_uniform(renderer->point_light, "inv_proj_view"), 1, GL_FALSE, renderer->inv_proj_view.m);
	glUniform3f(ex_shader_get_uniform(renderer->point_light, "camera_position"), camera_position.x, camera_position.y, camera_position.z);
}

void ex_renderer_geometry_pass(ex_renderer* renderer) {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	ex_screen_bind_geometry_buffer(renderer->screen);

	ex_shader_use(renderer->geometry);
	glUniformMatrix4fv(ex_shader_get_uniform(renderer->geometry, "proj_view"), 1, GL_FALSE, renderer->proj_view.m);

	glDepthMask(GL_TRUE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glDisable(GL_BLEND);
}

void ex_renderer_render_geometry(ex_renderer* renderer, ex_mesh* mesh, ex_material* material, ex_mat4* world) {
	unsigned int bitfield = 0;

	if (material) {
		ex_texture* diffuse_map = ex_material_get_diffuse_map(material);
		ex_texture* normal_map = ex_material_get_normal_map(material);
		ex_vec3 diffuse;
		ex_material_get_diffuse(material, &diffuse);

		if (diffuse_map) {
			bitfield |= 1;

			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, ex_texture_get_id(diffuse_map));
			glUniform1i(ex_shader_get_uniform(renderer->geometry, "color_map"), 1);
		}

		if (normal_map) {
			bitfield |= 2;

			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, ex_texture_get_id(diffuse_map));
			glUniform1i(ex_shader_get_uniform(renderer->geometry, "normal_map"), 1);
		}

		glUniform3f(ex_shader_get_uniform(renderer->geometry, "diffuse"), diffuse.x, diffuse.y, diffuse.z);
		glUniform1f(ex_shader_get_uniform(renderer->geometry, "roughness"), ex_material_get_roughness(material));
		glUniform1f(ex_shader_get_uniform(renderer->geometry, "metallic"), ex_material_get_metallic(material));
	} else {
		glUniform3f(ex_shader_get_uniform(renderer->geometry, "diffuse"), 1.0f, 1.0f, 1.0f);
		glUniform1f(ex_shader_get_uniform(renderer->geometry, "roughness"), 0.8f);
		glUniform1f(ex_shader_get_uniform(renderer->geometry, "metallic"), 0.2f);
	}

	glUniform1i(ex_shader_get_uniform(renderer->geometry, "bitfield"), bitfield);
	glUniformMatrix4fv(ex_shader_get_uniform(renderer->geometry, "world"), 1, GL_FALSE, world->m);

	ex_mesh_render(mesh);
}

void ex_renderer_light_pass(ex_renderer* renderer, float ambient_r, float ambient_g, float ambient_b) {
	ex_shader_use(NULL);

	ex_screen_bind_light_buffer(renderer->screen);

	glEnable(GL_BLEND);
	glBlendEquation(GL_FUNC_ADD);
	glBlendFunc(GL_ONE, GL_ONE);

	glDepthMask(GL_FALSE);
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	glCullFace(GL_FRONT);

	glClearColor(ambient_r, ambient_g, ambient_b, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	ex_shader_use(renderer->point_light);

	ex_screen_send_to_light_pass(renderer->screen, renderer->point_light);
}

void ex_renderer_render_point_light(ex_renderer* renderer, float x, float y, float z, float r, float g, float b, float intensity, float radius) {
	ex_shader_use(renderer->point_light);
	
	float world[16] = {
		radius, 0.0f, 0.0f, 0.0f,
		0.0f, radius, 0.0f, 0.0f,
		0.0f, 0.0f, radius, 0.0f,
		x, y, z, 1.0f
	};

	r *= intensity;
	g *= intensity;
	b *= intensity;

	glUniform3f(ex_shader_get_uniform(renderer->point_light, "light_color"), r, g, b);
	glUniform1f(ex_shader_get_uniform(renderer->point_light, "light_radius"), radius);
	glUniform3f(ex_shader_get_uniform(renderer->point_light, "light_pos"), x, y, z);
	glUniformMatrix4fv(ex_shader_get_uniform(renderer->point_light, "world"), 1, GL_FALSE, world);

	ex_mesh_render(renderer->sphere);
}

void ex_renderer_present(ex_renderer* renderer) {
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);
	glDepthMask(GL_TRUE);
	glCullFace(GL_BACK);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	ex_shader_use(renderer->present);

	ex_screen_send_to_present(renderer->screen, renderer->present);

	ex_mesh_render(renderer->quad);

	ex_shader_use(NULL);
}

/* Queen - Too Much Love Will Kill You */