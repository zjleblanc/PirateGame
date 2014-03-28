#include "SDL.h"

#ifndef MOUSE_H
#define MOUSE_H

class Mouse {
public:
	Mouse();
	void update();
	int getX();
	int getY();
	bool isLeftPressed();
	bool isRightPressed();
private:
	Uint32 button;
	int x;
	int y;
};

#endif
