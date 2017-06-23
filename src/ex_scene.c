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
#include <string.h>

struct ex_scene_t {
	ex_node_t* root;

	ex_node_t* camera;
};

ex_scene_t* ex_scene_create(void) {
	ex_scene_t* scene = (ex_scene_t*)ex_malloc(sizeof(ex_scene_t));

	scene->camera = 0;
	scene->root = ex_node_create("root", NULL);

	return scene;
}

void ex_scene_destroy(ex_scene_t* scene) {
	ex_node_destroy(scene->root);

	ex_free(scene);
}

ex_node_t* ex_scene_add_node(ex_scene_t* scene, const char* name, ex_node_t* parent) {
	return ex_node_create(name, parent ? parent : scene->root);
}

ex_node_t* ex_scene_find_node(ex_scene_t* scene, const char* name) {
	return ex_node_find_child(scene->root, name);
}

void ex_scene_set_main_camera(ex_scene_t* scene, ex_node_t* camera) {
	ex_assert(ex_node_has_component(camera, EX_COMPONENT_CAMERA));

	scene->camera = camera;
}

static
void update_node(ex_node_t* node, float delta_time) {
	unsigned int i, size;

	ex_node_update(node, delta_time);

	for (i = 0, size = ex_node_get_children_count(node); i < size; ++i) {
		update_node(ex_node_get_child(node, i), delta_time);
	}
}

void ex_scene_update(ex_scene_t* scene, float delta_time) {
	update_node(scene->root, delta_time);
}

static
void render_light(ex_node_t* node, ex_renderer_t* renderer) {
	const ex_vec3_t* position = ex_node_get_position(node);
	const ex_vec3_t* color = ex_light_get_color(node);
	float intensity = ex_light_get_intensity(node);

	switch (ex_light_get_type(node)) {
		case EX_LIGHT_DIRECTIONAL: {
			ex_vec3_t direction;
			ex_vec3_assign(&direction, position->x, position->y, position->z);
			ex_vec3_normalize(&direction, &direction);

			ex_renderer_render_directional_light(renderer,
				direction.x, direction.y, direction.z,
				color->x, color->y, color->z,
				intensity);
			break;
		}
		case EX_LIGHT_POINT: {
			ex_renderer_render_point_light(renderer,
				position->x, position->y, position->z,
				color->x, color->y, color->z,
				intensity,
				ex_light_get_radius(node));
			break;
		}
	}
}

static 
void render_node(ex_node_t* node, ex_renderer_t* renderer) {
	unsigned int i, size;

	if (ex_node_has_component(node, EX_COMPONENT_GEOMETRY)) {
		ex_mesh_t* mesh = ex_geometry_get_mesh(node);
		ex_material_t* material = ex_geometry_get_material(node);
		const ex_mat4_t* transform = ex_node_get_transform(node);

		if (mesh) {
			ex_renderer_render_geometry(renderer, mesh, material, transform);
		}
	}

	for (i = 0, size = ex_node_get_children_count(node); i < size; ++i) {
		render_node(ex_node_get_child(node, i), renderer);
	}
}

static
void light_node(ex_node_t* node, ex_renderer_t* renderer) {
	unsigned int i, size;

	if (ex_node_has_component(node, EX_COMPONENT_LIGHT)) {
		render_light(node, renderer);
	}

	for (i = 0, size = ex_node_get_children_count(node); i < size; ++i) {
		light_node(ex_node_get_child(node, i), renderer);
	}
}

void ex_scene_render(ex_scene_t* scene, ex_renderer_t* renderer) {
	if (!scene->camera) {
		return;
	}

	ex_renderer_clear(renderer);

	ex_renderer_begin(renderer, ex_camera_get_view(scene->camera), ex_camera_get_proj(scene->camera));

	ex_renderer_geometry_pass(renderer);

	render_node(scene->root, renderer);

	ex_renderer_light_pass(renderer, 0.4f, 0.4f, 0.4f);

	light_node(scene->root, renderer);

	ex_renderer_present(renderer);
}