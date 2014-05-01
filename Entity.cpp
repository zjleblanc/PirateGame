#include "Entity.h"
using namespace std;

// CONSTRUCTOR

Entity::Entity(string pathName)
	:sheet(pathName),
	g(-9.8)								// gravitational constant used for particle/ projectile physics
{
	x = 0;
	y = 0;
}

// PUBLIC METHODS

// GETTERS AND SETTERS

int Entity::getX() {
	return x;
} 

int Entity::getY() {
	return y;
}

void Entity::setLocation(int newX, int newY) {
	x = newX;
	y = newY;
}
