// Handles input from the keyboard for a class

#include "SDL.h"

#ifndef KEYBOARD_H
#define KEYBOARD_H

class Keyboard {
public:
	Keyboard();
	void update();
	bool getState(SDLKey);
private:
	Uint8* keys;
};

#endif
