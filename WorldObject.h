// Handles rendering of objects placed over the map

#include "Entity.h"
#include "Display.h"
#include <string>
#include <vector>
using namespace std;

#ifndef WORLDOBJECT_H
#define WORLDOBJECT_H

class WorldObject : public Entity {
public:

	WorldObject(string, int, int, int, int, int, int);

	void update(Display*);
	void render(int, int, SDL_Surface*);

private:

	void load();

	int xSheet, ySheet;
	int width, height;
	SDL_Rect clippedImage;
};

#endif
