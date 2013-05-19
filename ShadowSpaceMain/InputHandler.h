#pragma once

#include <map>
#include <allegro5\allegro5.h>
#include <allegro5\joystick.h>

// From: http://wiki.allegro.cc/index.php?title=Xbox_controller
class XboxController{
public:
    // axis values
    float left_stick_x;
    float left_stick_y;
    float left_trigger;
    float right_stick_x;
    float right_stick_y;
    float right_trigger;
    float dpad_x;
    float dpad_y;
 
    // buttons pressed?
    bool button_a;
    bool button_b;
    bool button_x;
    bool button_y;
    bool button_left_stick;
    bool button_right_stick;
    bool button_left_shoulder;
    bool button_right_shoulder;
    bool button_start;
    bool button_back;
    bool button_xbox;
 
    // reference to the underlying joystick object
    ALLEGRO_JOYSTICK *joy;

public:
	void xc_clear_state(void);

};

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