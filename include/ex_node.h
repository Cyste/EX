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
#ifndef EX_NODE_H_
#define EX_NODE_H_

#define EX_COMPONENT_CAMERA   0
#define EX_COMPONENT_GEOMETRY 1
#define EX_COMPONENT_LIGHT    2

#define EX_CAMERA_PERSPECTIVE 0
#define EX_CAMERA_ORTHOGONAL  1

#define EX_LIGHT_POINT       0
#define EX_LIGHT_DIRECTIONAL 1
#define EX_LIGHT_SPOT        2

typedef struct ex_node_t ex_node_t;

EX_API ex_node_t* ex_node_create(const char* name, ex_node_t* parent);

EX_API void ex_node_destroy(ex_node_t* node);


EX_API ex_node_t* ex_node_get_parent(ex_node_t* node);

EX_API unsigned int ex_node_get_children_count(ex_node_t* node);

EX_API ex_node_t* ex_node_get_child(ex_node_t* node, unsigned int index);

EX_API ex_node_t* ex_node_find_child(ex_node_t* node, const char* name);


EX_API int ex_node_add_component(ex_node_t* node, int component);

EX_API int ex_node_remove_component(ex_node_t* node, int component);

EX_API int ex_node_has_component(ex_node_t* node, int component);


EX_API const char* ex_node_get_name(ex_node_t* node);

EX_API void ex_node_set_position(ex_node_t* node, float x, float y, float z);

EX_API void ex_node_set_rotation(ex_node_t* node, float x, float y, float z);

EX_API void ex_node_set_scale(ex_node_t* node, float x, float y, float z);

EX_API const ex_vec3_t* ex_node_get_position(ex_node_t* node);

EX_API const ex_vec3_t* ex_node_get_rotation(ex_node_t* node);

EX_API const ex_vec3_t* ex_node_get_scale(ex_node_t* node);

EX_API const ex_mat4_t* ex_node_get_transform(ex_node_t* node);


EX_API int ex_camera_get_type(ex_node_t* node);

EX_API void ex_camera_get_perspective(ex_node_t* node, float* fov, float* aspect, float* near, float* far);

EX_API void ex_camera_set_perspective(ex_node_t* node, float fov, float aspect, float near, float far);

EX_API void ex_camera_get_orthogonal(ex_node_t* node, float* left, float* right, float* top, float* bottom, float* near, float* far);

EX_API void ex_camera_set_orthogonal(ex_node_t* node, float left, float right, float top, float bottom, float near, float far);

EX_API const ex_mat4_t* ex_camera_get_view(ex_node_t* node);

EX_API const ex_mat4_t* ex_camera_get_proj(ex_node_t* node);


EX_API void ex_geometry_set_mesh(ex_node_t* node, ex_mesh_t* mesh);

EX_API ex_mesh_t* ex_geometry_get_mesh(ex_node_t* node);

EX_API void ex_geometry_set_material(ex_node_t* node, ex_material_t* material);

EX_API ex_material_t* ex_geometry_get_material(ex_node_t* node);


EX_API int ex_light_get_type(ex_node_t* node);

EX_API void ex_light_set_type(ex_node_t* node, int type);

EX_API void ex_light_set_color(ex_node_t* node, float r, float g, float b);

EX_API void ex_light_set_intensity(ex_node_t* node, float intensity);

EX_API void ex_light_set_radius(ex_node_t* node, float radius);

EX_API const ex_vec3_t* ex_light_get_color(ex_node_t* node);

EX_API float ex_light_get_intensity(ex_node_t* node);

EX_API float ex_light_get_radius(ex_node_t* node);


EX_API void ex_node_update(ex_node_t* node, float delta_time);

#endif