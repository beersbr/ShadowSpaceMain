#include "InputHandler.h"

InputHandler::~InputHandler(void)
{
}

InputHandler* InputHandler::instance = nullptr;

InputHandler* InputHandler::Instance()
{
	if(!InputHandler::instance) InputHandler::instance = new InputHandler();
	return InputHandler::instance;
}

bool InputHandler::isKeyDown(const int al_keycode)
{
	if(key_states[al_keycode]) return key_states[al_keycode];
	return false;
}

void InputHandler::setKey(const int al_keycode)
{
	key_states[al_keycode] = true;
}

void InputHandler::unsetKey(const int al_keycode)
{
	key_states[al_keycode] = false;
}

InputHandler::InputHandler(void)
{
}
