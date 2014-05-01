#include "Sprite.h"

// CONSTRUCTOR

Sprite::Sprite(SDL_Surface* spriteSheet, int xcoord, int ycoord, int sprSize, bool solidTile, bool slidingTile) {

	x = xcoord;
	y = ycoord;
	size = sprSize;
	solid = solidTile;
	sliding = slidingTile;
	sheet = spriteSheet;
	loadSprite();

}

// PUBLIC METHODS

bool Sprite::operator==(const Sprite &sprite) const {						// overrides == for sprite comparison/ location checking
	if((x == sprite.x) && (y == sprite.y) && (sheet == sprite.sheet)) {
		return true;
	}
	return false;
}

void Sprite::render(int xScreen, int yScreen, SDL_Surface* destination) {		// renders the sprite at a given location on the screen
	SDL_Rect screenOffset;
	
	screenOffset.x = xScreen;
	screenOffset.y = yScreen;

	SDL_BlitSurface(sheet, &sprite, destination, &screenOffset);
}

// GETTERS AND SETTERS

bool Sprite::isSolid() {				// used for collision detection with the map
	return solid;
}

bool Sprite::isSliding() {				// used for sliding motion
	return sliding;
}

// PRIVATE METHODS

void Sprite::loadSprite() {
	sprite.x = x * size;					// converts to pixel precision
	sprite.y = y * size;					// converts to pixel precision
	sprite.w = size;
	sprite.h = size;
}
