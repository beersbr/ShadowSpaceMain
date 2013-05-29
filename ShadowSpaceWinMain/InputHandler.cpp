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

bool InputHandler::IsKeyDown(const int keycode)
{
	if(key_states[keycode]) return key_states[keycode];
	return false;
}

bool InputHandler::IsKeyPressed(const int keycode)
{
	if(key_pressed_states[keycode]) return key_pressed_states[keycode];
	return false;
}

void InputHandler::SetKey(const int keycode)
{
	key_states[keycode] = true;
}

void InputHandler::UnSetKey(const int keycode)
{
	key_states[keycode] = false;
	key_pressed_states[keycode] = true;
}

void InputHandler::ClearStates(void)
{
	key_pressed_states.clear();
}

InputHandler::InputHandler(void)
{
}
