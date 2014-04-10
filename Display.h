
#include "Chest.h"
#include "SpriteSheet.h"
#include "Sprite.h"
#include "Area.h"
#include "SDL.h"
#include "SDL_image.h"
#include <vector>
#include <string>
using namespace std;

#ifndef DISPLAY_H
#define DISPLAY_H

class Chest;

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
	Sprite* getChestHandle(int);
	void openChest(int, int);
	int isClosed(int, int);
	void addChest(Chest* chest);
	int getchestNum();


private:
	void renderTile(int, int, Sprite*, SDL_Surface*);
	int width, height;
	int xOffset, yOffset;
	int ctr;
	int chestNum;
	vector<Chest> chestArray;
	SpriteSheet terrainSheet;
	Sprite ice, grass, bush, flower, sand, sand_water_down;
	Sprite water1, water2, fence_front, fence_left, fence_right;
	Sprite chest_open, chest_closed;
	Area mainArea;
};

#endif