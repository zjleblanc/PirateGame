#include "AI_Unit.h"
#include <cstdlib>
#include <ctime>
#include <cmath>

vector<AI_Unit*> AI_Unit::enemyList;					// keeps track of all AI Units for CollisionHandler to scan

// CONSTRUCTOR

AI_Unit::AI_Unit(string path, int xi, int yi, int r, int diff, int size) 
	:Mobile(path, size) {

		srand(time(NULL));
		
		enemyList.push_back(this);

		xInit = xi * 16;								// translate initial x, y to pixel precision
		yInit = yi * 16;

		x = xInit;										// set AI x, y to the provided initial values (x and y are stored in entity)
		y = yInit;

		range = r * 16;									// sets maximum range that AI units can travel in without being engaged

		updateCount = 0;								// these two variables control how fast AI responds to incoming information
		difficulty = diff;

		pillaged = false;
}

//DECONSTRUCTOR

AI_Unit::~AI_Unit() {
	delete enemyHealth;
}

// PRIVATE METHODS

double AI_Unit::getDistance(Player* player) {			// distance function with player, this AI Unit as inputs

	double xdistance = pow((double)(player->getX() - x), 2);
	double ydistance = pow((double)(player->getY() - y), 2);
	double distance = sqrt(xdistance + ydistance);

	return distance;

}

bool AI_Unit::atRangeLimit() {							// checks to see if AI is leaving its range

	if((x == xInit - range) || (x == xInit + range)) {
		return true;	
	}

	if((y == yInit - range) || (y == yInit + range)) {
		return true;
	}

	return false;
}

// PUBLIC METHODS

// GETTERS AND SETTERS

void AI_Unit::subHealth(int damage) {
	enemyHealth->subHealth(damage);						// enemyHealth is instantiated in the child class constructor
}

bool AI_Unit::isSunk() {
	return sunk;
}

bool AI_Unit::canContactDamage() {
	return contactDamages;
}

void AI_Unit::sink() {
	sunk = true;
}

bool AI_Unit::isPillaged() {
	return pillaged;
}

void AI_Unit::setPillaged() {
	pillaged = true;
}

