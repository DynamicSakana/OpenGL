#include "Error.h"
extern "C" {
#include <glad/glad.h>
}
#include <GLFW/glfw3.h>
#include <assert.h>
#include <iostream>
bool ErrorCheck() {
	GLenum errorCode = glGetError();
	if (!errorCode) {
		return errorCode;
	}
	else {
		std::cout << "[Error]: ";
		switch (errorCode) {
		case GL_INVALID_ENUM:
			std::cout << "invalid enum: " << "error code: " << errorCode << "\n";
			break;
		case GL_INVALID_VALUE:
			std::cout << "invalid value: " << "error code: " << errorCode << "\n";
			break;
		case GL_INVALID_OPERATION:
			std::cout << "invalid operation: " << "error code: " << errorCode << "\n";
			break;
		case GL_OUT_OF_MEMORY:
			std::cout << "out of memory: " << "error code: " << errorCode << "\n";
			break;
		default:
			std::cout << "unkown error: error code: " << errorCode << "\n";
			break;
		}
		return errorCode;
	}
}