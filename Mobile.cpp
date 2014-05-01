#include "Mobile.h"

// OBJECT LIST

vector<Mobile*> Mobile::MobilesList;

// CONSTRUCTOR

Mobile::Mobile(string sheetPath, int s) 
	:Entity(sheetPath),
	size(s),
	left(sheet.getSurface(), 0, 1, 16 * size, true, false),
	right(sheet.getSurface(), 0, 0, 16 * size, true, false),
	up(sheet.getSurface(), 0, 2, 16 * size, true, false),
	down(sheet.getSurface(), 1, 0, 16 * size, true, false),

	move_left(sheet.getSurface(), 1, 1, 16 * size, true, false),
	move_right(sheet.getSurface(), 2, 1, 16 * size, true, false),			// instantiate player sprites
	move_up1(sheet.getSurface(), 1, 2, 16 * size, true, false),
	move_up2(sheet.getSurface(), 2, 2, 16 * size, true, false),
	move_down1(sheet.getSurface(), 2, 0, 16 * size, true, false),
	move_down2(sheet.getSurface(), 3, 0, 16 * size, true, false)
{
	currentlySliding = false;
	direction = 2;
}

// PUBLIC METHODS

void Mobile::render(int xp, int yp, SDL_Surface* screen) {
		
	if(direction == 0) {
		if(((y % 32 > 4) && (y % 32 < 12)) || currentlySliding) {
			move_up1.render(xp, yp, screen);
		} 
		else if((y % 32 > 20) && (y % 32 < 28)) {
			move_up2.render(xp, yp, screen);
		} 
		else {
			up.render(xp, yp, screen);
		}
	} 
	
	else if(direction == 2) {
		if(((y % 32 > 4) && (y % 32 < 12)) || currentlySliding) {				// render movement sprites based on direction, time, sliding
			move_down1.render(xp, yp, screen);
		} 
		else if((y % 32 > 20) && (y % 32 < 28)) {
			move_down2.render(xp, yp, screen);
		} 
		else {
			down.render(xp, yp, screen);
		}
	}

	else if(direction == 3) {
		if(((x % 16 > 4) && (x % 16 < 12)) || currentlySliding) {
			move_left.render(xp, yp, screen);
		} 
		else {
			left.render(xp,yp,screen);
		}
	}

	else if(direction == 1) {
		if(((x % 16 > 4) && (x % 16 < 12)) || currentlySliding) {
			move_right.render(xp, yp, screen);
		} 
		else {
			right.render(xp,yp,screen);
		}
	}

}

Sprite* Mobile::getNextTile(Display* display) {					// gets next tile in the path
	Sprite* nextTile;
	int xColl = x + 8;								
	int yColl = y + 8;

	switch(direction) {
	case 0:
		nextTile = display->getSprite((xColl >> 4), (yColl >> 4) - 1);		//convert to tile precision
		break;
	case 2:
		nextTile = display->getSprite((xColl >> 4), (yColl >> 4) + 1);
		break;
	case 3:
		nextTile = display->getSprite((xColl >> 4) - 1, (yColl >> 4));
		break;
	case 1:
		nextTile = display->getSprite((xColl >> 4) + 1, (yColl >> 4));
		break;
	}

	return nextTile;
}

Sprite* Mobile::getCurrentTile(Display* display) {
	int xColl = x + 8;
	int yColl = y + 8;
	Sprite* currentTile = display->getSprite(xColl >> 4, yColl >> 4);			// convert to tile precision
	return currentTile;
}

bool Mobile::isCollision(Display* display) {				// only looks for map collisions

	Sprite* nextTile = getNextTile(display);
	return nextTile->isSolid();

}

bool Mobile::isSliding(Display* display) {					// determines whether or not to slide the character based on current location
	Sprite* currentTile;
	int xSlide = x + 8;
	int ySlide = y + 8;
	currentTile = display->getSprite(xSlide >> 4, ySlide >> 4);

	if(currentTile->isSliding() && !isCollision(display)) {

		currentlySliding = true;
		
		if(direction == 0) {
			y-=2;
		}
		
		if(direction == 2) {
			y+=2;
		}
		
		if(direction == 3) {
			x-=2;
		}

		if(direction == 1) {
			x+=2;
		}
		return true;
	} else {
		currentlySliding = false;
	}

	return false;
}

int Mobile::getDirection() {
	return direction;
}

int Mobile::getSize() {
	return size;
}

// PROTECTED METHODS

void Mobile::goToNext() {				// move 1 space based on current direction
	switch(direction) {
	case 0:
		y--;
		break;
	case 2:
		y++;
		break;
	case 3:
		x--;
		break;
	case 1:
		x++;
		break;
	}
}

bool Mobile::continueMotion() {
	if((y % 16 != 0) && (direction == 0)) {
		y--;
		return true;
	} 
	else if ((y % 16 != 0) && (direction == 2)) {
		y++;
		return true;
	} 
	else if ((x % 16 != 0) && (direction == 3)) {
		x--;
		return true;
	} 
	else if ((x % 16 != 0) && (direction == 1)) {
		x++;
		return true;
	}

	return false;
}
