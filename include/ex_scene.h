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
#ifndef EX_SCENE_H_
#define EX_SCENE_H_

typedef struct ex_renderer_t ex_renderer_t;

typedef struct ex_scene_t ex_scene_t;

EX_API ex_scene_t* ex_scene_create(void);

EX_API void ex_scene_destroy(ex_scene_t* scene);

EX_API ex_node_t* ex_scene_add_node(ex_scene_t* scene, const char* name, ex_node_t* parent);

EX_API ex_node_t* ex_scene_find_node(ex_scene_t* scene, const char* name);

EX_API void ex_scene_set_main_camera(ex_scene_t* scene, ex_node_t* camera);

EX_API void ex_scene_update(ex_scene_t* scene, float delta_time);

EX_API void ex_scene_render(ex_scene_t* scene, ex_renderer_t* renderer);

#endif