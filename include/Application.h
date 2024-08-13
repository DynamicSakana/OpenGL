#pragma once
#include <iostream>

#define app Application::GetInstance()

class GLFWwindow;

// 封装application单例类（表示当前窗口）
class Application {
	using ResizeFunc = void(*)(int, int);
	using KeyFunc = void(*)(int, int, int, int);
	using MouseFunc_scroll = void(*)(double, double);
	using MouseFunc_click = void(*)(int, int, int);
	using MouseFunc_move = void(*)(double, double);

public:
	~Application();
	static Application& GetInstance(uint32_t = 1280, uint32_t = 720);

	uint32_t GetWidth() const;
	uint32_t GetHeight() const;

	bool LoopGoing();
	void Exit();

	void WhenWindowResize(ResizeFunc);
	void WhenKeyTrigger(KeyFunc);
	void WhenMouseScroll(MouseFunc_scroll);
	void WhenMouseClick(MouseFunc_click);
	void WhenMouseMove(MouseFunc_move);

private:
	// 将响应函数封装为静态函数，因为只有静态函数能够被gflw监听函数调用（glfw是C语言库）
	inline static void s_ResizeCallback(GLFWwindow*, int, int);
	inline static void s_KeyCallback(GLFWwindow*, int, int, int, int);
	inline static void s_MouseCallback_click(GLFWwindow*, int, int, int);
	inline static void s_MouseCallback_scroll(GLFWwindow*, double, double);
	inline static void s_MouseCallback_move(GLFWwindow*, double, double);


private:
	// 该函数不能被外界调用，代表这个类不能被new运算符创建，或者拷贝
	Application(uint32_t, uint32_t);
	Application(const Application&) = delete;

	static Application* m_Instance;
	uint32_t m_width;
	uint32_t m_height;
	GLFWwindow* m_window;

	ResizeFunc m_resizeCall;
	KeyFunc m_keyCall;
	MouseFunc_click m_mouseCall_click;
	MouseFunc_scroll m_mouseCall_scroll;
	MouseFunc_move m_mouseCall_move;
};

