// Parent class for all entities that are rendered to the display

#include "SpriteSheet.h"
#include "Display.h"
#include <string>
using namespace std;

#ifndef ENTITY_H
#define ENTITY_H

class Entity {
public:
	Entity(string);
	virtual void update(Display*) = 0;
	virtual void render(int, int, SDL_Surface*) = 0;
	int getX();
	int getY();
	void setLocation(int, int);
protected:
	SpriteSheet sheet;
	int x, y;
	const double g;
};

#endif
