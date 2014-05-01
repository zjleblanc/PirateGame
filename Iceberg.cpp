#include "Iceberg.h"
#include <cmath>
#include <ctime>
#include <cstdlib>

// CONSTRUCTOR

Iceberg::Iceberg(string path, int xi, int yi, int r, int size, int diff) 
	:AI_Unit(path, xi, yi, r, size, diff),
	shattered(sheet.getSurface(),  0, 3, 32, false, false)
{
	srand(time(NULL));

	chillin = true;											// set initial states
	chasing = false;
	engaged = false;

	moving = false;
	sunk = false;
	contactDamages = true;

	enemyHealth = new HealthBar("Health.png", 25);			// give the enemy a health bar
}

// PUBLIC METHODS

void Iceberg::update(Display* display) {

	updateCount++;											// used to determine how quickly AI responds to stimuli

	moving = continueMotion();								// ensures motion ends on a tile
	if(chasing) {
		moving = continueMotion();							// runs twice to make the enemy appear faster
	}

	if(enemyHealth->getHealth() <= 0) {
		sunk = true;
	}

}

void Iceberg::runAI(Player* player, Display* display) {

	if((updateCount % difficulty == 0) && !moving && !sunk) {	// determines next move when AI is idle and not sunk

		if(chillin) {
			chill(player, display);
		} else {
			chase(player, display);
		}

	}

}

void Iceberg::renderAttrib(SDL_Surface* screen, Display* display, Player* player) {		// render methods for enemy attributes
																						// such as sunken sprites and healthbars
	int WIDTH = display->getWidth() / 2;
	int HEIGHT = display->getHeight() / 2;

	int xP = WIDTH + (x - player->getX());
	int yP = HEIGHT + (y - player->getY());

	if(sunk) {
		shattered.render(xP, yP, screen);
	} else {
		enemyHealth->render(xP, yP - 16, screen);
	}

}

// PRIVATE METHODS

void Iceberg::chill(Player* player, Display* display) {

	int xDistance = x - player->getX(); 
	int yDistance = y - player->getY();
	double distance = sqrt(pow((double)xDistance,2) + pow((double)yDistance,2));

	bool waterNext = (getNextTile(display) == display->getWaterHandle(1)) || (getNextTile(display) == display->getWaterHandle(2));

	// PERFORM LOGIC

	bool toMove = false;

	if(rand() % 10 == 0) {
		toMove = true;
		direction = rand() % 4;				// random motion when not engaged
	}

	if(waterNext) {							// only move onto a tile if it's a water tile

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

	if(waterNext) {

		if(distance > 250) {				// starts chasing the player if they get too close
			chillin = true;
		} else {
			chillin = false; 
			chasing = true;
		}

	}

}

void Iceberg::chase(Player* player, Display* display) {

	int xDistance = x - player->getX(); 
	int yDistance = y - player->getY();

	bool waterNext = (getNextTile(display) == display->getWaterHandle(1)) || (getNextTile(display) == display->getWaterHandle(2));

	// PERFORM LOGIC

	if(waterNext) {					// only move onto a space if it is water

		if((abs(xDistance) > abs(yDistance))) {		// get most efficient path to the player
			if(xDistance > 0) {
				x-=2;
				direction = 3;
			} 
			else {
				x+=2;
				direction = 1;
			}
		} 
	
		else {
			if(yDistance > 0) {
				y-=2;
				direction = 0;
				} 
				else {
				y+=2;
				direction = 2;
			}
	
		}

	} else {
		chasing = false;					// if player goes out of range, go back to chillin
		chillin = true;
	}

}
