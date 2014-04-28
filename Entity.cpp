#include "Entity.h"
using namespace std;

Entity::Entity(string pathName)
	:sheet(pathName),
	g(-9.8)
{
	x = 0;
	y = 0;
}

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
