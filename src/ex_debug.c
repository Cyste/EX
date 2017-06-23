#include <ex.h>

#ifdef _DEBUG

#ifdef EX_OS_WINDOWS
#	include <Windows.h>
#endif

#include <stdlib.h>
#include <stdarg.h>

static FILE* _output = NULL;

void ex__assert(int cond, const char* filename, unsigned int line, const char* function, const char* condname) {
	if (!cond) {
		char buffer[256];
		sprintf(buffer, "[%s:%d]\n[%s]\n%s", filename, line, function, condname);

#ifdef EX_OS_WINDOWS
		MessageBox(NULL, buffer, "EX", MB_OK | MB_ICONERROR);
#endif

		exit(0);
	}
}

void ex_debug_set_dump(FILE* output) {
	_output = output;
}

void ex_debug__log(const char* filename, int line, const char* function, const char* message, ...) {
	if (_output) {
		va_list list;
		va_start(list, message);
		fprintf(_output, "[%s:%d][%s] ", filename, line, function);
		vfprintf(_output, message, list);
		va_end(list);
	}
}

#endif