#include "Mouse.h"
#include "Player.h"

Mouse::Mouse() {
	x = 0, y = 0; //initialize x and y position to zero
}

void Mouse::update() { //update mouse location
	if(SDL_PollEvent(&mouseEvent)) {
		if(mouseEvent.type == SDL_MOUSEMOTION) {
			x = mouseEvent.motion.x;
			y = mouseEvent.motion.y;
		}
	}
}

int Mouse::buttonPressed(){ // check for button pressed
	SDL_PumpEvents();
	if(SDL_GetMouseState(&x,&y)&SDL_BUTTON(1)) return 1;		//left button pressed
	else if(SDL_GetMouseState(&x,&y)&SDL_BUTTON(3)) return 3;  //right button pressed
	else return 0; //no button / middle pressed
}

int Mouse::buttonReleased(int button){ // check to see if a specific button is released
	if(button==buttonPressed())
		return 0;
	else
		return 1;
}


int Mouse::getX() {
	return x;
}

int Mouse::getY() {
	return y;
}

int Mouse::getXtile(Player *player){ // return x position in terms of tiles
		return player->getX()/16 - 20 + Mouse::getX()/16;
}

int Mouse::getYtile(Player *player){ // return y position in terms of tiles
		return player->getY()/16 - 15 + Mouse::getY()/16;
}
