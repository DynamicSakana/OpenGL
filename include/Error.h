#pragma once
#include <assert.h>
#include <include/compile.h>

#ifdef DEBUG
#define CALL(func) \
	func;          \
	assert(!ErrorCheck())
#else
#define CALL(func) func;
#endif

bool ErrorCheck();