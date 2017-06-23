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

typedef struct ex_material_t ex_material_t;

EX_API ex_material_t* ex_material_create(ex_material_t* copy);

EX_API void ex_material_destroy(ex_material_t* material);

EX_API void ex_material_set_diffuse(ex_material_t* material, float r, float g, float b);

EX_API void ex_material_get_diffuse(const ex_material_t* material, ex_vec3_t* diffuse);

EX_API void ex_material_set_roughness(ex_material_t* material, float roughness);

EX_API float ex_material_get_roughness(const ex_material_t* material);

EX_API void ex_material_set_metallic(ex_material_t* material, float metallic);

EX_API float ex_material_get_metallic(const ex_material_t* material);

EX_API void ex_material_set_diffuse_map(ex_material_t* material, ex_texture_t* diffuse_map);

EX_API ex_texture_t* ex_material_get_diffuse_map(const ex_material_t* material);

EX_API void ex_material_set_normal_map(ex_material_t* material, ex_texture_t* normal_map);

EX_API ex_texture_t* ex_material_get_normal_map(const ex_material_t* material);

EX_API void ex_material_remove_properties(ex_material_t* material, unsigned int flags);

EX_API void ex_material_add_properties(ex_material_t* material, unsigned int flags);

EX_API unsigned int ex_material_get_properties(const ex_material_t* material);

#endif