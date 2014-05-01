// Handles physics and rendering for particles 

#include "Entity.h"
#include <string>
using namespace std;

#ifndef PARTICLE_H
#define PARTICLE_H

enum type {WATER, GROUND, SHIP};

class Particle : public Entity {
public:

	Particle(string, double, type, int);
	void render(int, int, SDL_Surface*);
	void update(Display*);

	double getZ();
	bool isDead();

private:

	void load();
	void loadGround();
	void loadShip();
	void loadWater();

	void generateTrajectory();

	type variety;
	double lastTime;
	double z;
	double dx, dy, dz;
	double vx, vy, vz;
	SDL_Rect particleImage;
	bool dead;
	int vmax;
};

#endif
