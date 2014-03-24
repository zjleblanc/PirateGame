#include "SpriteSheet.h"
#include "Display.h"
#include "Keyboard.h"
#include "Sprite.h"

#ifndef PLAYER_H
#define PLAYER_H

class Player {
public:
	Player();
	~Player();
	void render(int, int, SDL_Surface*);
	void update(Display*);
	void setLocation(int, int);
	bool isCollision(Display*);
	bool isSliding(Display*);
	int getX();
	int getY(); 
private:
	bool continueMotion();
	void processInput(Display* display);
	int x, y;
	int xAnimate;
	int yAnimate;
	int direction;
	Keyboard* keyboard;
	SpriteSheet playerSprites;
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
