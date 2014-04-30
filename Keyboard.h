#include "SDL.h"

#ifndef KEYBOARD_H
#define KEYBOARD_H

class Keyboard {
public:
	Keyboard();
	void update(); // update keys state
	bool getState(SDLKey); // return key state for specific key
private:
	Uint8* keys;
};

#endif
