#ifndef EX_DEBUG_H_
#define EX_DEBUG_H_

#ifdef _DEBUG
	EX_API void ex__assert(int cond, const char* filename, unsigned int line, const char* function, const char* condname);
#	define ex_assert(x) ex__assert(!!(x), __FILE__, __LINE__, __FUNCTION__, #x)
#	define ex_verify(x) ex_assert(x)

#	include <stdio.h>
	EX_API void ex_debug_set_dump(FILE* output);
	EX_API void ex_debug__log(const char* filename, int line, const char* function, const char* message, ...);
#	define ex_debug_log(message, ...) ex_debug__log(__FILE__, __LINE__, __FUNCTION__, message, __VA_ARGS__)
#else
#	define ex_assert(x) (0)
#	define ex_verify(x) (x)

#	define ex_debug_set_dump(output) (0)
#	define ex_debug_log(message, ...) (0)
#endif

#endif