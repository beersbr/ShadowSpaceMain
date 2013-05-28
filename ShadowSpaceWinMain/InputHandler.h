#pragma once

#include <map>

class InputHandler
{
public:
	~InputHandler(void);

	static InputHandler* Instance();
	bool IsKeyDown(const int al_keycode);
	void SetKey(const int keyCode);
	void UnSetKey(const int keyCode);

private:
	InputHandler(void);
	static InputHandler* instance;
	std::map<int, bool> key_states;

};