#include "window.h"

#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Window {
	GLFWwindow* m_window = nullptr;
	GLFWmonitor* m_monitor = nullptr;
	const GLFWvidmode* m_mode = nullptr;
	int m_fullscreenWidth = 0;
	int m_fullscreenHeight = 0;
	int m_windowedWidth = 0;
	int m_windowedHeight = 0;
	int m_currentWidth = 0;
	int m_currentHeight = 0;
	const char* m_title = nullptr;
	bool m_fullscreen = false;

	void Initialize(int width, int height, const char* title, bool fullscreen, bool resizable) {
		int glfw_resizable = GLFW_FALSE;
		if (resizable) {
			glfw_resizable = GLFW_TRUE;
		}
		
		glfwInit();

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_RESIZABLE, glfw_resizable);

		m_monitor = glfwGetPrimaryMonitor();
		m_mode = glfwGetVideoMode(m_monitor);

		m_fullscreenWidth = m_mode->width;
		m_fullscreenHeight = m_mode->height;
		m_windowedWidth = width;
		m_windowedHeight = height;

		glfwWindowHint(GLFW_RED_BITS, m_mode->redBits);
		glfwWindowHint(GLFW_GREEN_BITS, m_mode->greenBits);
		glfwWindowHint(GLFW_BLUE_BITS, m_mode->blueBits);
		glfwWindowHint(GLFW_REFRESH_RATE, m_mode->refreshRate);

		m_fullscreen = fullscreen;
		if (m_fullscreen) {
			// WINDOWED FULLSCREEN - not really fullscreen
			m_currentWidth = m_fullscreenWidth;
			m_currentHeight = m_fullscreenHeight;
			m_window = glfwCreateWindow(m_currentWidth, m_currentHeight, title, m_monitor, nullptr);
			if (!m_window) {
				std::cerr << "Failed to create GLFW window\n";
				glfwTerminate();
			}
		}
		else {
			m_currentWidth = m_windowedWidth;
			m_currentHeight = m_windowedHeight;
			m_window = glfwCreateWindow(m_currentWidth, m_currentHeight, title, nullptr, nullptr);
			if (!m_window) {
				std::cerr << "Failed to create GLFW window\n";
				glfwTerminate();
			}
			glfwSetWindowPos(m_window, (m_mode->width - m_currentWidth) / 2, (m_mode->height - m_currentHeight) / 2);
		}

		glfwMakeContextCurrent(m_window);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
			std::cerr << "Failed to initialize GLAD\n";
			glfwTerminate();
		}

		glViewport(0, 0, m_currentWidth, m_currentHeight);
	}

	void Shutdown() {
		glfwDestroyWindow(m_window);
		glfwTerminate();
	}

	bool WindowIsOpen() {
		return !glfwWindowShouldClose(m_window);
	}

	void SwapBuffers() {
		glfwSwapBuffers(m_window);
	}

	GLFWwindow* GetWindowPointer() {
		return m_window;
	}

	int GetWindowWidth() {
		return m_currentWidth;
	}

	int GetWindowHeight() {
		return m_currentHeight;
	}

	float GetWindowAspect() {
		return static_cast<float>(m_currentWidth) / static_cast<float>(m_currentHeight);
	}

	void SetWindowShouldClose(bool value) {
		glfwSetWindowShouldClose(m_window, value);
	}

	void SetWindowWidth(int width) {
		m_currentWidth = width;
	}

	void SetWindowHeight(int height) {
		m_currentHeight = height;
	}

	void SetCursorMode(int value) {
		glfwSetInputMode(m_window, GLFW_CURSOR, value);
	}

	void ToggleFullscreen() {
		if (m_fullscreen) {
			SetWindowWidth(m_windowedWidth);
			SetWindowHeight(m_windowedHeight);
			glfwSetWindowMonitor(m_window, nullptr, (m_mode->width - m_currentWidth) / 2, (m_mode->height - m_currentHeight) / 2, m_currentWidth, m_currentHeight, 0);
			m_fullscreen = false;
		}
		else {
			SetWindowWidth(m_fullscreenWidth);
			SetWindowHeight(m_fullscreenHeight);
			glfwSetWindowMonitor(m_window, m_monitor, 0, 0, m_currentWidth, m_currentHeight, m_mode->refreshRate);
			m_fullscreen = true;
		}
	}
}
