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
#ifndef EX_MATERIAL_H_
#define EX_MATERIAL_H_

#define EX_MATERIAL_TWOSIDED  (1 << 0)
#define EX_MATERIAL_ALPHA     (1 << 1)
#define EX_MATERIAL_WIREFRAME (1 << 2)

typedef struct ex_material ex_material;

ex_material* ex_material_create(ex_material* copy);

void ex_material_destroy(ex_material* material);

void ex_material_set_diffuse(ex_material* material, float r, float g, float b);

void ex_material_get_diffuse(ex_material* material, ex_vec3* diffuse);

void ex_material_set_roughness(ex_material* material, float roughness);

float ex_material_get_roughness(ex_material* material);

void ex_material_set_metallic(ex_material* material, float metallic);

float ex_material_get_metallic(ex_material* material);

void ex_material_set_diffuse_map(ex_material* material, ex_texture* diffuse_map);

ex_texture* ex_material_get_diffuse_map(ex_material* material);

void ex_material_set_normal_map(ex_material* material, ex_texture* normal_map);

ex_texture* ex_material_get_normal_map(ex_material* material);

void ex_material_remove_properties(ex_material* material, unsigned int flags);

void ex_material_add_properties(ex_material* material, unsigned int flags);

unsigned int ex_material_get_properties(ex_material* material);

#endif