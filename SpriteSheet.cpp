#include "SpriteSheet.h"
#include "SDL_image.h"
#include "SDL.h"

// CONSTRUCTOR

SpriteSheet::SpriteSheet(string fileName) {
	path = fileName;
	sheet = loadSheet();
}

// DECONSTRUCTOR

SpriteSheet::~SpriteSheet() {
	SDL_FreeSurface(sheet);
}

// PUBLIC METHODS

bool SpriteSheet::operator==(const SpriteSheet& testSheet) const {		// used for sprite equivalence checking
	if(!path.compare(testSheet.path)) {
		return true;
	}
	return false;
}

// GETTERS AND SETTERS

SDL_Surface* SpriteSheet::getSurface() {								// returns the sheet's surface, used to render sprites individually
	return sheet;
}

string SpriteSheet::getPath() {
	return path;
}

// PRIVATE METHODS

SDL_Surface* SpriteSheet::loadSheet() {					// loads images of any format and returns a pointer to it, run upon instantiation
	
	SDL_Surface* loadedImage = NULL;
	SDL_Surface* optImage = NULL;

	loadedImage = IMG_Load(path.c_str());

	if(loadedImage != NULL) {
		optImage = SDL_DisplayFormat(loadedImage);
		SDL_FreeSurface(loadedImage);
	}

	if(optImage) {										// colorkeying of FF00FF is run upon loading
		colorkey = SDL_MapRGB(optImage->format, 0xFF, 0x00, 0xFF);
		SDL_SetColorKey(optImage, SDL_SRCCOLORKEY, colorkey);
	}

	return optImage;
}
