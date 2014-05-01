// Handles logic and rendering of iceberg enemies

#include "AI_Unit.h"

#ifndef ICEBERG_H
#define ICEBERG_H

class Iceberg : public AI_Unit {
public:

	Iceberg(string, int, int, int, int, int);

	void update(Display*);
	void runAI(Player*, Display*);
	void renderAttrib(SDL_Surface*, Display*, Player*);

private:

	void chase(Player*, Display*);
	void chill(Player*, Display*);

	bool chasing;
	bool chillin;
	bool engaged;
	bool moving;
	Sprite shattered;
};

#endif 
