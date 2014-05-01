// Handles logic and rendering of pirate enemies

#include "AI_Unit.h"
#include "Projectile.h"

#ifndef PIRATE_H
#define PIRATE_H

class Pirate : public AI_Unit {
public:

	Pirate(string, int, int, int, int, int);
	~Pirate();

	void renderAttrib(SDL_Surface*, Display*, Player*);
	void update(Display*);
	void runAI(Player*, Display*);

private:

	void chase(Player*, Display*);
	void chill(Player*, Display*);
	void evade(Player*, Display*);
	void position(Player*, Display*);
	void attack(Player*);
	void flee(Player*, Display*);

	bool chillin, chasing, evading, positioning, attacking, fleeing;
	bool moving;
	Projectile* left_projectile;
	Projectile* right_projectile;
	Sprite underWater;
};

#endif
