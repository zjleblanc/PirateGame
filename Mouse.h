#include "SDL.h"

#ifndef MOUSE_H
#define MOUSE_H

class Mouse {
public:
	Mouse();
	void update();
	int getX();
	int getY();
	int buttonPressed();
	int buttonReleased(int);
private:
	int x, y;
	SDL_Event mouseEvent;
};

#endif
