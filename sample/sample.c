#include <ex.h>

#include <math.h>

int main(int argc, char** argv) {
	int running = 1;
	ex_window* window = ex_window_create("EX", 1280, 720, EX_WINDOW_DEFAULT);
	ex_context* context = ex_context_create(window);
	ex_renderer* renderer = ex_renderer_create(1280, 720, EX_RENDERER_HDR);
	ex_mesh* mesh = ex_mesh_create_sphere(0.5f, 32, 32);
	ex_mesh* ground = ex_mesh_create_plane(40.0f, 40.0f);

	ex_mat4 view, proj, world;

	ex_mat4_translation(&view, 0.0f, -1.0f, -5.0f);
	ex_mat4_perspective(&proj, 45.0f, 1280.0f / 720.0f, 1.0f, 10.0f);
	ex_mat4_translation(&world, 0.0f, 0.0f, 0.0f);

	ex_context_interval(context, EX_INTERVAL_VSYNC);

	while (running) {
		ex_event event;
		while (ex_window_poll_events(window, &event)) {
			switch (event.type) {
				case EX_EVENT_CLOSE:
					running = 0;
					break;
			}
		}
		
		ex_renderer_clear(renderer);

		ex_renderer_begin(renderer, &view, &proj);

		ex_renderer_geometry_pass(renderer);

		ex_mat4_translation(&world, 0.0f, 0.5f, 0.0f);

		ex_renderer_render_geometry(renderer, mesh, NULL, &world);

		ex_mat4_translation(&world, 0.0f, 0.0f, 0.0f);

		ex_renderer_render_geometry(renderer, ground, NULL, &world);

		ex_renderer_light_pass(renderer, 0.2f, 0.2f, 0.2f);

		ex_renderer_render_point_light(renderer, cosf(0) * 1.5f, 0.6f, sinf(0) * 1.5f, 1.0f, 0.0f, 0.0f, 1.0f, 2.0f);

		ex_renderer_render_point_light(renderer, cosf(EX_PI * 2 / 3) * 1.5f, 0.6f, sinf(EX_PI * 2 / 3) * 1.5f, 0.0f, 1.0f, 0.0f, 1.0f, 2.0f);

		ex_renderer_render_point_light(renderer, cosf(EX_PI * 2 * 0.6f) * 1.5f, 0.6f, sinf(EX_PI * 2 * 0.6f) * 1.5f, 0.0f, 0.0f, 1.0f, 1.0f, 2.0f);

		ex_renderer_present(renderer);

		ex_context_swap(context);
	}

	ex_mesh_destroy(ground);
	ex_mesh_destroy(mesh);
	ex_renderer_destroy(renderer);
	ex_context_destroy(context);
	ex_window_destroy(window);
	return 0;
}
