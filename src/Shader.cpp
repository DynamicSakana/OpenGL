#include <include/Shader.h>
extern "C" {
#include <glad/glad.h>
}
#include <GLFW/glfw3.h>
#include <iostream>
#include "include/Error.h"

void GenShader() {
	// 编写shader的源代码
	const char* vertexShaderSrc =
		"#version 460 core\n"
		"layout (location = 0) in vec3 pos;\n"
		"void main()\n"
		"{\n"
		"	gl_Position = vec4(pos.x, pos.y, pos.z, 1.0);\n"
		"}\0";
	const char* fragmentShaderSrc =
		"#version 330 core\n"
		"out vec4 FragColor;\n"
		"void main()\n"
		"{\n"
		"	FragColor = vec4(1.0f, 0.5f, 0.2f, 0.8f);\n"
		"}\0";
	
	// 创建shader程序
	GLuint vShader, fShader;
	vShader = CALL(glCreateShader(GL_VERTEX_SHADER));
	fShader = CALL(glCreateShader(GL_FRAGMENT_SHADER));

	// 传入shader代码到源代码编译器
	CALL(glShaderSource(vShader, 1, &vertexShaderSrc, NULL));
	CALL(glShaderSource(fShader, 1, &fragmentShaderSrc, NULL));

	// 代码编译并检查代码编译结果
	CALL(glCompileShader(vShader));
	GLint compileStatus;
	// 获取代码编译结束状态
	CALL(glGetShaderiv(vShader, GL_COMPILE_STATUS, &compileStatus));
	if (compileStatus == 0) {
		char infoLog[1024];	// 错误日志
		CALL(glGetShaderInfoLog(vShader, 1024, NULL, infoLog));
		// 将vShader的编译错误储存到长度为1024个字节的char数组infoLog中
		std::cout << "[Error]: shader compile error --vertex\n" << infoLog << "\n";
	}
	CALL(glCompileShader(fShader));
	// 获取代码编译结束状态
	CALL(glGetShaderiv(fShader, GL_COMPILE_STATUS, &compileStatus));
	if (compileStatus == 0) {
		char infoLog[1024];	// 错误日志
		CALL(glGetShaderInfoLog(fShader, 1024, NULL, infoLog));
		// 将vShader的编译错误储存到长度为1024个字节的char数组infoLog中
		std::cout << "[Error]: shader compile error --fragment\n" << infoLog << "\n";
	}

	// 链接两个shader程序
	// 创建shaders program盒子
	GLint program = glCreateProgram();
	// 将编译好的两个shader放入这个盒子
	CALL(glAttachShader(program, vShader));
	CALL(glAttachShader(program, fShader));
	// 将这两个shader链接形成可执行程序
	CALL(glLinkProgram(program));
	// 获取代码编译结束状态
	CALL(glGetProgramiv(program, GL_LINK_STATUS, &compileStatus));
	if (compileStatus == 0) {
		char infoLog[1024];	// 错误日志
		CALL(glGetProgramInfoLog(program, 1024, NULL, infoLog));
		// 将program的链接错误储存到长度为1024个字节的char数组infoLog中
		std::cout << "[Error]: shader link error\n" << infoLog << "\n";
	}

	// 清理中间编译产物 vShader和fShader
	CALL(glDeleteShader(vShader));
	CALL(glDeleteShader(fShader));
}