// 注意glad的头文件必须在glfw头文件之前
extern "C" {
#include <glad/glad.h>
}
#include <GLFW/glfw3.h>
#include <iostream>

#include "TIMER/Timer.h"
#include "include/Error.h"
#include "include/Application.h"
#include "include/Respond.h"
#include "include/Shader.h"

void InterleavedBuffer() {
	// 创建数据
	float data[] = {
		-0.5f, 	-0.5f, 	0.0f, 	1.0f, 	0.0f, 	0.0f,
		0.5f, 	-0.5f, 	0.0f, 	0.0f, 	1.0f, 	0.0f,
		0.0f, 	0.5f, 	0.0f, 	0.0f, 	0.0f, 	1.0f
	};
	// 创建vbo
	GLuint vbo = 0;
	CALL(glGenBuffers(1, &vbo));
	CALL(glBindBuffer(GL_ARRAY_BUFFER, vbo));
	CALL(glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW));
	// 创建并表示vao
	GLuint vao;
	CALL(glGenVertexArrays(1, &vao));
	CALL(glBindVertexArray(vao));
	// 为vao加入描述信息
	CALL(glEnableVertexAttribArray(0));
	CALL(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0));
	CALL(glEnableVertexAttribArray(1));
	CALL(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float))));
}

int main(int argc, char** argv) {

	app;
	app.WhenWindowResize(ResizeCallback);
	app.WhenKeyTrigger(keyCallback);
	app.WhenMouseClick(MouseCallback);
	app.WhenMouseScroll(MouseScroll);
	app.WhenMouseMove(MouseMove);

	GenShader();
	InterleavedBuffer();
	// 设置opengl视口以及纯色背景
	// CALL(glViewport(0, 0, 800, 600));
	CALL(glClearColor(0.2f, 0.3f, 0.3f, 0.8f));

	// 执行窗口循环
	while (app.LoopGoing()) {
		// 清理颜色
		CALL(glClear(GL_COLOR_BUFFER_BIT));
	}

	// 结束程序
	glfwTerminate();
	return 0;
}