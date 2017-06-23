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
#ifndef EX_H_
#define EX_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "ex_compiler.h"
#include "ex_system.h"
#include "ex_debug.h"
#include "ex_memory.h"
#include "ex_mutex.h"
#include "ex_list.h"
#include "ex_vector.h"
#include "ex_time.h"
#include "ex_math.h"
#include "ex_vec2.h"
#include "ex_vec3.h"
#include "ex_vec4.h"
#include "ex_mat4.h"
#include "ex_config.h"
#include "ex_texture.h"
#include "ex_shader.h"
#include "ex_material.h"
#include "ex_mesh.h"
#include "ex_node.h"
#include "ex_scene.h"
#include "ex_key.h"
#include "ex_event.h"
#include "ex_window.h"
#include "ex_context.h"
#include "ex_screen.h"
#include "ex_renderer.h"

EX_API int ex_init(void);

EX_API void ex_release(void);

#ifdef __cplusplus
}
#endif

#endif