#include "SpriteSheet.h"
#include "SDL_image.h"
#include "SDL.h"

SpriteSheet::SpriteSheet(string fileName) {
	path = fileName;
	sheet = loadSheet();
}

SpriteSheet::~SpriteSheet() {
	SDL_FreeSurface(sheet);
}

SDL_Surface* SpriteSheet::loadSheet() {
	
	SDL_Surface* loadedImage = NULL;
	SDL_Surface* optImage = NULL;

	loadedImage = IMG_Load(path.c_str());

	if(loadedImage != NULL) {
		optImage = SDL_DisplayFormat(loadedImage);
		SDL_FreeSurface(loadedImage);
	}

	if(optImage) {
		colorkey = SDL_MapRGB(optImage->format, 0xFF, 0x00, 0xFF);
		SDL_SetColorKey(optImage, SDL_SRCCOLORKEY, colorkey);
	}

	return optImage;
}

SDL_Surface* SpriteSheet::getSurface() {
	return sheet;
}
