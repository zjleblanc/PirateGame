// Handles all objects to be placed on the screen

#include "SpriteSheet.h"
#include "Sprite.h"
#include "Area.h"
#include "Chest.h"
#include "SDL.h"
#include "SDL_image.h"
#include <string>
using namespace std;

#ifndef DISPLAY_H
#define DISPLAY_H

class Display {
public:

	Display(int, int);

	void render(SDL_Surface*);
	
	void ctrIncrement();

	Sprite* getSprite(int x, int y);
	Sprite* getWaterHandle(int);
	Sprite* getShoalHandle();
	Sprite* getIceHandle();
	Sprite* getChestHandle(int);

	Area* getCurrentArea();

	int getXOffset();
	int getYOffset();
	int getWidth();
	int getHeight();
	int getchestNum();
	int isOpen(int);
	
	void setArea(Area*);
	void addChest(Chest* chest);
	void openChest(int);
	void setOffsets(int, int);

private:

	void renderTile(int, int, Sprite*, SDL_Surface*);

	SpriteSheet terrainSheet;
	Sprite ice, grass, bush, flower, flower2, flower3, flower4, sand;
	Sprite water1, water2, fence_front, fence_left, fence_right;
	Sprite sand_left, sand_right, sand_down, estuary, estuary_down;
	Sprite dock, dock_right, dock_left, dock_up, dock_down;
	Sprite dock_leftup, dock_rightup, dock_leftdown, dock_rightdown;
	Sprite road, shoal, sand_leftcorner, sand_rightcorner, rroad;
	Sprite rfence_horiz, rfence_vertical, rfence_corner1, rfence_corner2, rfence_corner3, rfence_corner4;
	Sprite solidBack;
	Sprite chest_open, chest_closed;

	Area* currentArea;

	vector<Chest> chestArray;

	int chestNum;
	int width, height;
	int xOffset, yOffset;
	int ctr;

};

#endif
