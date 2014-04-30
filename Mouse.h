#include "SDL.h"
#include "Player.h"

#ifndef MOUSE_H
#define MOUSE_H

class Mouse {
public:
	Mouse();
	void update(); // update x,y in terms of pixels
	int getX(); // return x in pixels
	int getY(); // return y in pixels
	int getXtile(Player*); // return x in tiles
	int getYtile(Player*); // return y in tiles
	int buttonPressed(); // returns a 1 if left pressed, 3 if right pressed, 0 if neither pressed
	int buttonReleased(int); // returns if a specific button is released or not
private:
	int x, y;
	SDL_Event mouseEvent;
};

#endif
