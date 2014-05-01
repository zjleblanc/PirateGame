// Loads in spritesheets from image files

#include "SDL_image.h"
#include <iostream>
#include <string>
using namespace std;

#ifndef SPRITESHEET_H
#define SPRITESHEET_H
	
class SpriteSheet {
public:

	SpriteSheet(string);
	~SpriteSheet();

	bool operator==(const SpriteSheet &) const;

	string getPath();
	SDL_Surface* getSurface();

private:

	SDL_Surface* loadSheet();

	Uint32 colorkey;
	string path;
	int sheetSize;
	SDL_Surface* sheet;
};

#endif
