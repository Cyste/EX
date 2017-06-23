#include <ex.h>

int ex_init(void) {
	ex_debug_set_dump(stdout);
	
	ex_keyboard_init();

	return 1;
}

void ex_release(void) {
}