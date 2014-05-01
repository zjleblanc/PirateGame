#include "Pirate.h"
#include <cmath>
#include <ctime>
#include <cstdlib>

// CONSTRUCTOR

Pirate::Pirate(string path, int xi, int yi, int range, int diff, int size) 
	:AI_Unit(path, xi, yi, range, diff, size),
	underWater(sheet.getSurface(), 0, 3, 32, false, false)						// creates additional sunken sprite
	{

		srand(time(NULL));

		chillin = true;
		chasing = false;
		evading = false;										// default state: chillin
		attacking = false;
		positioning = false;
		fleeing = false;

		left_projectile = new Projectile("Cannonball.png");			// set projectiles to AI type
		left_projectile->setTag('a');
		right_projectile = new Projectile("Cannonball.png");
		right_projectile->setTag('a');

		enemyHealth = new HealthBar("Health.png", 150);
		//enemyHealth->subHealth(150);

		moving = false;
		sunk = false;
		contactDamages = false;										// can't hurt the player upon contact
}

// DECONSTRUCTOR

Pirate::~Pirate() {
	delete left_projectile;
	delete right_projectile;
}

// PUBLIC METHODS

void Pirate::renderAttrib(SDL_Surface* screen, Display* display, Player* player) {

	int WIDTH = display->getWidth() / 2;
	int HEIGHT = display->getHeight() / 2;

	int xP = WIDTH + (x - player->getX());
	int yP = HEIGHT + (y - player->getY());

	left_projectile->render(xP - x, yP - y, screen);				// render the enemy's projectiles
	right_projectile->render(xP - x, yP - y, screen);

	if(sunk) {
		underWater.render(xP, yP, screen);							// if sunk, render the sunken sprite, otherwise render the health bar
	} else {
		enemyHealth->render(xP, yP - 16, screen);
	}

}

void Pirate::update(Display* display) {

	updateCount++;

	moving = continueMotion();							// makes sure motion ends on a tile

	left_projectile->updateParticles(display);
	right_projectile->updateParticles(display);

	if(left_projectile->isActive()) {
		left_projectile->update(display);				// update the trajectory of active projectiles
	}

	if(right_projectile->isActive()) {
		right_projectile->update(display);
	}

	if(enemyHealth->getHealth() <= 0) {					// sink at 0 hp
		sunk = true;
	}

}

void Pirate::runAI(Player* player, Display* display) {

	if((updateCount % difficulty == 0) && !moving && !sunk) {

		if(chillin) {
			chill(player, display);
		}
		else if(chasing) {
			chase(player, display);						// execute state based on output of private state machine methods
		}
		else if(evading) {
			evade(player, display);
		}
		else if(positioning) {
			position(player, display);
		}
		else if(attacking) {
			attack(player);
		}
		else if(fleeing) {
			flee(player, display);
		}

	}

}

// PRIVATE METHODS

void Pirate::chill(Player* player, Display* display) {

	// PERFORM LOGIC

	bool toMove = false;

	if(rand() % 10 == 0) {
		toMove = true;
		direction = rand() % 4;			// move randomly
	}

	bool waterNext = (getNextTile(display) == display->getWaterHandle(1)) || (getNextTile(display) == display->getWaterHandle(2));
	
	if(waterNext) {

		if(toMove && direction == 0) {			// only move if the next tile is water
			y--;
		}
	
		else if(toMove && direction == 1) {
			x++;
		}
	
		else if(toMove && direction == 2) {
			y++;
		}
	
		else if(toMove && direction == 3) {
			x--;
		}

	}
	// GET NEXT STATE

	if(getDistance(player) > 160) {
		chillin = true;
	} 
	else if(atRangeLimit() && getDistance(player) <= 160) {
		chillin = false;
		fleeing = true;
	}
	else if(!atRangeLimit() && getDistance(player) <= 160) {			// chase player if they get out of range
		chillin = false;
		chasing = true;
	}

}

void Pirate::chase(Player* player, Display* display) {

	int xDistance = x - player->getX(); 
	int yDistance = y - player->getY();

	bool waterNext = (getNextTile(display) == display->getWaterHandle(1)) || (getNextTile(display) == display->getWaterHandle(2));

	// PERFORM LOGIC

	if(waterNext) {				// only move if water is the next tile
			
		if((abs(xDistance) > abs(yDistance))) {		// finds the fastest path to the player
			if(xDistance > 0) {
				x--;
				direction = 3;
			} 
			else {
				x++;
				direction = 1;
			}
		} 
		
		else {
			if(yDistance > 0) {
				y--;
				direction = 0;
			} 
			else {
				y++;
				direction = 2;
			}
	
		}

	} else {
		chasing = false;
		chillin = true;
	}

	// GET NEXT STATE

	if(atRangeLimit() && getDistance(player) > 160) {
		chasing = false;
		chillin = true;
	}

	else if(!atRangeLimit() && getDistance(player) > 160) {
		chasing = true;
	}

	else if(atRangeLimit() && getDistance(player) <= 160) {
		chasing = false;
		fleeing = true;
	}

	else if (!atRangeLimit() && getDistance(player) <= 160) {
		chasing = false;
		positioning = true;
	}

}

