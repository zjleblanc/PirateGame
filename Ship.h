// Handles ship-specific functionality of the player

#include "Entity.h"
#include "Display.h"
#include "Sprite.h"
#include "HealthBar.h"
#include <string>
#include <vector>
using namespace std;

#ifndef SHIP_H
#define SHIP_H

class Ship : public Entity {
public:

	Ship(string);

	void render(int x, int y, SDL_Surface* screen);
	void update(Display* display);

	void setDirection(int);
	void subHealth(int);
	void addHealth(int);

private:

	int direction;
	int maxHealth;
	int currentHealth;
	Sprite left;
	Sprite right;
	Sprite up_1, up_2;
	Sprite down_1, down_2;
	HealthBar shipHealth;
	int animate;
};

#endif
