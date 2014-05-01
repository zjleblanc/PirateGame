#include "Projectile.h"
#include "SDL.h"
#include <algorithm>

// OBJECT LIST

vector<Projectile*> Projectile::projectileList;					// list of projectiles used for collision detection

// CONSTRUCTOR

Projectile::Projectile(string pathName) 
	:Entity(pathName),
	sprite(sheet.getSurface(), 0, 0, 16, true, false)
{
	
	projectileList.push_back(this);								// add this projectile to the list

	z = 3;
	x = 0;
	y = 0;
	vxy = 0;													// initialize all velocities / positions
	vz = 0;
	fireState = false;
	direction = 0;
	lastTime = 0;
	particleType = WATER;			
}

// PUBLIC METHODS

void Projectile::render(int xRender, int yRender, SDL_Surface* screen) {
	if(fireState) {																	// if the projectile is active, render it at its location
		sprite.render(xRender + x + (int)dx, yRender + y + (int)dy, screen);
	}

	if(particles.size() != 0) {														// render the array of particles associated with the projectile
		renderParticles(xRender, yRender, screen);
	}
}

void Projectile::update(Display* display) {

	double dt;

	// Update Time
	if(lastTime) {
		dt = (double)(SDL_GetTicks() - lastTime) / 1000;
	} else {
		dt = 0;
	}
	lastTime = SDL_GetTicks();
	
	// Get z-Directional Change

	vz += g * dt;
	z += vz * dt;

	// Get xyPlane-Directional Change

	switch(direction) {
	case 0:
		dy -= vxy * dt;
		break;
	case 2:
		dy += vxy * dt;
		break;
	case 3:
		dx -= vxy * dt;
		break;
	case 1:
		dx += vxy * dt;
		break;
	}

	Sprite* nextTile = getNextTile(display);
	bool isWater = (nextTile == display->getWaterHandle(1)) || (nextTile == display->getWaterHandle(2));

	if(nextTile->isSolid() && !isWater) {				// makes the projectile inactive if it hits a solid object (that isn't water)
		z = 0;
	}

	if((z <= 0) && fireState) {							// upon collision with the ground or an object, create particles at this location
		particleX = x + dx;
		particleY = y + dy;
		createParticles(particleType);
	}

	if(z <= 0) {										// reset if the projectile isn't active
		fireState = false;
		dx = 0; 
		dy = 0;
		vz = 0;
		lastTime = 0;
	}

}

void Projectile::fire() {								// sets projectile to active and sets velocity
	fireState = true;
	vxy = 200;
}

void Projectile::updateParticles(Display* display) {

	bool toRemove = true;

	for(int i = 0; i < particles.size(); i++) {			// for all of the active particles, run the next timestep in their trajectory

		particles[i]->update(display);

		if(!(particles[i]->isDead())) {					// once all particles are dead, remove them all
			toRemove = false;
		}

	}

	if(toRemove) {
		particles.clear();
	}

}

// GETTERS AND SETTERS

int Projectile::getdx() {						// current projectile offsets from initial x, y
	return (int)dx;
}

int Projectile::getdy() {
	return (int)dy;
}

char Projectile::getTag() {						// tag determines which mobiles it can hit
	return tag;
}

void Projectile::setElevation(double newHeight) {
	z = newHeight;
}

void Projectile::setDirection(int newdir) {
	direction = newdir;
}

void Projectile::setTag(char newTag) {
	tag = newTag;
}

void Projectile::setZ(int newZ) {
	z = newZ;
}

void Projectile::setParticleType(type TYPE) {				// change the type of particles rendered on collision
	particleType = TYPE;
}

bool Projectile::isActive() {
	return fireState;
}

// PRIVATE METHODS

void Projectile::createParticles(type TYPE) {							// creates an array of particles, called upon collisions
	particles.clear();
	for(int i = 0; i < 35; i++) {
		particles.push_back(new Particle("Particles.png", 5, particleType, 15));
	}
}

void Projectile::renderParticles(int xRender, int yRender, SDL_Surface* screen) {		// render the current particle array

	for(int i = 0; i < particles.size(); i++) {
		particles[i]->render(particleX + xRender, particleY + yRender, screen);
	}

}

Sprite* Projectile::getNextTile(Display* display) {					// returns the next tile in the projectile's path based on the direction
	Sprite* nextTile;
	int xColl = x + dx;
	int yColl = y + dy;

	switch(direction) {
	case 0:
		nextTile = display->getSprite((xColl >> 4), (yColl >> 4) - 1);			// conversions to tile precision are necessary
		break;																	// when calling display->getSprite
	case 2:
		nextTile = display->getSprite((xColl >> 4), (yColl >> 4) + 1);
		break;
	case 3:
		nextTile = display->getSprite((xColl >> 4) - 1, (yColl >> 4));
		break;
	case 1:
		nextTile = display->getSprite((xColl >> 4) + 1, (yColl >> 4));
		break;
	}

	return nextTile;
}
