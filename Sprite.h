// Gets sprites from spritesheets and renders them

#include "SDL.h"
#include "SpriteSheet.h"

#ifndef SPRITE_H
#define SPRITE_H

class Sprite {
public:
	Sprite(SDL_Surface*, int, int, int, bool, bool);

	bool operator==(const Sprite &) const;

	void render(int, int, SDL_Surface*);

	bool isSolid();
	bool isSliding();

private:

	void loadSprite();

	int x, y;					// x and y are the coordinates on the sheet, not pixel coordinates
	SDL_Surface* sheet;
	SDL_Rect sprite;
	bool solid;
	bool sliding;
	bool directional;
	int size;
};

#endif
