#pragma once
#include <assert.h>

#define DEBUG

#ifdef DEBUG
#define CALL(func) \
	func;          \
	assert(!ErrorCheck())
#else
#define CALL(func) func;
#endif

bool ErrorCheck();