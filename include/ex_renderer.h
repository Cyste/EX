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
#ifndef EX_RENDERER_H_
#define EX_RENDERER_H_

#define EX_RENDERER_HDR           (1 << 0)
#define EX_RENDERER_SUPERSAMPLING (1 << 1)
#define EX_RENDERER_DOWNSAMPLING  (1 << 2)

typedef struct ex_renderer_t ex_renderer_t;

EX_API ex_renderer_t* ex_renderer_create(int width, int height, unsigned int flags);

EX_API void ex_renderer_destroy(ex_renderer_t* renderer);

EX_API void ex_renderer_resize(ex_renderer_t* renderer, int width, int height);

EX_API void ex_renderer_clear(ex_renderer_t* renderer);

EX_API void ex_renderer_begin(ex_renderer_t* renderer, const ex_mat4_t* view, const ex_mat4_t* proj);

EX_API void ex_renderer_geometry_pass(ex_renderer_t* renderer);

EX_API void ex_renderer_render_geometry(ex_renderer_t* renderer, const ex_mesh_t* mesh, const ex_material_t* material, const ex_mat4_t* world);

EX_API void ex_renderer_light_pass(ex_renderer_t* renderer, float ambient_r, float ambient_g, float ambient_b);

EX_API void ex_renderer_render_directional_light(ex_renderer_t* renderer, float x, float y, float z, float r, float g, float b, float intensity);

EX_API void ex_renderer_render_point_light(ex_renderer_t* renderer, float x, float y, float z, float r, float g, float b, float intensity, float radius);

EX_API void ex_renderer_present(ex_renderer_t* renderer);

#endif