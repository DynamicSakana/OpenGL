#include "Error.h"
extern "C"
{
#include <glad/glad.h>
}
#include <GLFW/glfw3.h>
#include <assert.h>
#include <iostream>
bool ErrorCheck() {
	GLenum errorCode = glGetError();
	switch (errorCode) {
	case GL_INVALID_ENUM:
		std::cout << "Invalid enum\n";
		break;
	case GL_INVALID_VALUE:
		std::cout << "Invalid value\n";
		break;
	case GL_INVALID_OPERATION:
		std::cout << "Invalid operation\n";
		break;
	case GL_OUT_OF_MEMORY:
		std::cout << "Out of memory\n";
		break;
	default:
		break;
	}
	return errorCode;
}