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
#ifndef EX_MESH_H_
#define EX_MESH_H_

#define EX_VERTEX_NONE 0

#define EX_VERTEX_POSITION    (1 << 0) /* 0000 0000 0000 0001 */
#define EX_VERTEX_TEXCOORD    (1 << 1) /* 0000 0000 0000 0010 */
#define EX_VERTEX_NORMAL      (1 << 2) /* 0000 0000 0000 0100 */
#define EX_VERTEX_BONE_WEIGHT (1 << 3) /* 0000 0000 0000 1000 */
#define EX_VERTEX_BONE_ID     (1 << 4) /* 0000 0000 0001 0000 */

#define EX_VERTEX_FLOAT    (1 << 8)  /* 0000 0001 0000 0000 */
#define EX_VERTEX_FLOAT2   (1 << 9)  /* 0000 0010 0000 0000 */
#define EX_VERTEX_FLOAT3   (1 << 10) /* 0000 0100 0000 0000 */
#define EX_VERTEX_FLOAT4   (1 << 11) /* 0000 1000 0000 0000 */
#define EX_VERTEX_INTEGER  (1 << 12) /* 0001 0000 0000 0000 */
#define EX_VERTEX_INTEGER2 (1 << 13) /* 0010 0000 0000 0000 */
#define EX_VERTEX_INTEGER3 (1 << 14) /* 0100 0000 0000 0000 */
#define EX_VERTEX_INTEGER4 (1 << 15) /* 1000 0000 0000 0000 */

#define EX_VERTEX_NAME_MASK 0x00FF
#define EX_VERTEX_TYPE_MASK 0xFF00

#define EX_VERTEX(name, type) (name | type)

#define EX_INDEX_UINT8  0
#define EX_INDEX_UINT16 1
#define EX_INDEX_UINT32 2

#define EX_TOPOLOGY_POINTS         0
#define EX_TOPOLOGY_LINES          1
#define EX_TOPOLOGY_LINE_STRIP     2
#define EX_TOPOLOGY_TRIANGLES      3
#define EX_TOPOLOGY_TRIANGLE_STRIP 4
#define EX_TOPOLOGY_TRIANGLE_FAN   5

typedef unsigned short ex_vertex_element_t;

typedef struct ex_mesh_t ex_mesh_t;

EX_API ex_mesh_t* ex_mesh_create(ex_vertex_element_t* elements,
	void* vertices, 
	unsigned int vertex_count, 
	void* indices, 
	unsigned int index_count, 
	int index_type, 
	int topology);

EX_API ex_mesh_t* ex_mesh_create_sphere(float radius, int slices, int stacks);

EX_API ex_mesh_t* ex_mesh_create_fullscreen_quad(void);

EX_API ex_mesh_t* ex_mesh_create_plane(float width, float height);

EX_API void ex_mesh_destroy(ex_mesh_t* mesh);

EX_API void ex_mesh_render(const ex_mesh_t* mesh);

#endif