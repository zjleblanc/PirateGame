#include "Display.h"
#include <iostream>
#include <cmath>
#include <sstream>
#include <string>
using namespace std;

// CONSTRUCTOR

Display::Display(int WIDTH, int HEIGHT) 
	:terrainSheet( "Terrain.png" ),									// main spritesheet to be used for the map display

	ice(terrainSheet.getSurface(), 0, 0, 16, false, true),
	grass(terrainSheet.getSurface(), 0, 1, 16, false, false),
	flower(terrainSheet.getSurface(), 1, 1, 16, false, false),
	flower2(terrainSheet.getSurface(), 1, 3, 16, false, false),
	flower3(terrainSheet.getSurface(), 2, 3, 16, false, false),
	flower4(terrainSheet.getSurface(), 2, 4, 16, false, false),		// instantiates (statically) all sprites that are a part of the map
	bush(terrainSheet.getSurface(), 2, 1, 16, true, false), 
	sand(terrainSheet.getSurface(), 3, 1, 16, false, false),
	water1(terrainSheet.getSurface(), 5, 1, 16, true, false),
	water2(terrainSheet.getSurface(), 4, 0, 16, true, false),
	fence_front(terrainSheet.getSurface(), 0, 2, 16, true, false),
	fence_left(terrainSheet.getSurface(), 0, 3, 16, true, false),
	fence_right(terrainSheet.getSurface(), 0, 4, 16, true, false),
	sand_left(terrainSheet.getSurface(), 3, 0, 16, false, false),
	sand_right(terrainSheet.getSurface(), 2, 0, 16, false, false),
	sand_down(terrainSheet.getSurface(), 5, 0, 16, false, false),
	estuary(terrainSheet.getSurface(), 4, 10, 16, false, false),
	estuary_down(terrainSheet.getSurface(), 4, 11, 16, false, false),
	dock(terrainSheet.getSurface(), 9, 10, 16, false, false),
	dock_left(terrainSheet.getSurface(), 8, 10, 16, false, false),
	dock_right(terrainSheet.getSurface(), 10, 10, 16, false, false),
	dock_up(terrainSheet.getSurface(), 9, 9, 16, false, false),
	dock_down(terrainSheet.getSurface(), 9, 11, 16, false, false),
	dock_leftup(terrainSheet.getSurface(), 8, 9, 16, false, false),
	dock_rightup(terrainSheet.getSurface(), 10, 9, 16, false, false),
	dock_leftdown(terrainSheet.getSurface(), 8, 11, 16, false, false),
	dock_rightdown(terrainSheet.getSurface(), 10, 11, 16, false, false),
	road(terrainSheet.getSurface(), 1, 4, 16, false, false),
	solidBack(terrainSheet.getSurface(), 1, 13, 16, true, false), 
	shoal(terrainSheet.getSurface(), 2, 13, 16, true, false),
	sand_leftcorner(terrainSheet.getSurface(), 3, 14, 16, false, false),
	sand_rightcorner(terrainSheet.getSurface(), 3, 13, 16, false, false),
	rfence_horiz(terrainSheet.getSurface(), 1, 15, 16, true, false),
	rfence_vertical(terrainSheet.getSurface(), 0, 14, 16, true, false),
	rfence_corner1(terrainSheet.getSurface(), 1, 14, 16, true, false),
	rfence_corner2(terrainSheet.getSurface(), 2, 14, 16, true, false),
	rfence_corner3(terrainSheet.getSurface(), 0, 15, 16, true, false),
	rfence_corner4(terrainSheet.getSurface(), 2, 15, 16, true, false),
	rroad(terrainSheet.getSurface(), 0, 13, 16, false, false),
	chest_closed(terrainSheet.getSurface(), 2, 2, 16, true, false),
   chest_open(terrainSheet.getSurface(), 1, 2, 16, true, false)
{

		width = WIDTH;
		height = HEIGHT;
		xOffset = 0;
		yOffset = 0;
		ctr = 0;

		for(int i = 0; i <= 100; i++){										// sets up the array of chests to be rendered on the display
			Chest* chest = new Chest(0,0);
			chestArray.push_back(*chest);
		}

}

// PUBLIC METHODS

void Display::render(SDL_Surface* screen) {
	ctr++;
	int xTileMin = xOffset >> 4;
	int yTileMin = yOffset >> 4;
	int xTileMax = (xOffset + width + 16) >> 4;								// corner pins, convert from pixel to tile precision
	int yTileMax = (yOffset + height + 16) >> 4;

	for(int y = yTileMin; y < yTileMax; y++) {
		for(int x = xTileMin; x < xTileMax; x++) {
			renderTile(((x - xTileMin) << 4), ((y - yTileMin) << 4), getSprite(x, y), screen);			// call renderTile for all tiles 
		}																								// within the bounds of the corner pins
	}
}

