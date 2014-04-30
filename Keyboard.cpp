#include "Keyboard.h"

Keyboard::Keyboard() {
	keys = SDL_GetKeyState(NULL); //initialize key states
}

void Keyboard::update() { //update key states for all keys
	keys = SDL_GetKeyState(NULL);
}

bool Keyboard::getState(SDLKey INDEX) { //return true if INDEX is pressed, 0 if unpressed
	return keys[INDEX];
}
