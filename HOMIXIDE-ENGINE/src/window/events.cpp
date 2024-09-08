#include "Events.h"
#include "window.h"

#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define _MOUSE_BUTTONS 1024

namespace Events {
	bool* m_keys = nullptr;
	unsigned int* m_frames = nullptr;
	unsigned int m_current = 0;
	float m_x = 0.0f;
	float m_y = 0.0f;
	float m_dx = 0.0f;
	float m_dy = 0.0f;
	bool m_cursor_locked = false;
	bool m_cursor_started = false;

	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
		if (action == GLFW_PRESS) {
			m_keys[key] = true;
			m_frames[key] = m_current;
		}
		else if (action == GLFW_RELEASE) {
			m_keys[key] = false;
			m_frames[key] = m_current;
		}
	}

	void mouse_button_callback(GLFWwindow* window, int button, int action, int mode) {
		if (action == GLFW_PRESS) {
			m_keys[_MOUSE_BUTTONS + button] = true;
			m_frames[_MOUSE_BUTTONS + button] = m_current;
		}
		else if (action == GLFW_RELEASE) {
			m_keys[_MOUSE_BUTTONS + button] = false;
			m_frames[_MOUSE_BUTTONS + button] = m_current;
		}
	}

	void cursor_position_callback(GLFWwindow* window, double xpos, double ypos) {
		if (m_cursor_started) {
			m_dx += static_cast<float>(xpos) - m_x;
			m_dy += static_cast<float>(ypos) - m_y;
		}
		else {
			m_cursor_started = true;
		}

		m_x = static_cast<float>(xpos);
		m_y = static_cast<float>(ypos);
	}

	void window_size_callback(GLFWwindow* window, int width, int height) {
		glViewport(0, 0, width, height);
		Window::SetWindowWidth(width);
		Window::SetWindowHeight(height);
	}

	void Initialize() {
		GLFWwindow* window = Window::GetWindowPointer();
		m_keys = new bool[1032];
		m_frames = new unsigned int[1032];

		memset(m_keys, false, 1032 * sizeof(bool));
		memset(m_frames, 0, 1032 * sizeof(unsigned int));

		glfwSetKeyCallback(window, key_callback);
		glfwSetMouseButtonCallback(window, mouse_button_callback);
		glfwSetCursorPosCallback(window, cursor_position_callback);
		glfwSetWindowSizeCallback(window, window_size_callback);
	}

	void PollEvents() {
		m_current++;
		m_dx = 0.0f;
		m_dy = 0.0f;

		glfwPollEvents();
	}

	bool KeyPressed(int keycode) {
		if (keycode < 0 || keycode >= _MOUSE_BUTTONS)
			return false;
		return m_keys[keycode] && m_frames[keycode] == m_current;
	}

	bool KeyDown(int keycode) {
		if (keycode < 0 || keycode >= _MOUSE_BUTTONS)
			return false;
		return m_keys[keycode];
	}

	bool ButtonClicked(int button) {
		int index = _MOUSE_BUTTONS + button;
		return m_keys[index] && m_frames[index] == m_current;
	}

	bool ButtonDown(int button) {
		int index = _MOUSE_BUTTONS + button;
		return m_keys[index];
	}

	void ToggleCursor() {
		m_cursor_locked = !m_cursor_locked;
		Window::SetCursorMode(m_cursor_locked ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL);
	}

	bool GetCursorLocked() {
		return m_cursor_locked;
	}

	float GetDeltaX(){
		return m_dx;
	}

	float GetDeltaY() {
		return m_dy;
	}
}