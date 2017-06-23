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

typedef struct ex_camera_t {
	int type;

	ex_mat4_t view;
	ex_mat4_t proj;

	union {
		struct {
			float fov;
			float aspect;
			float near;
			float far;
		} perspective;

		struct {
			float left;
			float right;
			float top;
			float bottom;
			float near;
			float far;
		} orthogonal;
	};
} ex_camera_t;

typedef struct ex_geometry_t {
	ex_mesh_t* mesh;
	ex_material_t* material;
} ex_geometry_t;

typedef struct ex_light_t {
	int type;

	ex_vec3_t color;
	float intensity;

	union {
		struct {
			float radius;
		} point;

		struct {
			ex_vec3_t direction;
		} directional;
	};
} ex_light_t;

struct ex_node_t {
	char* name;
	int type;

	ex_vec3_t position;
	ex_vec3_t rotation;
	ex_vec3_t scale;
	ex_mat4_t transform;

	int need_update;

	ex_camera_t*   camera;
	ex_geometry_t* geometry;
	ex_light_t*    light;

	ex_node_t*  parent;
	ex_vector_t children;
};

ex_node_t* ex_node_create(const char* name, ex_node_t* parent) {
	ex_node_t* node = (ex_node_t*)ex_malloc(sizeof(ex_node_t));

	if (name) {
		unsigned int name_length = strlen(name);
		node->name = (char*)ex_malloc(name_length + 1);
		strcpy(node->name, name);
	} else {
		node->name = NULL;
	}

	ex_vec3_assign(&node->position, 0.0f, 0.0f, 0.0f);
	ex_vec3_assign(&node->rotation, 0.0f, 0.0f, 0.0f);
	ex_vec3_assign(&node->scale, 1.0f, 1.0f, 1.0f);
	ex_mat4_identity(&node->transform);

	node->need_update = 1;

	node->camera   = NULL;
	node->geometry = NULL;
	node->light    = NULL;

	node->parent = parent;
	ex_vector_init(&node->children, 0);

	if (node->parent) {
		ex_vector_push(&node->parent->children, node);
	}

	return node;
}

void ex_node_destroy(ex_node_t* node) {
	unsigned int i;
	for (i = 0; i < ex_vector_size(&node->children); ++i) {
		ex_node_destroy(ex_node_get_child(node, i));
	}

	ex_vector_release(&node->children);

	ex_free(node->camera);
	ex_free(node->geometry);
	ex_free(node->light);

	ex_free(node->name);

	ex_free(node);
}


ex_node_t* ex_node_get_parent(ex_node_t* node) {
	return node->parent;
}

unsigned int ex_node_get_children_count(ex_node_t* node) {
	return ex_vector_size(&node->children);
}

ex_node_t* ex_node_get_child(ex_node_t* node, unsigned int index) {
	return (ex_node_t*)ex_vector_at(&node->children, index);
}

ex_node_t* ex_node_find_child(ex_node_t* node, const char* name) {
	unsigned int i;
	ex_node_t* child;

	for (i = 0; i < ex_vector_size(&node->children); ++i) {
		child = ex_node_get_child(node, i);

		if (strcmp(child->name, name) == 0) {
			return child;
		}

		child = ex_node_find_child(child, name);
		if (child) {
			return child;
		}
	}

	return NULL;
}

int ex_node_add_component(ex_node_t* node, int component) {
	switch (component) {
	case EX_COMPONENT_CAMERA:
		if (!node->camera) {
			node->camera = (ex_camera_t*)ex_malloc(sizeof(ex_camera_t));
			node->camera->type = EX_CAMERA_PERSPECTIVE;
			node->camera->perspective.near = 1.0f;
			node->camera->perspective.far = 100.0f;
			node->camera->perspective.fov = 45.0f;
			node->camera->perspective.aspect = 1.777777791f;
		}
		return 1;
	case EX_COMPONENT_GEOMETRY:
		if (!node->geometry) {
			node->geometry = (ex_geometry_t*)ex_malloc(sizeof(ex_geometry_t));
			node->geometry->material = NULL;
			node->geometry->mesh     = NULL;
		}
		return 1;
	case EX_COMPONENT_LIGHT:
		if (!node->light) {
			node->light = (ex_light_t*)ex_malloc(sizeof(ex_light_t));
			node->light->type = EX_LIGHT_POINT;
			ex_vec3_assign(&node->light->color, 1.0f, 1.0f, 1.0f);
			node->light->intensity = 1.0f;
			node->light->point.radius = 1.0f;
		}
		return 1;
	}

	return 0;
}

