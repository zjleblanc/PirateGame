#include "Keyboard.h"

// CONSTRUCTOR

Keyboard::Keyboard() {
	keys = SDL_GetKeyState(NULL);
}

//PUBLIC METHODS

void Keyboard::update() {				// update the array for constant evaluation
	keys = SDL_GetKeyState(NULL);
}

bool Keyboard::getState(SDLKey INDEX) {
	return keys[INDEX];
}
