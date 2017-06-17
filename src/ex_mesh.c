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
#include <math.h>

#define GLEW_STATIC
#include "gl/glew.h"

#define EX_BUFFER_VERTEX 0
#define EX_BUFFER_INDEX  1

struct ex_mesh {
	GLuint id;
	GLuint buffers[2];

	ex_vertex_element* elements;

	unsigned int vertex_count;
	unsigned int index_count;

	int index_type;
	int topology;
};

static
GLenum _modes[] = {
	GL_POINTS,
	GL_LINES,
	GL_LINE_STRIP,
	GL_TRIANGLES,
	GL_TRIANGLE_STRIP,
	GL_TRIANGLE_FAN
};

static
GLenum _index_types[] = {
	GL_UNSIGNED_BYTE,
	GL_UNSIGNED_SHORT,
	GL_UNSIGNED_INT
};

static
unsigned int _vertex_element_sizes[] = {
	sizeof(float),    
	sizeof(float) * 2, 
	sizeof(float) * 3, 
	sizeof(float) * 4, 

	sizeof(int), 
	sizeof(int) * 2, 
	sizeof(int) * 3, 
	sizeof(int) * 4, 
};

static 
char _vertex_element_integers[] = {
	0, 0, 0, 0,
	1, 1, 1, 1
};

static
unsigned int _index_type_sizes[] = {
	sizeof(unsigned char),
	sizeof(unsigned short),
	sizeof(unsigned int)
};

static 
unsigned int get_vertex_size(ex_vertex_element* elements) {
	unsigned int vertex_size = 0;
	int i;
	for (i = 0; elements[i]; i++) {
		vertex_size += _vertex_element_sizes[i];
	}
	return vertex_size;
}

static 
unsigned int get_vertex_element_size(ex_vertex_element element) {
	unsigned int type = ((element & EX_VERTEX_TYPE_MASK) >> 8);
	unsigned int i;
	for (i = 0; i < sizeof(_vertex_element_sizes) / sizeof(_vertex_element_sizes[0]); i++) {
		if (type & (1 << i)) {
			return _vertex_element_sizes[i];
		}
	}
	return 0;
}

ex_mesh* ex_mesh_create(ex_vertex_element* elements,
	void* vertices,
	unsigned int vertex_count,
	void* indices,
	unsigned int index_count,
	int index_type,
	int topology) {
	ex_mesh* mesh = (ex_mesh*)malloc(sizeof(ex_mesh));
	unsigned int vertex_size = 0;
	unsigned int element_count = 0;
	int offset = 0;
	int i;

	for (i = 0; elements[i]; i++) {
		vertex_size += get_vertex_element_size(elements[i]);
		element_count++;
	}

	mesh->elements = (ex_vertex_element*)malloc((element_count + 1) * sizeof(ex_vertex_element));
	memcpy(mesh->elements, elements, (element_count + 1) * sizeof(ex_vertex_element));

	mesh->vertex_count = vertex_count;
	mesh->index_count = index_count;

	mesh->index_type = index_type;
	mesh->topology = topology;

	glGenVertexArrays(1, &mesh->id);
	glBindVertexArray(mesh->id);

	glGenBuffers(2, mesh->buffers);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->buffers[EX_BUFFER_VERTEX]);
	glBufferData(GL_ARRAY_BUFFER, vertex_count * vertex_size, vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->buffers[EX_BUFFER_INDEX]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_count * _index_type_sizes[index_type], indices, GL_STATIC_DRAW);

	for (i = 0; elements[i]; i++) {
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, get_vertex_element_size(elements[i]) / sizeof(GLfloat), GL_FLOAT, GL_FALSE, vertex_size, (GLvoid*)offset);
		offset += get_vertex_element_size(elements[i]);
	}

	glBindVertexArray(0);
	return mesh;
}

