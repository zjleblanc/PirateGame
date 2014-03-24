#include "Player.h"

Player::Player() 
	:playerSprites("Player3.png"),

	left(playerSprites.getSurface(), 0, 1, false, false),
	right(playerSprites.getSurface(), 0, 0, false, false),
	up(playerSprites.getSurface(), 0, 2, false, false),
	down(playerSprites.getSurface(), 1, 0, false, false),

	move_left(playerSprites.getSurface(), 1, 1, false, false),
	move_right(playerSprites.getSurface(), 2, 1, false, false),
	move_up1(playerSprites.getSurface(), 1, 2, false, false),
	move_up2(playerSprites.getSurface(), 2, 2, false, false),
	move_down1(playerSprites.getSurface(), 2, 0, false, false),
	move_down2(playerSprites.getSurface(), 3, 0, false, false)
{
	x = 0; 
	y = 0;
	direction = 1; 
	currentlySliding = false;
	keyboard = new Keyboard();
}

Player::~Player() {
	delete keyboard;
}

void Player::render(int xp, int yp, SDL_Surface* screen) {
	
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
	
	else if(direction == 1) {
		if(((y % 32 > 4) && (y % 32 < 12)) || currentlySliding) {
			move_down1.render(xp, yp, screen);
		} 
		else if((y % 32 > 20) && (y % 32 < 28)) {
			move_down2.render(xp, yp, screen);
		} 
		else {
			down.render(xp, yp, screen);
		}
	}

	else if(direction == 2) {
		if(((x % 16 > 4) && (x % 16 < 12)) || currentlySliding) {
			move_left.render(xp, yp, screen);
		} 
		else {
			left.render(xp,yp,screen);
		}
	}

	else if(direction == 3) {
		if(((x % 16 > 4) && (x % 16 < 12)) || currentlySliding) {
			move_right.render(xp, yp, screen);
		} 
		else {
			right.render(xp,yp,screen);
		}
	}

}

void Player::update(Display* display) { 
	keyboard->update();
	if(isSliding(display)) {

	}  
	else if (!continueMotion()) {
		processInput(display);
	}
}

bool Player::continueMotion() {
	if((y % Sprite::getSize() != 0) && (direction == 0)) {
		y--;
		return true;
	} 
	else if ((y % Sprite::getSize() != 0) && (direction == 1)) {
		y++;
		return true;
	} 
	else if ((x % Sprite::getSize() != 0) && (direction == 2)) {
		x--;
		return true;
	} 
	else if ((x % Sprite::getSize() != 0) && (direction == 3)) {
		x++;
		return true;
	}

	return false;
}

void Player::processInput(Display* display) {
	if(keyboard->getState(SDLK_UP)) { 
		direction = 0;
		if(!isCollision(display)) {
			y--;
		}
	}

	else if(keyboard->getState(SDLK_DOWN)) {
		direction = 1;
		if(!isCollision(display)) {
			y++;
		}
	}
	
	else if(keyboard->getState(SDLK_LEFT)) {
		direction = 2;
		if(!isCollision(display)) {
			x--;
		}
	}
	
	else if(keyboard->getState(SDLK_RIGHT)) {
		direction = 3;
		if(!isCollision(display)) {
			x++;
		}
	}
}

void Player::setLocation(int newX, int newY) {
	x = newX;
	y = newY;
}

bool Player::isCollision(Display* display) {

	Sprite* nextTile;
	int xColl = x + (Sprite::getSize() / 2) + display->getWidth() / 2;
	int yColl = y + (Sprite::getSize() / 2) + display->getHeight() / 2;

	switch(direction) {
	case 0:
		nextTile = display->getSprite((xColl >> 4), (yColl >> 4) - 1);
		break;
	case 1:
		nextTile = display->getSprite((xColl >> 4), (yColl >> 4) + 1);
		break;
	case 2:
		nextTile = display->getSprite((xColl >> 4) - 1, (yColl >> 4));
		break;
	case 3:
		nextTile = display->getSprite((xColl >> 4) + 1, (yColl >> 4));
		break;
	}

	return nextTile->isSolid();

}

bool Player::isSliding(Display* display) {
	Sprite* currentTile;
	int xSlide = x + (Sprite::getSize() / 2) + display->getWidth() / 2;
	int ySlide = y + (Sprite::getSize() / 2) + display->getHeight() / 2;
	currentTile = display->getSprite(xSlide >> 4, ySlide >> 4);

	if(currentTile->isSliding() && !isCollision(display)) {

		currentlySliding = true;
		
		if(direction == 0) {
			y-=2;
		}
		
		if(direction == 1) {
			y+=2;
		}
		
		if(direction == 2) {
			x-=2;
		}

		if(direction == 3) {
			x+=2;
		}
		return true;
	} else {
		currentlySliding = false;
	}

	return false;
}

int Player::getX() {
	return x;
}

int Player::getY() {
	return y;
}