void Display::ctrIncrement() {								// increments the counter used for rendering dynamic tiles (like water)
	ctr++;
}

// GETTERS AND SETTERS

Sprite* Display::getSprite(int x, int y) {					// based on the provided coordinates, gets the char from the current Area's 
	if(x < 0 || y < 0 || x >= currentArea->getWidth() - 1 || y >= currentArea->getHeight() - 1) {	// map vector and returns the corresponding sprite
		return &grass;
	}

	switch(currentArea->getTile(x, y)) {
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
	case 'F':
		return &fence_front;
		break;
	case 'H':
		return &fence_left;
		break;
	case 'J':
		return &fence_right;
		break;
	case 'O':
		return &shoal;
		break;
	case 'R':
		return &road;
		break;
	case 'S':
		return &sand;
		break;
	case 'X':
		return &solidBack;
		break;
	case 's':
		return &sand_left;
		break;
	case 'a':
		return &sand_right;
		break;
	case 'b':
		return &sand_down;
		break;
	case 'c':
		return &sand_leftcorner;
		break;
	case 'f':
		return &sand_rightcorner;
		break;
	case 'e':
		return &estuary;
		break;
	case 'd':
		return &estuary_down;
		break;
	case '0':
		return &dock;
		break;
	case '1':
		return &dock_left;
		break;
	case '2':
		return &dock_right;
		break;
	case '3':
		return &dock_up;
		break;
	case '4':
		return &dock_down;
		break;
	case '5':
		return &dock_leftup;
		break;
	case '6':
		return &dock_rightup;
		break;
	case '7':
		return &dock_leftdown;
		break;
	case '8':
		return &dock_rightdown;
		break;
	case 'W':
		if(ctr % 280 < 140) {
			return &water1;
		} else {
			return &water2;
		}
		break;
	case 'r':
			return &rfence_horiz;
		break;
	case '9':
		return &rfence_vertical;
		break;
	case 'g':
		return &rfence_corner1;
		break;
	case 'h':
		return &rfence_corner2;
		break;
	case 'i':
		return &rfence_corner3;
		break;
	case 'j':
		return &rfence_corner4;
		break;
	case 'k':
		return &rroad;
		break;
	case 'l':
		return &flower2;
		break;
	case 'm':
		return &flower3;
		break;
	case 'n':
		return &flower4;
		break;
	case 'C':
		if(isOpen(y)){
			return &chest_open;
		} else{
			return &chest_closed;
		}
		break;
	}
}

Sprite* Display::getWaterHandle(int which) {	// returns a handle to the water tile, used for checking the player/AIs current tile
	if(which == 1) {							// two possible return values since the tile is dynamic
		return &water1;
	} else {
		return &water2;
	}
}

Sprite* Display::getShoalHandle() {				// returns a handle to the shoal tile, used for checking the player/AI collisions
	return &shoal;
}

Sprite* Display::getIceHandle() {				// returns a handle to the ice tile, used for player sliding
	return &ice;
}

Sprite* Display::getChestHandle(int which){		// returns a handle to the shoal tile, used for opening chests  
	if(which){
		return &chest_closed;
	} else {
		return &chest_open;
	}
}

Area* Display::getCurrentArea() {				// returns the current area the display is rendering
	return currentArea;
}

int Display::getXOffset() {						// return x or y offsets based on the display's current offset relative to the current area
	return xOffset;
}

int Display::getYOffset() {
	return yOffset;
}

int Display::getWidth() {						// return the height or width of the display window (rendered image)
	return width;
}

int Display::getHeight() {
	return height;
}

int Display::getchestNum() {					// number of chests in the display
	return chestNum;
}

int Display::isOpen(int y){						// used to determine which chest image to render 
	if(chestArray[y].isOpen()){
		return 1;
	} else{
		return 0;
	}
}

void Display::setOffsets(int x, int y) {
	xOffset = x;
	yOffset = y;
}

void Display::setArea(Area* newArea) {			// used for changing the current area (not implemented)
	currentArea = newArea;
}

void Display::addChest(Chest* chest) {			// used for pushing new chests onto the vector
	chestNum++;
	int ypos = chest->gety();
	chestArray[ypos]= *chest;
}

void Display::openChest(int y){
	chestArray[y].openChest();
}

// PRIVATE METHODS

void Display::renderTile(int x, int y, Sprite* sprite, SDL_Surface* screen) {		// based on the information provided by render, calls 
	int xRender = x - xOffset % 16;													// sprite.render to put a tile on a certain screen location
	int yRender = y - yOffset % 16;

	if(xOffset < 0) {
		xRender = x + (abs(xOffset) % 16);
	}
	if(yOffset < 0) {
		yRender = y + (abs(yOffset) % 16);
	}

	(*sprite).render(xRender, yRender, screen);
}
