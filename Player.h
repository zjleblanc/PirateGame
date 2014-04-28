#include "SpriteSheet.h"
#include "Mobile.h"
#include "Projectile.h"
#include "Display.h"
#include "Ship.h"
#include "HUD.h"
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
	void openChest(Display*, SDL_Surface*);
private:
	void processInput(Display* display);
	void renderLand(int, int, SDL_Surface*);
	void renderSea(int, int, SDL_Surface*);
	void toBoat(Display*);
	void fireProjectile();
	Ship* playerVessel;
	Projectile* left_projectile;
	Projectile* right_projectile;
	Keyboard* keyboard;
	HUD playerHUD;
	bool shipState;
	int numProjectiles;
	int maxHealth, currentHealth;
	int doubloons;
	int sinks;
};

#endif