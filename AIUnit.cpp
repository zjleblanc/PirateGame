#include "AI_Unit.h"

vector<AI_Unit*> AI_Unit::enemyList;

AI_Unit::AI_Unit(string path, int xi, int yi, int r, int diff, int size) 
	:Mobile(path, size) {

		enemyList.push_back(this);

		xInit = xi * 16;
		yInit = yi * 16;
		x = xInit;
		y = yInit;
		range = r * 16;
		aggro = false;
		updateCount = 0;
		difficulty = diff;
}

AI_Unit::~AI_Unit() {
	delete enemyHealth;
}

bool AI_Unit::isAggro() {
	return aggro;
}

double AI_Unit::getDistance(Player* player) {

	double xdistance = pow((double)(player->getX() - x), 2);
	double ydistance = pow((double)(player->getY() - y), 2);
	double distance = sqrt(xdistance + ydistance);

	return distance;

}

bool AI_Unit::atRangeLimit() {

	if((x == xInit - range) || (x == xInit + range)) {
		return true;	
	}

	if((y == yInit - range) || (y == yInit + range)) {
		return true;
	}

	return false;
}

void AI_Unit::subHealth(int damage) {
	enemyHealth->subHealth(damage);
}
