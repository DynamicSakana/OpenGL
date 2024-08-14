#include <GLFW/glfw3.h>
#include <include/Error.h>
#include <assert.h>
#include <iostream>

void ResizeCallback(int width, int height) {
	// 调整窗口大小
	CALL(glViewport(0, 0, width, height));
}

// 键盘消息响应函数
// key 字母按键码，如果按下的是字符键，则会返回对应字符的ASCII码，如果是功能键，则会返回大于127的值
// scanCode 物理按键码
// action 按下还是抬起
// mod 是否和 ctrl 或 shift 一起按下
void keyCallback(int key, int scanCode, int action, int mods) {
	if (key < 128) {
		if (action)
			std::cout << "Press ";
		else
			std::cout << "Release ";
		std::cout << "key : '" << (char)key << "' while ";
		switch (mods) {
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
	else {
		// 按下按键为1，松开按键为0
		if (action == GLFW_PRESS) {
			std::cout << "Pressed a function key.\n";
		}
		else if (action == GLFW_RELEASE) {
			std::cout << "Released a function key.\n";
		}
	}
}

// 鼠标点击响应函数
void MouseCallback(int button, int action, int mods) {
	if (action == GLFW_PRESS)
		std::cout << "Pressed ";
	else if (action == GLFW_RELEASE)
		std::cout << "Release ";

	switch (button) {
	case GLFW_MOUSE_BUTTON_LEFT:
		std::cout << "left button of mouse pressed, ";
		break;
	case GLFW_MOUSE_BUTTON_RIGHT:
		std::cout << "right button of mouse pressed, ";
		break;
	case GLFW_MOUSE_BUTTON_MIDDLE:
		std::cout << "middle button of mouse pressed, ";
		break;
	default:
		break;
	}

	switch (mods) {
	case GLFW_MOD_CONTROL:
		std::cout << "while Ctrl pressed.\n";
		break;
	case GLFW_MOD_SHIFT:
		std::cout << "while Shift pressed.\n";
		break;
	default:
		std::cout << "while nothing else pressed.\n";
		break;
	}
}

// 鼠标滚轮响应函数
void MouseScroll(double x, double y) {
	std::cout << "Scroll: x offset: " << x << ", y offset: " << y << ".\n";
}

// 鼠标滚轮响应函数
void MouseMove(double x, double y) {
	std::cout << "Mouse move: x offset: " << x << ", y offset: " << y << ".\n";
}