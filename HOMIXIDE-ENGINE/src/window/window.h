#pragma once

struct GLFWwindow;

namespace Window {
	void Initialize(int width, int height, const char* title, bool fullscreen, bool resizable);
	void Shutdown();

	bool WindowIsOpen();
	void SwapBuffers();

	GLFWwindow* GetWindowPointer();
	int GetWindowWidth();
	int GetWindowHeight();
	float GetWindowAspect();
	void SetWindowShouldClose(bool value);
	void SetWindowWidth(int width);
	void SetWindowHeight(int height);
	void SetCursorMode(int value);
	void ToggleFullscreen();
}
