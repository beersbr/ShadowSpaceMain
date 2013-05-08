#pragma once

#include <map>
#include <allegro5\allegro5.h>

class InputHandler
{
public:
	~InputHandler(void);

	static InputHandler* Instance();
	bool isKeyDown(const int al_keycode);
	void setKey(const int al_keycode);
	void unsetKey(const int al_keycode);

private:
	InputHandler(void);
	static InputHandler* instance;
	std::map<int, bool> key_states;

};