#include "Mouse.h"

Mouse::Mouse() {
	button = SDL_GetMouseState(&x,&y);
}

void Mouse::update() {
	button = SDL_GetMouseState(&x,&y);
}

bool Mouse::isLeftPressed() {
	return ( SDL_GetMouseState(&x,&y) & SDL_BUTTON(1) );
}

bool Mouse::isRightPressed() {
	return ( SDL_GetMouseState(&x,&y) & SDL_BUTTON(3) );
}

int Mouse::getX(){
		return x;
}

int Mouse::getY(){
		return y;
}
