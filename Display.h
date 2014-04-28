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
	int getWidth();
	int getHeight();
	void setOffsets(int, int);
	void render(SDL_Surface*);
	char* getCurrentTile();
	Sprite* getSprite(int x, int y);
	void getOffsets();
	void ctrIncrement();
	Sprite* getWaterHandle(int);
	Sprite* getShoalHandle();
	int getXOffset();
	int getYOffset();
	void setArea(Area*);
	Area* getCurrentArea();
	Sprite* getChestHandle(int);
	int isOpen(int);
	void addChest(Chest* chest);
	int getchestNum();
	void openChest(int);

private:
	void renderTile(int, int, Sprite*, SDL_Surface*);
	int width, height;
	int xOffset, yOffset;
	int ctr;
	SpriteSheet terrainSheet;
	Sprite ice, grass, bush, flower, flower2, flower3, flower4, sand;
	Sprite water1, water2, fence_front, fence_left, fence_right;
	Sprite sand_left, sand_right, sand_down, sand_up, estuary, estuary_down;
	Sprite dock, dock_right, dock_left, dock_up, dock_down;
	Sprite dock_leftup, dock_rightup, dock_leftdown, dock_rightdown;
	Sprite road, shoal, sand_leftcorner, sand_rightcorner, rroad;
	Sprite rfence_horiz, rfence_vertical, rfence_corner1, rfence_corner2, rfence_corner3, rfence_corner4;
	Sprite solidBack;
	Area* currentArea;
	Sprite chest_open, chest_closed;
	int chestNum;
	vector<Chest> chestArray;
};

#endif