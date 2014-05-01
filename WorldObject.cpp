#include "WorldObject.h"

// CONSTRUCTOR

WorldObject::WorldObject(string pathName, int x0, int y0, int w, int h, int xPos, int yPos) 
	:Entity(pathName),
	xSheet(x0 * 16),
	ySheet(y0 * 16),
	width(w * 16),
	height(h * 16)
{
		x = xPos * 16;
		y = yPos * 16;
		load();
}

// PUBLIC METHODS

void WorldObject::render(int xScreen, int yScreen, SDL_Surface* screen) {
	SDL_Rect offset;

	offset.x = xScreen;
	offset.y = yScreen;

	SDL_BlitSurface(sheet.getSurface(), &clippedImage, screen, &offset);	 // renders the image as a given location on the screen	
}																			 // based on provided values

void WorldObject::update(Display* display) {								// necessary method since WorldObject inherits Entity

}

// PRIVATE METHODS

void WorldObject::load() {		// clips image from the spritesheet for rendering

	clippedImage.x = xSheet;
	clippedImage.y = ySheet;
	clippedImage.w = width;
	clippedImage.h = height;

}