ex_mesh* ex_mesh_create_sphere(float radius, int slices, int stacks) {
	ex_mesh* mesh;
	float phi, theta;
	float dphi = EX_PI / stacks;
	float dtheta = (2.0f * EX_PI) / slices;
	float x, y, z, sc;
	int index = 0, stack, slice;
	GLuint* indices;
	int k;

	struct ex_vertex {
		ex_vec3 position;
		ex_vec3 normal;
		ex_vec2 texcoord;
	} *vertices = (struct ex_vertex*)malloc(sizeof(struct ex_vertex) * (slices + 1) * (stacks + 1));

	ex_vertex_element elements[] = {
		EX_VERTEX(EX_VERTEX_POSITION, EX_VERTEX_FLOAT3),
		EX_VERTEX(EX_VERTEX_NORMAL, EX_VERTEX_FLOAT3),
		EX_VERTEX(EX_VERTEX_TEXCOORD, EX_VERTEX_FLOAT2),
		EX_VERTEX_NONE
	};

	for (stack = 0; stack <= stacks; stack++) {
		phi = EX_PI * 0.5f - stack * dphi;
		y = radius * sinf(phi);
		sc = -radius * cosf(phi);

		for (slice = 0; slice <= slices; slice++) {
			theta = slice * dtheta;
			x = sc * sinf(theta);
			z = sc * cosf(theta);

			ex_vec3_assign(&vertices[index].position, x, y, z);
			ex_vec3_normalize(&vertices[index].normal, &vertices[index].position);
			ex_vec2_assign(&vertices[index].texcoord, slice / (float)slices, stack / (float)stacks);

			index++;
		}
	}

	indices = (unsigned int*)malloc(sizeof(unsigned int) * (stacks * slices * 6));
	index = 0;
	k = slices + 1;

	for (int stack = 0; stack < stacks; stack++) {
		for (int slice = 0; slice < slices; slice++) {
			indices[index++] = (stack + 0) * k + slice;
			indices[index++] = (stack + 1) * k + slice;
			indices[index++] = (stack + 0) * k + slice + 1;

			indices[index++] = (stack + 0) * k + slice + 1;
			indices[index++] = (stack + 1) * k + slice;
			indices[index++] = (stack + 1) * k + slice + 1;
		}
	}

	mesh = ex_mesh_create(elements, vertices, (slices + 1) * (stacks + 1), indices, index, EX_INDEX_UINT32, EX_TOPOLOGY_TRIANGLES);

	free(vertices);
	free(indices);

	return mesh;
}

ex_mesh* ex_mesh_create_fullscreen_quad(void) {
	ex_vec2 vertices[] = {
		{ -1, 1 },
		{ -1, -1 },
		{ 1, -1 },
		{ 1, 1 }
	};

	unsigned char indices[] = {
		0, 1, 2,
		2, 3, 0
	};

	ex_vertex_element elements[] = {
		EX_VERTEX(EX_VERTEX_POSITION, EX_VERTEX_FLOAT2),
		EX_VERTEX_NONE
	};

	return ex_mesh_create(elements, vertices, 4, indices, 6, EX_INDEX_UINT8, EX_TOPOLOGY_TRIANGLES);
}

ex_mesh* ex_mesh_create_plane(float width, float height) {
	width *= 0.5f;
	height *= 0.5f;

	struct ex_vertex {
		ex_vec3 position;
		ex_vec3 normal;
		ex_vec2 texcoord;
	} vertices[] = {
		{ { -width, 0.0f, -height }, { 0.0f, 1.0f, 0.0f }, { 0.0f, 0.0f } },
		{ { -width, 0.0f, height },  { 0.0f, 1.0f, 0.0f }, { 0.0f, 1.0f } },
		{ { width, 0.0f, height },   { 0.0f, 1.0f, 0.0f }, { 1.0f, 1.0f } },
		{ { width, 0.0f, -height },  { 0.0f, 1.0f, 0.0f }, { 1.0f, 0.0f } }
	};

	unsigned char indices[] = {
		0, 1, 2,
		2, 3, 0
	};

	ex_vertex_element elements[] = {
		EX_VERTEX(EX_VERTEX_POSITION, EX_VERTEX_FLOAT3),
		EX_VERTEX(EX_VERTEX_NORMAL, EX_VERTEX_FLOAT3),
		EX_VERTEX(EX_VERTEX_TEXCOORD, EX_VERTEX_FLOAT2),
		EX_VERTEX_NONE
	};

	return ex_mesh_create(elements, vertices, 4, indices, 6, EX_INDEX_UINT8, EX_TOPOLOGY_TRIANGLES);
}

void ex_mesh_destroy(ex_mesh* mesh) {
	glDeleteVertexArrays(1, &mesh->id);
	glDeleteBuffers(2, mesh->buffers);
	free(mesh->elements);

	free(mesh);
}

void ex_mesh_render(ex_mesh* mesh) {
	glBindVertexArray(mesh->id);

	if (mesh->index_count > 0) {
		glDrawElements(_modes[mesh->topology], mesh->index_count, _index_types[mesh->index_type], 0);
	} else if (mesh->vertex_count > 0) {
		glDrawArrays(_modes[mesh->topology], 0, mesh->vertex_count);
	}

	glBindVertexArray(0);
}