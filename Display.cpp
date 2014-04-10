#include "Display.h"
#include <iostream>
#include <cmath>
//#include <Windows.h>
#include <vector>
#include <sstream>
#include <string>
#include "Chest.h"

using namespace std;

Display::Display(int WIDTH, int HEIGHT) 
	:terrainSheet( "Terrain.png" ),

	ice(terrainSheet.getSurface(), 0, 0, 16, false, true),
	grass(terrainSheet.getSurface(), 0, 1, 16, false, false),
	flower(terrainSheet.getSurface(), 1, 1, 16, false, false),
	bush(terrainSheet.getSurface(), 2, 1, 16, true, false), 
	sand(terrainSheet.getSurface(), 3, 1, 16, false, false),
	sand_water_down(terrainSheet.getSurface(), 5, 0, 16, false, false),
	water1(terrainSheet.getSurface(), 5, 1, 16, true, false),
	water2(terrainSheet.getSurface(), 4,0, 16, true, false),
	fence_front(terrainSheet.getSurface(), 0, 2, 16, true, false),
	fence_left(terrainSheet.getSurface(), 0, 3, 16, true, false),
	fence_right(terrainSheet.getSurface(), 0, 4, 16, true, false),
	chest_closed(terrainSheet.getSurface(), 2, 2, 16, true, false),
	chest_open(terrainSheet.getSurface(), 1, 2, 16, true, false),


	mainArea("MainMap.txt") {

		width = WIDTH;
		height = HEIGHT;
		xOffset = 0;
		yOffset = 0;
		ctr = 0;
		chestNum = 0;
		

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

	if(xOffset < 0) {
		xRender = x + (abs(xOffset) % 16);
	}
	if(yOffset < 0) {
		yRender = y + (abs(yOffset) % 16);
	}

	(*sprite).render(xRender, yRender, screen);
}

void Display::render(SDL_Surface* screen) {
	ctr++;
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
	if(x < 0 || y < 0 || x >= mainArea.getWidth() - 1 || y >= mainArea.getHeight() - 1) {
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
	case 'S':
		return &sand;
		break;
	case 's':
		return &sand_water_down;
		break;
	case 'W':
		if(ctr % 280 < 140) {
			return &water1;
		} else {
			return &water2;
		}
		break;
	case 'C':
		if(!isClosed(x, y)){
			return &chest_open;
		} else{
			return &chest_closed;
		}
		break;
	}
}

char* Display::getCurrentTile() {
	int xTile = (xOffset + 8 + width / 2) >> 4;
	int yTile = (yOffset + 8 + height / 2) >> 4;

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
	case 'S':
		return "sand";
		break;
	case 'W':
		return "water";
		break;
	default:
		return "tile not found";
	}
}

/* void Display::getOffsets() {
	stringstream ss;
	ss << "X: " << xOffset << " Y: " << yOffset;
	OutputDebugString(ss.str().c_str());
} */

void Display::ctrIncrement() {
	ctr++;
}

Sprite* Display::getWaterHandle(int which) {
	if(which == 1) {
		return &water1;
	} else {
		return &water2;
	}
}

Sprite* Display::getChestHandle(int which){
	if(which){
		return &chest_closed;
	} else {
		return &chest_open;
	}
}

void Display::addChest(Chest* chest){
	chestNum++;
	chestArray.push_back(*chest);
}

int Display::getchestNum(){
	return chestNum;
}

void Display::openChest(int x, int y){
	for (int i = 0; i < chestNum; i++){
		if (chestArray[i].getx() == x && chestArray[i].gety() == y){
			chestArray[i].openChest();
		}
	}
}

int Display::isClosed(int x, int y){
	for(int i = 0; i < chestNum; i++){
		if (chestArray[i].getx() == x && chestArray[i].gety() == y && chestArray[i].isopen()==0){
			return 1;
		}
	}
	return 0;
}
