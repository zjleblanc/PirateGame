#include "Player.h"
#include <sstream>

Player::Player(string sheetName) 
	:Mobile(sheetName)
{
	keyboard = new Keyboard();
	left_projectile = new Projectile("Cannonball.png");
	right_projectile = new Projectile("Cannonball.png");
	shipState = false;
	playerVessel = new Ship(CUTTER, "Ships.png"); 
}

Player::~Player() {
	delete keyboard;
	delete right_projectile;
	delete left_projectile;
}

void Player::update(Display* display) { 
	keyboard->update();
	if(left_projectile->isActive()) {
		left_projectile->update(display);
		right_projectile->update(display);
	}
	if(isSliding(display)) {

	}  
	else if (!continueMotion()) {
		processInput(display);
	}
}

void Player::renderAttrib(SDL_Surface* screen, Display* display) {
	opening(screen, display);
	if(left_projectile->isActive()) {
		left_projectile->render((display->getWidth() / 2) - x, (display ->getHeight() / 2) - y, screen);
		right_projectile->render((display->getWidth() / 2) - x, (display ->getHeight() / 2) - y, screen);
	}
}

void Player::renderLand(int xp, int yp, SDL_Surface* screen) {
		
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

void Player::renderSea(int x, int y, SDL_Surface* screen) {
	playerVessel->render(x,y,screen);
}

void Player::render(int x, int y, SDL_Surface* screen) {
	if(shipState) {
		renderSea(x,y,screen);
	} else {
		renderLand(x,y,screen);
	}
}

void Player::processInput(Display* display) {
	
	toBoat(display);

	if(keyboard->getState(SDLK_x) && !left_projectile->isActive() && shipState) {
		fireProjectile();
	} 

	if(keyboard->getState(SDLK_UP)) { 
		direction = 0;
		playerVessel->setDirection(0);
		if(!isCollision(display)) {
			y--;
		}
	}

	else if(keyboard->getState(SDLK_DOWN)) {
		direction = 2;
		playerVessel->setDirection(2);
		if(!isCollision(display)) {
			y++;
		}
	}
	
	else if(keyboard->getState(SDLK_LEFT)) {
		direction = 3;
		playerVessel->setDirection(3);
		if(!isCollision(display)) {
			x--;
		}
	}
	
	else if(keyboard->getState(SDLK_RIGHT)) {
		direction = 1;
		playerVessel->setDirection(1);
		if(!isCollision(display)) {
			x++;
		}
	}
}

void Player::toBoat(Display* display) {
	if(!((getCurrentTile(display) == display->getWaterHandle(1)) || getCurrentTile(display) == display->getWaterHandle(2))) {
		shipState = false;
	}
	if(keyboard->getState(SDLK_z)) {
		if((getNextTile(display) == display->getWaterHandle(1)) || (getNextTile(display) == display->getWaterHandle(2))) {
			shipState = true;
			goToNext();
		}
	}
}


void Player::fireProjectile() {
	left_projectile->setLocation(x,y);
	right_projectile->setLocation(x,y);
	left_projectile->setDirection((direction + 1) & 3);
	right_projectile->setDirection((direction - 1) & 3);
	left_projectile->fire();
	right_projectile->fire();
}

bool Player::isSailing() {
	return shipState;
}

void Player::opening(SDL_Surface* screen, Display* display){
	if(keyboard->getState(SDLK_a) && (getNextTile(display) == display->getChestHandle(1))) {
		int xColl = x + 8;
		int yColl = y + 8;
		int cx, cy;
			switch(direction) {
				case 0:
					cx = (xColl >> 4);
					cy = (yColl >> 4) - 1;
					break;
				case 2:
					cx = (xColl >> 4);
					cy = (yColl >> 4) + 1;
					break;
				case 3:
					cx = (xColl >> 4) - 1;
					cy = (yColl >> 4);
					break;
				case 1:
					cx = (xColl >> 4) + 1;
					cy = (yColl >> 4);
					break;
			}
			display->openChest(cx, cy);
		}
}

