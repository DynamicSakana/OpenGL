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

GLuint program, vao;

void InterleavedBuffer() {
	// 创建数据
	float data[] = {
		// 每一行代表一个顶点，前三个为位置数据，后三个为颜色数据
		-0.5f, 	-0.5f, 	0.0f, 	1.0f, 	0.0f, 	0.0f,
		0.5f, 	-0.5f, 	0.0f, 	0.0f, 	1.0f, 	0.0f,
		0.0f, 	0.5f, 	0.0f, 	0.0f, 	0.0f, 	1.0f
	};
	// 创建vbo并将数据导入vbo
	GLuint vbo = 0;
	CALL(glGenBuffers(1, &vbo));
	CALL(glBindBuffer(GL_ARRAY_BUFFER, vbo));
	CALL(glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW));
	// 创建并表示vao
	// GLuint vao;
	CALL(glGenVertexArrays(1, &vao));
	CALL(glBindVertexArray(vao));
	// 为vao加入描述信息
	CALL(glEnableVertexAttribArray(0));
	CALL(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0));
	CALL(glEnableVertexAttribArray(1));
	CALL(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float))));
}

void SingleBuffer() {
	// 创建数据
	float pos[] = {
		// 每一行都是一个顶点
		-0.5f, 	-0.5f, 	0.0f,
		0.5f, 	-0.5f, 	0.0f,
		0.0f, 	0.5f, 	0.0f,
		0.5f, 	0.5f, 	0.0f,
		0.8f, 	0.8f, 	0.0f,
		0.8f, 	0.0f, 	0.0f
	};
	// 创建vbo并将数据导入vbo
	GLuint vbo = 0;
	CALL(glGenBuffers(1, &vbo));
	CALL(glBindBuffer(GL_ARRAY_BUFFER, vbo));
	CALL(glBufferData(GL_ARRAY_BUFFER, sizeof(pos), pos, GL_STATIC_DRAW));
	// 创建并表示vao
	// GLuint vao;
	CALL(glGenVertexArrays(1, &vao));
	CALL(glBindVertexArray(vao));
	// 为vao加入描述信息
	CALL(glEnableVertexAttribArray(0));
	CALL(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0));
}

void RenderTriangle() {
	// 清理颜色
	CALL(glClear(GL_COLOR_BUFFER_BIT));
	// 绑定一个shader程序 
	CALL(glUseProgram(program));
	// 绑定一个vao(模型)
	CALL(glBindVertexArray(vao));
	// 发出绘制指令
	// 三角形三个绘制模式：
	// GL_TRIANGLES：每相邻三个点构成一个三角形（012，345，共两个三角形）
	// GL_TRIANGLE_STRIP：每相邻三个点构成一个三角形（012，123，234，345，共四个三角形）
	// GL_TRIANGLE_FAN：每两个点和0号点构成一个三角形（012，023，034，045，共四个三角形）
	// CALL(glDrawArrays(GL_TRIANGLES, 0, 6));
	// CALL(glDrawArrays(GL_TRIANGLE_STRIP, 0, 6));
	// CALL(glDrawArrays(GL_TRIANGLE_FAN, 0, 6));
}

void RenderLine() {
	// 清理颜色
	CALL(glClear(GL_COLOR_BUFFER_BIT));
	// 绑定一个shader程序 
	CALL(glUseProgram(program));
	// 绑定一个vao(模型)
	CALL(glBindVertexArray(vao));
	// 发出绘制指令
	// CALL(glDrawArrays(GL_LINES, 0, 6));
	// CALL(glDrawArrays(GL_LINE_STRIP, 0, 6));
}

int main(int argc, char** argv) {
	APPINIT;

	app.WhenWindowResize(ResizeCallback);
	app.WhenKeyTrigger(keyCallback);
	app.WhenMouseClick(MouseCallback);
	app.WhenMouseScroll(MouseScroll);
	app.WhenMouseMove(MouseMove);

	GenShader();
	SingleBuffer();
	// InterleavedBuffer();
	// 设置opengl视口以及纯色背景
	// CALL(glViewport(0, 0, 800, 600));
	CALL(glClearColor(0.2f, 0.3f, 0.3f, 0.8f));

	// 执行窗口循环
	while (app.LoopGoing()) {
		RenderTriangle();
	}

	// 结束程序
	glfwTerminate();
	return 0;
}