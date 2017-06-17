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

#define EX_RENDERER_HDR (1 << 0)

typedef struct ex_renderer ex_renderer;

ex_renderer* ex_renderer_create(int width, int height, unsigned int flags);

void ex_renderer_destroy(ex_renderer* renderer);

void ex_renderer_clear(ex_renderer* renderer);

void ex_renderer_begin(ex_renderer* renderer, ex_mat4* view, ex_mat4* proj);

void ex_renderer_geometry_pass(ex_renderer* renderer);

void ex_renderer_render_geometry(ex_renderer* renderer, ex_mesh* mesh, ex_material* material, ex_mat4* world);

void ex_renderer_light_pass(ex_renderer* renderer, float ambient_r, float ambient_g, float ambient_b);

void ex_renderer_render_point_light(ex_renderer* renderer, float x, float y, float z, float r, float g, float b, float intensity, float radius);

void ex_renderer_present(ex_renderer* renderer);

#endif