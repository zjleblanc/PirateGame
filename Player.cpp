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
	x = 0, xAnimate = 0; 
	y = 0, yAnimate = 0;
	direction = 1; 
	keyboard = new Keyboard();
}

Player::~Player() {
	delete keyboard;
}

void Player::render(int xp, int yp, SDL_Surface* screen) {
	
	if(direction == 0) {
		if((yAnimate % 32 > 4) && (yAnimate % 32 < 12)) {
			move_up1.render(xp, yp, screen);
		} 
		else if((yAnimate % 32 > 20) && (yAnimate % 32 < 28)) {
			move_up2.render(xp, yp, screen);
		} 
		else {
			up.render(xp, yp, screen);
		}
	} 
	
	else if(direction == 1) {
		if((yAnimate % 32 > 4) && (yAnimate % 32 < 12)) {
			move_down1.render(xp, yp, screen);
		} 
		else if((yAnimate % 32 > 20) && (yAnimate % 32 < 28)) {
			move_down2.render(xp, yp, screen);
		} 
		else {
			down.render(xp, yp, screen);
		}
	}

	else if(direction == 2) {
		if((xAnimate % 16 > 4) && (xAnimate % 16 < 12)) {
			move_left.render(xp, yp, screen);
		} 
		else {
			left.render(xp,yp,screen);
		}
	}

	else if(direction == 3) {
		if((xAnimate % 16 > 4) && (xAnimate % 16 < 12)) {
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
		yAnimate--;
		return true;
	} 
	else if ((y % Sprite::getSize() != 0) && (direction == 1)) {
		y++;
		yAnimate++;
		return true;
	} 
	else if ((x % Sprite::getSize() != 0) && (direction == 2)) {
		x--;
		xAnimate--;
		return true;
	} 
	else if ((x % Sprite::getSize() != 0) && (direction == 3)) {
		x++;
		xAnimate++;
		return true;
	}

	return false;
}

void Player::processInput(Display* display) {
	if(keyboard->getState(SDLK_UP)) { 
		direction = 0;
		if(!isCollision(display)) {
			y--;
			yAnimate--;
		}
	}

	else if(keyboard->getState(SDLK_DOWN)) {
		direction = 1;
		if(!isCollision(display)) {
			y++;
			yAnimate++;
		}
	}
	
	else if(keyboard->getState(SDLK_LEFT)) {
		direction = 2;
		if(!isCollision(display)) {
			x--;
			xAnimate--;
		}
	}
	
	else if(keyboard->getState(SDLK_RIGHT)) {
		direction = 3;
		if(!isCollision(display)) {
			x++;
			xAnimate++;
		}
	}
}

void Player::setLocation(int newX, int newY) {
	x = newX;
	y = newY;
}

bool Player::isCollision(Display* display) {

	Sprite* nextTile;
	int xColl = x + display->getWidth() / 2;
	int yColl = y + display->getHeight() / 2;

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
	int xSlide = x + display->getWidth() / 2;
	int ySlide = y + display->getHeight() / 2;
	currentTile = display->getSprite(xSlide >> 4, ySlide >> 4);

	if(currentTile->isSliding() && !isCollision(display)) {
		
		if(direction == 0) {
			y-=2;
			yAnimate = 8;
		}
		
		if(direction == 1) {
			y++;
			yAnimate = 8;
			if(!isCollision(display)) {
				y++;
			} else {
				yAnimate = 0;
			}
		}
		
		if(direction == 2) {
			x--;
			if(!isCollision(display)) x--;
			xAnimate = 8;
		}

		if(direction == 3) {
			x++;
			xAnimate = 8;
			if(!isCollision(display)) {
				x++;
			} else {
				xAnimate = 0;
			}
		}
		return true;
	}

	return false;
}

int Player::getX() {
	return x;
}

int Player::getY() {
	return y;
}
