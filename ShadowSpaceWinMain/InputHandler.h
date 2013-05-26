#pragma once

#include <map>

class InputHandler
{
public:
	~InputHandler(void);

	static InputHandler* Instance();
	bool isKeyDown(const int al_keycode);
	void setKey(const int keyCode);
	void unsetKey(const int keyCode);

private:
	InputHandler(void);
	static InputHandler* instance;
	std::map<int, bool> key_states;

};