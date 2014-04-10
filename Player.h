#pragma once
#include "SpriteSheet.h"
#include "Mobile.h"
#include "Projectile.h"
#include "Display.h"
#include "Chest.h"



#include "Ship.h"
#include "Keyboard.h"
#include "Sprite.h"
#include <string>
using namespace std;

#ifndef PLAYER_H
#define PLAYER_H

class Player : public Mobile {
public:
	Player(string);
	~Player();
	void update(Display*); 
	void renderAttrib(SDL_Surface*, Display* display);
	void render(int, int, SDL_Surface*);
	bool isSailing();
	void opening(SDL_Surface*, Display*);
private:
	void processInput(Display* display);
	void renderLand(int, int, SDL_Surface*);
	void renderSea(int, int, SDL_Surface*);
	void toBoat(Display*);
	void fireProjectile();
	void openChest(SDL_Surface*, Display*);
	Ship* playerVessel;
	Projectile* left_projectile;
	Projectile* right_projectile;
	Keyboard* keyboard;
	bool shipState;
};

#endif