#include "SDL.h"

#ifndef KEYBOARD_H
#define KEYBOARD_H

class Keyboard {
public:
	Keyboard();
	void update(); // update keys state
	bool getState(SDLKey); // check if SDLKEY is pressed or unpressed
private:
	Uint8* keys;
};

#endif
