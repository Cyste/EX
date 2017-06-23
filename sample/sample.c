#include <vld.h>

#include <ex.h>

#include <stdlib.h>
#include <math.h>

static ex_window_t*   window   = NULL;
static ex_context_t*  context  = NULL;
static ex_renderer_t* renderer = NULL;

static ex_mesh_t*     r_sphere    = NULL;
static ex_mesh_t*     r_floor     = NULL;
static ex_material_t* material    = NULL;
static ex_texture_t*  diffuse_map = NULL;
static ex_texture_t*  normal_map  = NULL;

static ex_scene_t* scene     = NULL;
static ex_node_t*  camera    = NULL;
static ex_node_t*  sphere    = NULL;
static ex_node_t*  ground    = NULL;
static ex_node_t*  lights[4] = { NULL, NULL, NULL, NULL };

static float rotation = 0.0f;

int init(void) {
	if (!ex_init()) {
		return 0;
	}

	window   = ex_window_create("EX", 1280, 720, EX_WINDOW_DEFAULT | EX_WINDOW_RESIZABLE);
	context  = ex_context_create(window);
	renderer = ex_renderer_create(1280, 720, EX_RENDERER_HDR);

	ex_context_interval(context, EX_INTERVAL_NONE);

	r_sphere    = ex_mesh_create_sphere(0.5f, 32, 32);
	r_floor     = ex_mesh_create_plane(20.0f, 20.0f);
	material    = ex_material_create(NULL);
	diffuse_map = ex_texture_load("../data/sample/textures/floor_d.png");
	normal_map  = ex_texture_load("../data/sample/textures/floor_n.png");

	ex_texture_generate_mipmaps(diffuse_map);
	ex_texture_generate_mipmaps(normal_map);

	ex_material_set_diffuse_map(material, diffuse_map);
	ex_material_set_normal_map(material, normal_map);

	scene     = ex_scene_create();

	camera    = ex_scene_add_node(scene, "camera", NULL);
	sphere    = ex_scene_add_node(scene, "sphere", NULL);
	ground    = ex_scene_add_node(scene, "floor", NULL);
	lights[0] = ex_scene_add_node(scene, "light0", NULL);
	lights[1] = ex_scene_add_node(scene, "light1", NULL);
	lights[2] = ex_scene_add_node(scene, "light2", NULL);
	lights[3] = ex_scene_add_node(scene, "light3", NULL);

	ex_node_add_component(camera, EX_COMPONENT_CAMERA);
	ex_node_add_component(sphere, EX_COMPONENT_GEOMETRY);
	ex_node_add_component(ground, EX_COMPONENT_GEOMETRY);
	ex_node_add_component(lights[0], EX_COMPONENT_LIGHT);
	ex_node_add_component(lights[1], EX_COMPONENT_LIGHT);
	ex_node_add_component(lights[2], EX_COMPONENT_LIGHT);
	ex_node_add_component(lights[3], EX_COMPONENT_LIGHT);

	ex_camera_set_perspective(camera, 45.0f, 1280.0f / 720.0f, 0.01f, 100.0f);
	ex_node_set_position(camera, 0.0f, 1.0f, 5.0f);

	ex_node_set_position(sphere, 0.0f, 0.5f, 0.0f);
	ex_geometry_set_mesh(sphere, r_sphere);
	ex_geometry_set_material(sphere, material);

	ex_geometry_set_mesh(ground, r_floor);
	ex_geometry_set_material(ground, material);

	ex_light_set_type(lights[3], EX_LIGHT_DIRECTIONAL);
	ex_node_set_position(lights[3], -1.0f, -1.0f, 0.0f);

	ex_light_set_intensity(lights[0], 1.0f);
	ex_light_set_intensity(lights[1], 1.0f);
	ex_light_set_intensity(lights[2], 1.0f);
	ex_light_set_intensity(lights[3], 0.5f);

	ex_light_set_radius(lights[0], 2.0f);
	ex_light_set_radius(lights[1], 2.0f);
	ex_light_set_radius(lights[2], 2.0f);

	ex_scene_set_main_camera(scene, camera);

	return 1;
}

void update(float delta_time) {
	const ex_vec3_t* position = 0;

	if (ex_keyboard_get_state(EX_KEY_W)) {
		position = ex_node_get_position(camera);

		ex_node_set_position(camera, position->x, position->y, position->z - delta_time * 4.0f);
	}
	else if (ex_keyboard_get_state(EX_KEY_S)) {
		position = ex_node_get_position(camera);

		ex_node_set_position(camera, position->x, position->y, position->z + delta_time * 4.0f);
	}

	if (ex_keyboard_get_state(EX_KEY_A)) {
		position = ex_node_get_position(camera);

		ex_node_set_position(camera, position->x - delta_time * 4.0f, position->y, position->z);
	}
	else if (ex_keyboard_get_state(EX_KEY_D)) {
		position = ex_node_get_position(camera);

		ex_node_set_position(camera, position->x + delta_time * 4.0f, position->y, position->z);
	}

	if (ex_keyboard_get_state(EX_KEY_Q)) {
		position = ex_node_get_position(camera);

		ex_node_set_position(camera, position->x, position->y - delta_time * 4.0f, position->z);
	}
	else if (ex_keyboard_get_state(EX_KEY_E)) {
		position = ex_node_get_position(camera);

		ex_node_set_position(camera, position->x, position->y + delta_time * 4.0f, position->z);
	}

	rotation += delta_time;

	ex_node_set_position(lights[0], cosf(rotation) * 1.5f, 0.5f, sinf(rotation) * 1.5f);

	ex_node_set_position(lights[1], cosf(rotation + EX_PI * 2 * 0.3333f) * 1.5f, 0.5f, sinf(rotation + EX_PI * 2 * 0.3333f) * 1.5f);

	ex_node_set_position(lights[2], cosf(rotation + EX_PI * 2 * 0.6666f) * 1.5f, 0.5f, sinf(rotation + EX_PI * 2 * 0.6666f) * 1.5f);

	ex_scene_update(scene, delta_time);
}

void render(void) {
	ex_scene_render(scene, renderer);

	ex_context_swap(context);
}

void run(void) {
	ex_event_t event;
	int running = 1;

	unsigned int last_time = ex_get_time(), curr_time;
	float delta_time;

	while (running) {
		while (ex_window_poll_events(window, &event)) {
			switch (event.type) {
			case EX_EVENT_RESIZE:
				ex_renderer_resize(renderer, event.resize.width, event.resize.height);
				ex_camera_set_perspective(camera, 45.0f, event.resize.width / (float)event.resize.height, 0.01f, 10.0f);
				break;
			case EX_EVENT_CLOSE:
				running = 0;
				break;
			}
		}

		curr_time = ex_get_time();
		delta_time = (curr_time - last_time) * 0.001f;
		last_time = curr_time;

		update(delta_time);

		render();
	}
}

void release(void) {
	ex_texture_destroy(normal_map);
	ex_texture_destroy(diffuse_map);
	ex_material_destroy(material);
	ex_mesh_destroy(r_floor);
	ex_mesh_destroy(r_sphere);
	ex_scene_destroy(scene);
	ex_renderer_destroy(renderer);
	ex_context_destroy(context);
	ex_window_destroy(window);
	ex_release();
}

int main(int argc, char** argv) {
	if (init()) {
		run();

		release();
	}
	return 0;
}