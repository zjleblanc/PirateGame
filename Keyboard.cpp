#include "Keyboard.h"

Keyboard::Keyboard() {
	keys = SDL_GetKeyState(NULL);
}

void Keyboard::update() {
	keys = SDL_GetKeyState(NULL);
}

bool Keyboard::getState(SDLKey INDEX) {
	return keys[INDEX];
}
