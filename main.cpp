// 注意glad的头文件必须在glfw头文件之前
extern "C" {
#include <glad/glad.h>
}
#include <GLFW/glfw3.h>
#include <TIMER/Timer.h>
#include <iostream>

// 窗体大小变化响应函数
void frameBufferSizeCallBack(GLFWwindow *window, int width, int height) {
	std::cout << "Window size set to : " << width << ", " << height << ".\n";
}

// 键盘消息响应函数
// key 字母按键码
// scanCode 物理按键码
// action 按下还是抬起
// mod 是否和 ctrl 或 shift 一起按下
void keyCallBack(GLFWwindow *window, int key, int scanCode, int action, int mods)
{
	if (key < 128)
	{
		if (action)
			std::cout << "Press ";
		else
			std::cout << "Release ";
		std::cout << "key : '" << (char)key << "' while ";
		switch (mods)
		{
		case GLFW_MOD_SHIFT:
			std::cout << "Shift pressed.\n";
			break;
		case GLFW_MOD_CONTROL:
			std::cout << "Ctrl pressed.\n";
			break;
		default:
			std::cout << "nothing else pressed.\n";
			break;
		}
	}
	else
	{
		// 按下按键为1，松开按键为0
		if (action == GLFW_PRESS)
		{
			std::cout << "Pressed a function key.\n";
		}
		else if (action == GLFW_RELEASE)
		{
			std::cout << "Released a function key.\n";
		}
	}
}

int main(int argc, char **argv)
{

	// UNIT_MILI;

	// OpenGL 初始化
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);				   // 设置主版本号
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);				   // 设置次版本号
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // 设置核心模式

	// 构造窗体对象
	GLFWwindow *window = glfwCreateWindow(800, 600, "test", nullptr, nullptr);
	glfwMakeContextCurrent(window); // 设置该对象为OpenGL的绘制窗口

	// 设置监听窗体大小变化
	glfwSetFramebufferSizeCallback(window, frameBufferSizeCallBack);

	// 设置监听键盘消息
	glfwSetKeyCallback(window, keyCallBack);

	// 使用glad加载函数
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD.\n";
		exit(EXIT_FAILURE);
	}
	// 执行窗口循环
	while (!glfwWindowShouldClose(window))
	{
		// SCOPE_TIMER

		glfwPollEvents(); // 接收并分发消息
	}

	// 结束程序
	glfwTerminate();

	return 0;
}