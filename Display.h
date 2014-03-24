#include "SpriteSheet.h"
#include "Sprite.h"
#include "Area.h"
#include "SDL.h"
#include "SDL_image.h"
#include <string>

#ifndef DISPLAY_H
#define DISPLAY_H

class Display {
public:
	Display(int, int);
	int getWidth();
	int getHeight();
	void setOffsets(int, int);
	void render(SDL_Surface*);
	char* getCurrentTile();
	Sprite* getSprite(int x, int y);
private:
	void renderTile(int, int, Sprite*, SDL_Surface*);
	int width, height;
	int xOffset, yOffset;
	SpriteSheet terrainSheet;
	Sprite ice;
	Sprite grass;
	Sprite flower;
	Sprite bush;
	Area mainArea;
};

#endif
