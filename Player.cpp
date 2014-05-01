#include "Player.h"
#include <sstream>

// CONSTRUCTOR 

Player::Player(string sheetName) 
	:Mobile(sheetName, 1),
	playerHUD("HUD.png", 250, 200)			// player's HUD
{
	keyboard = new Keyboard();

	left_projectile = new Projectile("Cannonball.png");						// gives player two projectiles with a player tag
	left_projectile->setTag('p');
	right_projectile = new Projectile("Cannonball.png");
	right_projectile->setTag('p');


	shipState = false;
	playerVessel = new Ship("Ships.png");									// prepares the player's ship
	numProjectiles = 200;
	playerHUD.setCurrentShot(numProjectiles);
	maxHealth = 250;
	currentHealth = 250;

	sinks = 0;
	doubloons = 0;
}

//DECONSTRUCTOR

Player::~Player() {
	delete keyboard;
	delete right_projectile;
	delete left_projectile;
}

// PUBLIC METHODS

void Player::update(Display* display) { 

	keyboard->update();									// update keystates

	playerVessel->update(display);						// updates the player's ship

	left_projectile->updateParticles(display);			// updates the projectiles' particles
	right_projectile->updateParticles(display);

	playerHUD.setCurrentHealth((double)currentHealth);	// update the HUD
	playerHUD.setSinks(sinks);
	playerHUD.setDoubloons(doubloons);

	if(left_projectile->isActive()) {					// update the projectiles (if active)
		left_projectile->update(display);
	}

	if(right_projectile->isActive()) {
		right_projectile->update(display);
	}

	if(isSliding(display)) {							// moves the player based on conditions

	}  
	else if (!continueMotion()) {
		processInput(display);
	}
}

void Player::renderAttrib(SDL_Surface* screen, Display* display) {			// renders all objects player is composed of
	openChest(display, screen);
	playerHUD.render(0, 0, screen);
	left_projectile->render((display->getWidth() / 2) - x, (display ->getHeight() / 2) - y, screen);
	right_projectile->render((display->getWidth() / 2) - x, (display ->getHeight() / 2) - y, screen);
}

void Player::renderLand(int xp, int yp, SDL_Surface* screen) {				// renders the player's sprites when on land
		
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

void Player::renderSea(int x, int y, SDL_Surface* screen) {				// calls the ship's render functions (when at sea)
	playerVessel->setDirection(direction);
	playerVessel->render(x,y,screen);
}

void Player::render(int x, int y, SDL_Surface* screen) {				// determines which render method to use, and executes it
	if(shipState) {
		renderSea(x,y,screen);
	} else {
		renderLand(x,y,screen);
	}
}

// GETTERS AND SETTERS

bool Player::isSailing() {
	return shipState;
}

void Player::addDoubloons(double addition) {
	doubloons += addition;
}

void Player::incrementSinks() {
	sinks++;
}

void Player::subHealth(int damage) {			// limits health to more than 0

	if(currentHealth - damage >= 0) {
		currentHealth -= damage;
	} else {
		currentHealth = 0;
	}

	playerHUD.setCurrentHealth(currentHealth);	// sets hud, healthbar to reflect new values
	playerVessel->subHealth(damage);
}

void Player::restoreHealth(int healing) {		// limits health gained to less than maxhealth
	
	if(currentHealth + healing < 200) {
		currentHealth += healing;
	} else {
		currentHealth = 200;
	}

	playerHUD.setCurrentHealth(currentHealth);	// sets hud, healthbar to reflect new values
	playerVessel->addHealth(healing);

}

int Player::getHealth() {
	return currentHealth;
}

void Player::openChest(Display* display, SDL_Surface* screen){

	if(keyboard->getState(SDLK_a) && (getNextTile(display) == display->getChestHandle(1))) {		// if closed and 'a' is pressed

		playerHUD.setDoubloons(doubloons + 50);
		currentHealth = 250;
		numProjectiles = 200;
		playerHUD.setCurrentShot(numProjectiles);				// chest restores health, gives doubloons
		playerHUD.setCurrentHealth(currentHealth);
		doubloons += 50;

		int xColl = x + 8;
		int yColl = y + 8;
		int cx, cy;

		switch(direction) {
		case 0:
			cx = (xColl >> 4);
			cy = (yColl >> 4) - 1;					// converts to tile precision
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

		display->openChest(cy);
	
	}
}

// PRIVATE METHODS

void Player::processInput(Display* display) {
	
	toBoat(display);							// determines whether or not to place the player in a ship

	bool onWater = ((getCurrentTile(display) == display->getWaterHandle(1)) || getCurrentTile(display) == display->getWaterHandle(2));
	bool waterAdjacent = ((getNextTile(display) == display->getWaterHandle(1)) || getNextTile(display) == display->getWaterHandle(2));
	bool shoalAdjacent = ((getNextTile(display))->isSolid()) && !waterAdjacent;

	if(keyboard->getState(SDLK_x) && !left_projectile->isActive() && !right_projectile->isActive() && shipState) {
		fireProjectile();
	} 

	if(keyboard->getState(SDLK_UP)) { 
		direction = 0;
		if(!isCollision(display) || (shipState && onWater && !shoalAdjacent)) {		// moves if on water and no collisions present
			y--;
		}
	}

	else if(keyboard->getState(SDLK_DOWN)) {
		direction = 2;
		if(!isCollision(display) || (shipState && onWater && !shoalAdjacent)) {
			y++;
		}
	}
	
	else if(keyboard->getState(SDLK_LEFT)) {
		direction = 3;
		if(!isCollision(display) || (shipState && onWater && !shoalAdjacent)) {
			x--;
		}
	}
	
	else if(keyboard->getState(SDLK_RIGHT)) {
		direction = 1;
		if(!isCollision(display) || (shipState && onWater && !shoalAdjacent)) {
			x++;
		}
	}
}

void Player::toBoat(Display* display) {
	if(!((getCurrentTile(display) == display->getWaterHandle(1)) || getCurrentTile(display) == display->getWaterHandle(2))) {	// disembark condition
		shipState = false;
	}
	if(keyboard->getState(SDLK_z) && !shipState) {
		if((getNextTile(display) == display->getWaterHandle(1)) || (getNextTile(display) == display->getWaterHandle(2))) {	// enter ship condition
			shipState = true;
			goToNext();
		}
	}
	else if((getCurrentTile(display) == display->getWaterHandle(1)) || (getCurrentTile(display) == display->getWaterHandle(2))) { // stay sailing
		shipState = true;
	}
}

void Player::fireProjectile() {

	left_projectile->setZ(3);				//set elevation and locaion, and fire according to player's direction
	right_projectile->setZ(3);

	left_projectile->setLocation(x,y);
	right_projectile->setLocation(x,y);

	left_projectile->setDirection((direction + 1) & 3);
	right_projectile->setDirection((direction - 1) & 3);

	if(numProjectiles > 0) {				// fire only if the player has projectiles
		left_projectile->fire();
		right_projectile->fire();
		numProjectiles -= 2;
		playerHUD.setCurrentShot(numProjectiles);
	}

}
	