int ex_node_remove_component(ex_node_t* node, int component) {
	switch (component) {
	case EX_COMPONENT_CAMERA:
		if (node->camera) {
			ex_free(node->camera);
			node->camera = NULL;
		}
		return 1;
	case EX_COMPONENT_GEOMETRY:
		if (node->geometry) {
			ex_free(node->geometry);
			node->geometry = NULL;
		}
		return 1;
	case EX_COMPONENT_LIGHT:
		if (node->light) {
			ex_free(node->light);
			node->light = NULL;
		}
		return 1;
	}

	return 0;
}

int ex_node_has_component(ex_node_t* node, int component) {
	switch (component) {
	case EX_COMPONENT_CAMERA:
		return node->camera != NULL;
	case EX_COMPONENT_GEOMETRY:
		return node->geometry != NULL;
	case EX_COMPONENT_LIGHT:
		return node->light != NULL;
	}

	return 0;
}


const char* ex_node_get_name(ex_node_t* node) {
	return node->name;
}

int ex_node_get_type(ex_node_t* node) {
	return node->type;
}

void ex_node_set_position(ex_node_t* node, float x, float y, float z) {
	ex_vec3_assign(&node->position, x, y, z);
	node->need_update = 1;
}

void ex_node_set_rotation(ex_node_t* node, float x, float y, float z) {
	ex_vec3_assign(&node->rotation, x, y, z);
	node->need_update = 1;
}

void ex_node_set_scale(ex_node_t* node, float x, float y, float z) {
	ex_vec3_assign(&node->scale, x, y, z);
	node->need_update = 1;
}

const ex_vec3_t* ex_node_get_position(ex_node_t* node) {
	return &node->position;
}

const ex_vec3_t* ex_node_get_rotation(ex_node_t* node) {
	return &node->rotation;
}

const ex_vec3_t* ex_node_get_scale(ex_node_t* node) {
	return &node->scale;
}

const ex_mat4_t* ex_node_get_transform(ex_node_t* node) {
	return &node->transform;
}


int ex_camera_get_type(ex_node_t* node) {
	ex_assert(node->camera);

	return node->camera->type;
}

void ex_camera_get_perspective(ex_node_t* node, float* fov, float* aspect, float* near, float* far) {
	ex_assert(node->camera && node->camera->type == EX_CAMERA_PERSPECTIVE);

	if (fov) {
		*fov = node->camera->perspective.fov;
	}

	if (aspect) {
		*aspect = node->camera->perspective.aspect;
	}

	if (near) {
		*near = node->camera->perspective.near;
	}

	if (far) {
		*far = node->camera->perspective.far;
	}
}

void ex_camera_set_perspective(ex_node_t* node, float fov, float aspect, float near, float far) {
	ex_assert(node->camera && node->camera->type == EX_CAMERA_PERSPECTIVE);

	node->camera->perspective.fov = fov;
	node->camera->perspective.aspect = aspect;
	node->camera->perspective.near = near;
	node->camera->perspective.far = far;

	node->need_update = 1;
}

void ex_camera_get_orthogonal(ex_node_t* node, float* left, float* right, float* top, float* bottom, float* near, float* far) {
	ex_assert(node->camera && node->camera->type == EX_CAMERA_ORTHOGONAL);

	if (left) {
		*left = node->camera->orthogonal.left;
	}

	if (right) {
		*right = node->camera->orthogonal.right;
	}

	if (top) {
		*top = node->camera->orthogonal.top;
	}

	if (bottom) {
		*bottom = node->camera->orthogonal.bottom;
	}

	if (near) {
		*near = node->camera->orthogonal.near;
	}

	if (far) {
		*far = node->camera->orthogonal.far;
	}
}

