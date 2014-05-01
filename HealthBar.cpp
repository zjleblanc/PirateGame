#include "HealthBar.h"
using namespace std;

// CONSTRUCTOR

HealthBar::HealthBar(string pathName, int hitpoints) 
	:Entity(pathName)
{
	maxHP = hitpoints;
	currentHP = maxHP;
	load();
}

// PUBLIC METHODS

void HealthBar::update(Display* display) {					// must be defined, since HealthBar inherits Entity

}

void HealthBar::render(int x, int y, SDL_Surface* screen) {
	SDL_Rect offset;

	offset.x = x;
	offset.y = y;

	SDL_BlitSurface(sheet.getSurface(), &bar, screen, &offset);						// renders full health bar

	int damageCtrs = (int)((maxHP - currentHP) / ((double)maxHP / 28));				// gets number of damage ticks necessary to render over full bar

	for(int i = 28; i > 28 - damageCtrs; i--) {
		offset.x = x + i + 1;
		offset.y = y + 6;

		SDL_BlitSurface(sheet.getSurface(), &damageTick, screen, &offset);			// render a single damage tick
	}
}

//	GETTERS AND SETTERS

int HealthBar::getHealth() {
	return currentHP;
}

void HealthBar::subHealth(int damage) {					// remove health from the bar, minimum health -> 0
	if((currentHP - damage) > 0) {							
		currentHP -= damage;
	} else {
		currentHP = 0;
	}
}

void HealthBar::addHealth(int healing) {				// add health to the bar, maximum health -> maxHP
	if(currentHP + healing >= maxHP) {
		currentHP = maxHP;
	} else {
		currentHP += healing;
	}
}

// PRIVATE METHODS

void HealthBar::load() {								// sets the SDL_Rect specs for clipping bar images from the spritesheet
	bar.x = 0;											// called on instantiation
	bar.y = 0;
	bar.w = 32;
	bar.h = 16;

	damageTick.x = 0;
	damageTick.y = 16;
	damageTick.w = 1;
	damageTick.h = 4;
}
