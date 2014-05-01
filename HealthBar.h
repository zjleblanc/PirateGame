// Handles rendering of the health bar above ships and enemies based on health

#include "Entity.h"
#include "SpriteSheet.h"
#include "Display.h"
#include <string>
using namespace std;

#ifndef HEALTHBAR_H
#define HEALTHBAR_H

class HealthBar : public Entity {
public:
	HealthBar(string, int);
	void update(Display*);
	void render(int, int, SDL_Surface*);
	int getHealth();
	void subHealth(int);
	void addHealth(int);
private:
	void load();
	int maxHP;
	int currentHP;
	SDL_Rect bar, damageTick;
};

#endif 
