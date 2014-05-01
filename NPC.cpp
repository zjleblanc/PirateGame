#include "NPC.h"
#include <cstdlib>
#include <ctime>

// OBJECT LIST

vector<NPC*> NPC::NPC_list;

// CONSTRUCTORS

NPC::NPC(string sheetName, int maxRange, int xi, int yi) 
	:Mobile(sheetName, 1)
{
	srand(time(NULL));
	range = maxRange * 16;
	xInit = xi * 16;					// convert to pixel precision
	yInit = yi * 16;
	x = xInit;
	y = yInit;

	xMax = xInit + range;				// set range corner pins
	xMin = xInit - range;
	yMax = yInit + range;
	yMin = yInit - range;

	NPC_list.push_back(this);
}

// PUBLIC METHODS

void NPC::update(Display* display) {
	if(isSliding(display)) {

	} 
	else if(continueMotion()) {				// movement mechanics, rendering is handled by Mobile

	}
	else if(toMove()) {
		move(display);
	}
}

// PRIVATE METHODS

bool NPC::toMove() {
	if(rand() % 20 == 0) {		
		return true;
	}
	return false;
}

void NPC::move(Display* display) {
	direction = rand() % 4;
	if((direction == 0) && (!isCollision(display)) && (y > yMin)) {
		y--;
	} 
	else if((direction == 2) && (!isCollision(display)) && (y < yMax)) {		// move based on selected direction
		y++;
	}
	else if((direction == 3) && (!isCollision(display)) && (x > xMin)) {
		x--;
	}
	else if((direction == 1) && (!isCollision(display)) && (x < xMax)) {
		x++;
	}
}



