#include "SDL.h"
#include "Player.h"

#ifndef MOUSE_H
#define MOUSE_H

class Mouse {
public:
	Mouse();
	void update();
	int getX();
	int getY();
	int getXtile(Player*);
	int getYtile(Player*);
	int buttonPressed();
	int buttonReleased(int);
private:
	int x, y;
	SDL_Event mouseEvent;
};

#endif
