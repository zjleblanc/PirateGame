// Handles logic and rendering methods shared by all mobile characters

#include "Display.h"
#include "Sprite.h"
#include "Entity.h"
#include <vector>
using namespace std;

#ifndef MOBILE_H
#define MOBILE_H

class Mobile : public Entity {
public:

	static vector<Mobile*> MobilesList;

	Mobile(string, int);

	void render(int, int, SDL_Surface*);
	virtual void update(Display*) = 0;

	Sprite* getNextTile(Display*);
	Sprite* getCurrentTile(Display*);
	bool isCollision(Display*);
	bool isSliding(Display*);
	int getDirection();
	int getSize();

protected:

	void goToNext();
	bool continueMotion();

	bool currentlySliding;
	int direction;
	int size;
	Sprite left;
	Sprite right;
	Sprite up;
	Sprite down;
	Sprite move_left;
	Sprite move_right;
	Sprite move_down1;
	Sprite move_down2;
	Sprite move_up1;
	Sprite move_up2;
};

#endif
