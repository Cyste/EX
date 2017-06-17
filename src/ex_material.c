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

struct ex_material {
	ex_vec3 diffuse;
	float roughness;
	float metallic;

	ex_texture* diffuse_map;
	ex_texture* normal_map;

	unsigned int flags;
};

ex_material* ex_material_create(ex_material* copy) {
	ex_material* material = (ex_material*)malloc(sizeof(ex_material));
	if (copy) {
		*material = *copy;
	} else {
		ex_vec3_assign(&material->diffuse, 1.0f, 1.0f, 1.0f);
		material->roughness = 1.0f;
		material->metallic = 0.0f;
		
		material->diffuse_map = NULL;
		material->normal_map = NULL;

		material->flags = 0;
	}
	return material;
}

void ex_material_destroy(ex_material* material) {
	free(material);
}

void ex_material_set_diffuse(ex_material* material, float r, float g, float b) {
	ex_vec3_assign(&material->diffuse, r, g, b);
}

void ex_material_get_diffuse(ex_material* material, ex_vec3* diffuse) {
	*diffuse = material->diffuse;
}

void ex_material_set_roughness(ex_material* material, float roughness) {
	material->roughness = material->roughness;
}

float ex_material_get_roughness(ex_material* material) {
	return material->roughness;
}

void ex_material_set_metallic(ex_material* material, float metallic) {
	material->metallic = metallic;
}

float ex_material_get_metallic(ex_material* material) {
	return material->metallic;
}

void ex_material_set_diffuse_map(ex_material* material, ex_texture* diffuse_map) {
	material->diffuse_map = diffuse_map;
}

ex_texture* ex_material_get_diffuse_map(ex_material* material) {
	return material->diffuse_map;
}

void ex_material_set_normal_map(ex_material* material, ex_texture* normal_map) {
	material->normal_map = normal_map; 
}

ex_texture* ex_material_get_normal_map(ex_material* material) {
	return material->normal_map;
}

void ex_material_remove_properties(ex_material* material, unsigned int flags) {
	material->flags &= ~flags;
}

void ex_material_add_properties(ex_material* material, unsigned int flags) {
	material->flags |= flags;
}

unsigned int ex_material_get_properties(ex_material* material) {
	return material->flags;
}