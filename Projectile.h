// Handles all projectile physics, rendering of projectiles, creates list of projectiles used to eval collisions

#include "Entity.h"
#include "Display.h"
#include "Sprite.h"
#include "Particle.h"
#include <string>
#include <vector>
using namespace std;

#ifndef PROJECTILE_H
#define PROJECTILE_H

class Projectile : public Entity {
public:

	static vector<Projectile*> projectileList;

	Projectile(string);

	void render(int, int, SDL_Surface*);
	void update(Display* display);
	void fire();
	void updateParticles(Display*);

	char getTag();
	int getdx();
	int getdy();
	void setElevation(double);
	void setZ(int);
	void setTag(char);
	void setDirection(int);
	void setParticleType(type);
	bool isActive();

private:

	void createParticles(type);
	void renderParticles(int, int, SDL_Surface*);
	Sprite* getNextTile(Display*);

	bool fireState;
	Uint32 lastTime;
	double vxy, vz;
	double z;
	double dx, dy;
	double maxDamage;
	int direction;
	Sprite sprite;
	vector<Particle*> particles;
	int particleX, particleY;
	char tag;
	type particleType;
};

#endif
