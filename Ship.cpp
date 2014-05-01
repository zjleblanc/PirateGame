#include "Ship.h"

// CONSTRUCTOR

Ship::Ship(string pathName) 
	: Entity(pathName),
	left(sheet.getSurface(), 0, 0, 32, true, false),
	right(sheet.getSurface(), 0, 1, 32, true, false),
	up_1(sheet.getSurface(), 0, 2, 32, true, false),				// loads in all of the ship's directional sprites
	down_1(sheet.getSurface(), 0, 4, 32, true, false),
	up_2(sheet.getSurface(), 0, 3, 32, true, false),
	down_2(sheet.getSurface(), 0, 5, 32, true, false),
	shipHealth("Health.png", 250)
{
	animate = 0;
}

// PUBLIC METHODS

void Ship::render(int x, int y, SDL_Surface* screen) {
	
	switch(direction) {					// renders the ship's sprite based on the direction and time, animation counter
	case 0:
		if(animate % 70 < 35) {
			up_1.render(x,y,screen);
		} else {
			up_2.render(x,y,screen);
		}
		break;
	case 1:
		left.render(x,y,screen);
		break;
	case 2:
		if(animate % 70 < 35) {
			down_1.render(x,y,screen);
		} else {
			down_2.render(x,y,screen);
		}
		break;
	case 3:
		right.render(x,y,screen);
		break;
	}
	shipHealth.render(x, y - 16, screen);					// renders the healthbar one tile above the ship on the display
}

void Ship::update(Display* display) {						// update the animation count on a fixed timescale
	animate++;
}

// GETTERS AND SETTERS

void Ship::setDirection(int newDir) {
	direction = newDir;
}

void Ship::subHealth(int damage) {
	shipHealth.subHealth(damage);
}

void Ship::addHealth(int healing) {
	shipHealth.addHealth(healing);
}