void ex_camera_set_orthogonal(ex_node_t* node, float left, float right, float top, float bottom, float near, float far) {
	ex_assert(node->camera && node->camera->type == EX_CAMERA_ORTHOGONAL);

	node->camera->orthogonal.left = left;
	node->camera->orthogonal.right = right;
	node->camera->orthogonal.top = top;
	node->camera->orthogonal.bottom = bottom;
	node->camera->orthogonal.near = near;
	node->camera->orthogonal.far = far;

	node->need_update = 1;
}

const ex_mat4_t* ex_camera_get_view(ex_node_t* node) {
	ex_assert(node->camera);

	return &node->camera->view;
}

const ex_mat4_t* ex_camera_get_proj(ex_node_t* node) {
	ex_assert(node->camera);

	return &node->camera->proj;
}


void ex_geometry_set_mesh(ex_node_t* node, ex_mesh_t* mesh) {
	ex_assert(node->geometry);

	node->geometry->mesh = mesh;
}


ex_mesh_t* ex_geometry_get_mesh(ex_node_t* node) {
	ex_assert(node->geometry);

	return node->geometry->mesh;
}

void ex_geometry_set_material(ex_node_t* node, ex_material_t* material) {
	ex_assert(node->geometry);

	node->geometry->material = material;
}

ex_material_t* ex_geometry_get_material(ex_node_t* node) {
	ex_assert(node->geometry);

	return node->geometry->material;
}

int ex_light_get_type(ex_node_t* node) {
	ex_assert(node->light);

	return node->light->type;
}

void ex_light_set_type(ex_node_t* node, int type) {
	ex_assert(node->light);

	if (node->light->type != type) {
		node->light->type = type;

		switch (type) {
			case EX_LIGHT_DIRECTIONAL: {
				ex_vec3_assign(&node->light->directional.direction, -1.0f, 0.0f, 0.0f);
				break;
			}
			case EX_LIGHT_POINT: {
				node->light->point.radius = 1.0f;
				break;
			}
		}
	}
}

void ex_light_set_color(ex_node_t* node, float r, float g, float b) {
	ex_assert(node->light);

	ex_vec3_assign(&node->light->color, r, g, b);
}

void ex_light_set_intensity(ex_node_t* node, float intensity) {
	ex_assert(node->light);

	node->light->intensity = intensity;
}

void ex_light_set_radius(ex_node_t* node, float radius) {
	ex_assert(node->light && node->light->type == EX_LIGHT_POINT);

	node->light->point.radius = radius;
}

const ex_vec3_t* ex_light_get_color(ex_node_t* node) {
	ex_assert(node->light);

	return &node->light->color;
}

float ex_light_get_intensity(ex_node_t* node) {
	ex_assert(node->light);

	return node->light->intensity;
}

float ex_light_get_radius(ex_node_t* node) {
	ex_assert(node->light && node->light->type == EX_LIGHT_POINT);

	return node->light->point.radius;
}

static
void camera_update(ex_node_t* node, float delta_time) {
	ex_mat4_translation(&node->camera->view,
		-node->position.x,
		-node->position.y,
		-node->position.z);

	switch (node->camera->type) {
	case EX_CAMERA_ORTHOGONAL:
		/* TODO: orthogonal */
		break;
	case EX_CAMERA_PERSPECTIVE:
		ex_mat4_perspective(&node->camera->proj,
			node->camera->perspective.fov,
			node->camera->perspective.aspect,
			node->camera->perspective.near,
			node->camera->perspective.far);
		break;
	}
}

void ex_node_update(ex_node_t* node, float delta_time) {
	if (node->need_update) {
		ex_mat4_translation(&node->transform, node->position.x, node->position.y, node->position.z);

		if (node->camera) {
			camera_update(node, delta_time);
		}

		node->need_update = 0;
	}
}