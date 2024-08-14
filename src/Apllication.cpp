#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <iostream>
#include "include/Application.h"
#include "include/Error.h"

// 单例类型
Application* Application::m_Instance = nullptr;

// 初始化 application 单例类型
Application::Application(uint32_t width, uint32_t height) {
	m_width = width;
	m_height = height;

	// UNIT_MILI;
	// OpenGL 初始化
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);				   // 设置主版本号
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);				   // 设置次版本号
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // 设置核心模式

	m_window = glfwCreateWindow(m_width, m_height, "application", nullptr, nullptr);
	if (!m_window) {
		std::cout << "Failed to create a window.\n";
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(m_window); // 设置该对象为OpenGL的上下文
	// 使用glad加载函数，该函数必须在有上下文的时候才能够正确加载函数
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD.\n";
		exit(EXIT_FAILURE);
	}
}

Application::~Application() {
	free(m_window);
}

Application& Application::GetInstance(uint32_t width, uint32_t height) {
	if (m_Instance) {
		return *m_Instance;
	}
	else {
		m_Instance = new Application(width, height);
		return *m_Instance;
	}
}

uint32_t Application::GetWidth() const { return m_width; }
uint32_t Application::GetHeight() const { return m_height; }
bool Application::LoopGoing() {
	if (glfwWindowShouldClose(m_window)) {
		return false;
	}
	glfwPollEvents();
	glfwSwapBuffers(m_window);
	return true;
}
void Application::Exit() {
	glfwTerminate();
}


// 实现窗口大小回调
void Application::WhenWindowResize(ResizeFunc correspond) {
	m_resizeCall = correspond;
	glfwSetFramebufferSizeCallback(m_window, s_ResizeCallback);
}
void Application::s_ResizeCallback(GLFWwindow* window, int width, int height) {
	m_Instance->m_resizeCall(width, height);
}

// 实现键盘响应回调
void Application::WhenKeyTrigger(KeyFunc correspond) {
	m_keyCall = correspond;
	glfwSetKeyCallback(m_window, s_KeyCallback);
}
void Application::s_KeyCallback(GLFWwindow* window, int key, int scanCode, int action, int mods) {
	m_Instance->m_keyCall(key, scanCode, action, mods);
}

// 实现鼠标点击响应回调
void Application::WhenMouseClick(MouseFunc_click correspond) {
	m_mouseCall_click = correspond;
	glfwSetMouseButtonCallback(m_window, s_MouseCallback_click);
}
void Application::s_MouseCallback_click(GLFWwindow* window, int button, int action, int mods) {
	m_Instance->m_mouseCall_click(button, action, mods);
}

// 实现鼠标滚动响应回调
void Application::WhenMouseScroll(MouseFunc_scroll correspond) {
	m_mouseCall_scroll = correspond;
	glfwSetScrollCallback(m_window, s_MouseCallback_scroll);
}
void Application::s_MouseCallback_scroll(GLFWwindow* window, double x, double y) {
	m_Instance->m_mouseCall_scroll(x, y);
}

// 实现鼠标滑动响应回调
void Application::WhenMouseMove(MouseFunc_move correspond) {
	m_mouseCall_move = correspond;
	glfwSetCursorPosCallback(m_window, s_MouseCallback_move);
}
void Application::s_MouseCallback_move(GLFWwindow* window, double x, double y) {
	m_Instance->m_mouseCall_move(x, y);
}