void Pirate::evade(Player* player, Display* display) {

	int px = player->getX();
	int py = player->getY();
	int pdir = player->getDirection();
	int moveChoice = rand() % 2;

	bool waterNext = (getNextTile(display) == display->getWaterHandle(1)) || (getNextTile(display) == display->getWaterHandle(2));

	// PERFORM LOGIC

	if(waterNext) {
	
		if((pdir == 0) || (pdir == 2)) {
	
			if(moveChoice == 0) {
				y--;
				direction = 0;
			} else {
				y++;
				direction = 2;
			}
	
		} else {
	
			if(moveChoice == 0) {
				x--;
				direction = 3;
			} else {
				x++;
				direction = 1;
			}
	
		}
	
	} else {
		evading = false;
		chillin = true;
	}

	// GET NEXT STATE

	if(getDistance(player) > 160) {
		evading = false;
		chasing = true;
	}

	else if((px == x) && ((direction == 1 || direction == 3) && (pdir == 0 || pdir == 2))) {
		evading = true;
	}

	else if((py == y) && ((direction == 0 || direction == 2) && (pdir == 1 || pdir == 3))) {
		evading = true;
	}

	else {
		evading = false;
		positioning = true;
	}

}

void Pirate::attack(Player* player) {

	int px = player->getX();
	int py = player->getY();
	int pdir = player->getDirection();

	// PERFORM LOGIC


	if(!left_projectile->isActive() && !right_projectile->isActive()) {
	
		left_projectile->setZ(3);
		right_projectile->setZ(3);
		
		left_projectile->setLocation(x,y);
		right_projectile->setLocation(x,y);
		
		left_projectile->setDirection((direction + 1) & 3);
		right_projectile->setDirection((direction - 1) & 3);

		right_projectile->fire();
		left_projectile->fire();

	}

	// GET NEXT STATE

	if((px == x) && (direction == 1 || direction == 3) && getDistance(player) < 160) {
		attacking = true;
	}

	else if((py == y) && (direction == 0 || direction == 2) && (getDistance(player) < 160)) {
		attacking = true;
	}

	else if(getDistance(player) >= 160) {
		attacking = false;
		chasing = true;
	}

	else {
		attacking = false;
		positioning = true;
	}

}

void Pirate::position(Player* player, Display* display) {

	int px = player->getX();
	int py = player->getY();
	int pdir = player->getDirection();

	// PERFORM LOGIC

	bool toMove = false;

	if(rand() % 10 == 0) {
		toMove = true;
		direction = rand() % 4;
	}

	bool waterNext = (getNextTile(display) == display->getWaterHandle(1)) || (getNextTile(display) == display->getWaterHandle(2));

	if(waterNext) {
	
		if(toMove && direction == 0) {
			y--;
		}
	
		else if(toMove && direction == 1) {
			x++;
		}
	
		else if(toMove && direction == 2) {
			y++;
		}
	
		else if(toMove && direction == 3) {
			x--;
		}

	}

	// GET NEXT STATE

	if(getDistance(player) > 160) {
		positioning = false;
		chasing = true;
	}

	else if((px == x) && ((direction == 0 || direction == 2) && (pdir == 1 || pdir == 3))) {
		positioning = false;
		evading = true;
	}

	else if((py == y) && ((direction == 1 || direction == 3) && (pdir == 0 || pdir == 2))) {
		positioning = false;
		evading = true;
	}

	else if((px == x) && (direction == 1 || direction == 3)) {
		positioning = false;
		attacking = true;
	}

	else if((py == y) && (direction == 0 || direction == 2)) {
		positioning = false;
		attacking = true;
	}

	else {
		positioning = true;
	}

}

void Pirate::flee(Player* player, Display* display) {

	int xDistance = x - player->getX(); 
	int yDistance = y - player->getY();

	bool waterNext = (getNextTile(display) == display->getWaterHandle(1)) || (getNextTile(display) == display->getWaterHandle(2));
	 
	// PERFORM LOGIC

	if(waterNext) {

		if((abs(xDistance) > abs(yDistance))) {
			if(xDistance > 0) {
				x++;
				direction = 1;
			} 
			else {
				x--;
				direction = 3;
			}
		} 
		
		else {
			if(yDistance > 0) {
				y++;
				direction = 2;
			} 
			else {
				y--;
				direction = 0;
			}
		}

	} else {
		fleeing = false;
		chillin = true;
	}

	// GET NEXT STATE

	if(getDistance(player) < 160) {
		fleeing = true;
	}

	else {
		fleeing = false;
		chillin = true;
	}
}
