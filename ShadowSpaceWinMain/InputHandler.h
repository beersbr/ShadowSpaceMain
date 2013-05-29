#pragma once

#include <map>

class InputHandler
{
public:
	~InputHandler(void);

	static InputHandler* Instance();
	bool IsKeyDown(const int keycode);
	bool IsKeyPressed(const int keycode);
	void SetKey(const int keyCode);
	void UnSetKey(const int keyCode);

	void ClearStates(void);

private:
	InputHandler(void);
	static InputHandler* instance;
	std::map<int, bool> key_states;
	std::map<int, bool> key_pressed_states;
};