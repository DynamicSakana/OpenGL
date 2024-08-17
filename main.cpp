// 注意glad的头文件必须在glfw头文件之前
#include <include/glAPI.h>
#include <iostream>

#include "Timer/Timer.h"
#include "include/Error.h"
#include "include/Application.h"
#include "include/Respond.h"
#include "include/Shader.h"
#include "include/Texture.h"

GLuint vao;
Shader* shader = nullptr;
Texture* sky, * cat, * cloud, * firefly= nullptr;

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
	// 为vao加入描述信息
	CALL(glBindVertexArray(vao));
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
	// 绑定一个vao(模型)
	CALL(glBindVertexArray(vao));
	// 发出绘制指令
	// 三角形三个绘制模式：
	// GL_TRIANGLES：每相邻三个点构成一个三角形（012，345，共两个三角形）
	// GL_TRIANGLE_STRIP：每相邻三个点构成一个三角形（012，123，234，345，共四个三角形）
	// GL_TRIANGLE_FAN：每两个点和0号点构成一个三角形（012，023，034，045，共四个三角形）
	// CALL(glDrawArrays(GL_TRIANGLES, 0, 3));
	// CALL(glDrawArrays(GL_TRIANGLE_STRIP, 0, 6));
	// CALL(glDrawArrays(GL_TRIANGLE_FAN, 0, 6));
	CALL(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0));
}

void RenderLine() {
	// 清理颜色
	CALL(glClear(GL_COLOR_BUFFER_BIT));
	// 绑定一个shader程序 
	// 绑定一个vao(模型)
	CALL(glBindVertexArray(vao));
	// 发出绘制指令
	// CALL(glDrawArrays(GL_LINES, 0, 6));
	// CALL(glDrawArrays(GL_LINE_STRIP, 0, 6));
}

void EBO() {
	// vao数据
	float pos[] = {
		0.75f, 0.75f, 0.0f,
		-0.75f, 0.75f, 0.0f,
		-0.75f, -0.75f, 0.0f,
		0.75f, -0.75f, 0.0f,
	};

	// float color[] = {
	// 	1.0f, 0.0f, 0.0f,
	// 	0.0f, 1.0f, 0.0f,
	// 	0.0f, 0.0f, 1.0f,
	// 	1.0f, 1.0f, 1.0f
	// };

	float uv[] = {
		1.0f, 1.0f,
		0.0f, 1.0f,
		0.0f, 0.0f,
		1.0f, 0.0f
	};

	uint32_t index[] = {
		0, 1, 2,
		0, 2, 3
	};

	// 创建vbo
	GLuint posvbo;
	CALL(glGenBuffers(1, &posvbo));
	CALL(glBindBuffer(GL_ARRAY_BUFFER, posvbo));
	CALL(glBufferData(GL_ARRAY_BUFFER, sizeof(pos), pos, GL_STATIC_DRAW));
	GLuint colorvbo;
	CALL(glGenBuffers(1, &colorvbo));
	CALL(glBindBuffer(GL_ARRAY_BUFFER, colorvbo));
	// CALL(glBufferData(GL_ARRAY_BUFFER, sizeof(color), color, GL_STATIC_DRAW));
	GLuint uvvbo;
	CALL(glGenBuffers(1, &uvvbo));
	CALL(glBindBuffer(GL_ARRAY_BUFFER, uvvbo));
	CALL(glBufferData(GL_ARRAY_BUFFER, sizeof(uv), uv, GL_STATIC_DRAW));
	// 创建ebo
	GLuint ebo;
	CALL(glGenBuffers(1, &ebo));
	CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo));
	CALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index), index, GL_STATIC_DRAW));
	// vao创建
	CALL(glGenVertexArrays(1, &vao));
	CALL(glBindVertexArray(vao));

	// 动态获取位置
	// glGetAttriLocation会按照vertex shader中in的位置决定属性的写入位置
	GLint posLocation = CALL(glGetAttribLocation(shader->GetProgram(), "a_pos"));
	// GLint colorLocation = CALL(glGetAttribLocation(shader->GetProgram(), "a_color"));
	GLint uvLocation = CALL(glGetAttribLocation(shader->GetProgram(), "a_uv"));

	// 绑定vbo，ebo加入属性描述信息
	// 加入位置信息
	CALL(glBindBuffer(GL_ARRAY_BUFFER, posvbo));
	CALL(glEnableVertexAttribArray(posLocation));
	CALL(glVertexAttribPointer(posLocation, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0));
	// 加入颜色信息
	// CALL(glBindBuffer(GL_ARRAY_BUFFER, colorvbo));
	// CALL(glEnableVertexAttribArray(colorLocation));
	// CALL(glVertexAttribPointer(colorLocation, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0));
	// 加入uv信息
	CALL(glBindBuffer(GL_ARRAY_BUFFER, uvvbo));
	CALL(glEnableVertexAttribArray(uvLocation));
	CALL(glVertexAttribPointer(uvLocation, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0));
	// 加入ebo信息
	CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo));
}

int main(int argc, char** argv) {
	APPINIT(1000, 1000);
	shader = new Shader("assets/Shaders/vertex.vert", "assets/Shaders/fragment.frag");
	app.WhenWindowResize(ResizeCallback);
	app.WhenKeyTrigger(keyCallback);
	app.WhenMouseClick(MouseCallback);
	app.WhenMouseScroll(MouseScroll);
	app.WhenMouseMove(MouseMove);

	EBO();
	sky = new Texture("assets/texture/Sky.jpg", 0);
	cat = new Texture("assets/texture/Cat.jpg", 1);
	cloud = new Texture("assets/texture/Cloud.jpg", 2);
	firefly = new Texture("assets/texture/LowResolution.jpg", 3);
	// sky->BindTexture();
	// InterleavedBuffer();
	CALL(glClearColor(0.2f, 0.3f, 0.3f, 0.8f));

	// 执行窗口循环
	while (app.LoopGoing()) {
		shader->BeginUse();
		// shader->SetUniform("u_time", float(glfwGetTime()));
		// shader->SetUniform("u_velocity", 0.5f);
		shader->SetSample("skySampler", sky->GetTextureUnit());
		shader->SetSample("catSampler", cat->GetTextureUnit());
		//shader->SetSample("cloudSampler", cloud->GetTextureUnit());
		shader->SetSample("cloudSampler", firefly->GetTextureUnit());
		shader->SetUniform("u_time", (float)glfwGetTime());
		RenderTriangle();
		shader->StopUse();
	}
	delete sky;
	// 结束程序
	app.Exit();
	return 0;
}