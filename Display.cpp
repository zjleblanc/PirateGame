#include "Display.h"
#include <math.h>
#include <string>

Display::Display(int WIDTH, int HEIGHT) 
	:terrainSheet( "Terrain.png"),

	ice(terrainSheet.getSurface(), 0, 0, false, true),
	grass(terrainSheet.getSurface(), 0, 1, false, false),
	flower(terrainSheet.getSurface(), 1, 1, false, false),
	bush(terrainSheet.getSurface(), 2, 1, true, false), 

	mainArea(1000,1000) {

		width = WIDTH;
		height = HEIGHT;
		xOffset = 0;
		yOffset = 0;

}

int Display::getWidth() {
	return width;
}

int Display::getHeight() {
	return height;
}

void Display::setOffsets(int x, int y) {
	xOffset = x;
	yOffset = y;
}

void Display::renderTile(int x, int y, Sprite* sprite, SDL_Surface* screen) {
	int xRender = x - xOffset % 16;
	int yRender = y - yOffset % 16;

	(*sprite).render(xRender, yRender, screen);
}

void Display::render(SDL_Surface* screen) {
	int xTileMin = xOffset >> 4;
	int yTileMin = yOffset >> 4;
	int xTileMax = (xOffset + width + 16) >> 4;
	int yTileMax = (yOffset + height + 16) >> 4;

	for(int y = yTileMin; y < yTileMax; y++) {
		for(int x = xTileMin; x < xTileMax; x++) {
			renderTile(((x - xTileMin) << 4), ((y - yTileMin) << 4), getSprite(x, y), screen);
		}
	}
}

Sprite* Display::getSprite(int x, int y) {
	if(x < 0 || y < 0 || x >= mainArea.getWidth() || y >= mainArea.getHeight()) {
		return &grass;
	}

	switch(mainArea.getTile(x, y)) {
	case 'G': 
		return &grass;
		break;
	case 'I':
		return &ice;
		break;
	case 'A':
		return &flower;
		break;
	case 'B':
		return &bush;
		break;
	}
}

char* Display::getCurrentTile() {
	int xTile = (xOffset + width / 2) >> 4;
	int yTile = (yOffset + height / 2) >> 4;

	char tile = '&';

	if((xTile >= 0) && (yTile >= 0) && (xTile < mainArea.getWidth()) && (yTile < mainArea.getHeight())) {
		tile = mainArea.getTile(xTile, yTile);
	}

	switch(tile) {
	case 'G':
		return "grass";
		break;
	case 'I':
		return "ice";
		break;
	case 'A':
		return "flower";
		break;
	case 'B':
		return "bush";
		break;
	default:
		return "tile not found";
	}
}
