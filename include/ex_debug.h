#ifndef EX_DEBUG_H_
#define EX_DEBUG_H_

#include <assert.h>

#ifdef _DEBUG
#	define ex_assert(x) assert(x)
#	define ex_verify(x) assert(x)
#else
#	define ex_assert(x) (0)
#	define ex_verify(x) (x)
#endif

#endif