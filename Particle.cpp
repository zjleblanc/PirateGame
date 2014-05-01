#include "Particle.h"
#include "SDL.h"
#include <cstdlib>
#include <cmath>
#include <ctime>

// CONSTRUCTOR

Particle::Particle(string path, double zInit, type particleType, int maxV) 
	:Entity(path)
{
	srand(SDL_GetTicks());

	vmax = maxV;
	generateTrajectory();			// randomly generates vx and vy 
	lastTime = 0;
	dx = 0;						
	dy = 0;
	dz = 0;
	z = zInit;
	variety = particleType;
	dead = false;

	load();							// load in particle images

}

// PUBLIC METHODS

void Particle::render(int xRender, int yRender, SDL_Surface* screen) {	// renders particle at its current location
	SDL_Rect offset;

	offset.x = (xRender + (int)dx + 8);
	offset.y = (yRender + (int)dy + 8);

	SDL_BlitSurface(sheet.getSurface(), &particleImage, screen, &offset);
}

void Particle::update(Display* display) {
	
	double dt;

	// Update Time
	if(lastTime) {
		dt = (double)(SDL_GetTicks() - lastTime) / 1000;
	} else {
		dt = 0;
	}
	lastTime = SDL_GetTicks();

	if(abs(dz) < z) {
	
		vz += g * dt;				// translate based on timestamp
	
		dx += vx * dt;
		dy += vy * dt;
		dz += vz * dt;

	} else {
		dead = true;				// if z = 0, the particle has landed and is dead
	}
}

// GETTERS AND SETTERS

double Particle::getZ() {
	return z - dz;
}

bool Particle::isDead() {

return dead;

}

// PRIVATE METHODS

void Particle::load() {					// based on the particle type, calls the appropriate load method

	particleImage.h = 1;
	particleImage.w = 1;

	if(variety == GROUND) {
		loadGround();
	}
	else if(variety == SHIP) {
		loadShip();
	}
	else if(variety == WATER) {
		loadWater();
	}

}

void Particle::loadGround() {
	int color = rand() % 3;
	particleImage.x = 2;

	if(color == 0) {
		particleImage.y = 0;
	}
	else if(color == 1) {
		particleImage.y = 1;
	}
	else if(color == 2) {
		particleImage.y = 2;
	}

}

void Particle::loadShip() {
	int color = rand() % 3;
	particleImage.x = 1;

	if(color == 0) {
		particleImage.y = 0;
	}
	else if(color == 1) {
		particleImage.y = 1;
	}
	else if(color == 2) {
		particleImage.y = 2;
	}

}

void Particle::loadWater() {
	int color = rand() % 3;
	particleImage.x = 0;

	if(color == 0) {
		particleImage.y = 0;
	}
	else if(color == 1) {
		particleImage.y = 1;
	}
	else if(color == 2) {
		particleImage.y = 2;
	}

}

void Particle::generateTrajectory() {					// gets random trajectory 
	vx = vmax - rand() % (2 * vmax);
	vy = vmax - rand() % (2 * vmax);
	vz = 0;
}
