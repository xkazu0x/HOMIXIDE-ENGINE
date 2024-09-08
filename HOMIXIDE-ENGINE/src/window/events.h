#pragma once

namespace Events {
	void Initialize();
	void PollEvents();

	bool KeyPressed(int keycode);
	bool KeyDown(int keycode);

	bool ButtonClicked(int button);
	bool ButtonDown(int button);

	void ToggleCursor();
	bool GetCursorLocked();

	float GetDeltaX();
	float GetDeltaY();
}
