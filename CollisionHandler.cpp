#include "CollisionHandler.h"
#include <cstdlib>
#include <ctime>

// CONSTRUCTOR

CollisionHandler::CollisionHandler() {
	srand(time(NULL));
}

// PUBLIC METHODS

void CollisionHandler::handleAI_to_Projectile() {

	int xAI, yAI;									// AI position
	int xP, yP;										// projectile position
	bool inxRange, inyRange;						// within the x,y range of the hitbox
	char tag;										// only hits if tag is correct

	for(int i = 0; i < AI_Unit::enemyList.size(); i++) {

		for(int k = 0; k < Projectile::projectileList.size(); k++) {				// checks each unit for each projectile

			xAI = AI_Unit::enemyList[i]->getX();							
			yAI = AI_Unit::enemyList[i]->getY();
			xP = Projectile::projectileList[k]->getX() + Projectile::projectileList[k]->getdx();		// all info from static vectors
			yP = Projectile::projectileList[k]->getY() + Projectile::projectileList[k]->getdy();
			tag = Projectile::projectileList[k]->getTag();

			inxRange = (xAI >= xP && xAI <= xP + 16) || (xAI + 32 >= xP && xAI + 32 <= xP + 16);		// checks to see if either boundary of the 
			inyRange = (yAI >= yP && yAI <= yP + 16) || (yAI + 32 >= yP && yAI + 32 <= yP + 16);		// AI is within the projectile hitbox

			if(inxRange && inyRange && (tag == 'p') && !AI_Unit::enemyList[i]->isSunk() && Projectile::projectileList[k]->isActive()) {

				Projectile::projectileList[k]->setZ(0);
				Projectile::projectileList[k]->setParticleType(SHIP);				// emulate projectile collision if it's a player projectile
				AI_Unit::enemyList[i]->subHealth(25);

			}

		}

	}

}

void CollisionHandler::handleAI_to_Player(Player* player) {

	int xP = player->getX() + 16;					
	int yP = player->getY() + 16;

	int x0, y0, x1, y1;									//Enemy hitbox bounds
	bool inxRange, inyRange;

	for(int i = 0; i < AI_Unit::enemyList.size(); i++) {		// check all enemies against the player

		x0 = AI_Unit::enemyList[i]->getX();
		y0 = AI_Unit::enemyList[i]->getY();
		x1 = x0 + AI_Unit::enemyList[i]->getSize() * 16;		// gets enemy positions from static AI vector
		y1 = y0 + AI_Unit::enemyList[i]->getSize() * 16;

		inxRange = (xP >= x0) && (xP <= x1);					//checks to see if enough of the enemy hitbox overlaps with player
		inyRange = (yP >= y0) && (yP <= y1);

		if(inxRange && inyRange && !AI_Unit::enemyList[i]->isSunk() && AI_Unit::enemyList[i]->canContactDamage() && player->isSailing()) {
			
			AI_Unit::enemyList[i]->sink();						// evaluates damage if enemy is a contact damager, like an iceberg
			player->subHealth(100);
		
		}

		if(inxRange && inyRange && AI_Unit::enemyList[i]->isSunk() && !AI_Unit::enemyList[i]->isPillaged()) {

			player->addDoubloons((rand() % 100) / 10);		// tries to pillage sunken enemies
			player->incrementSinks();
			AI_Unit::enemyList[i]->setPillaged();

		}

	}

}

void CollisionHandler::handlePlayer_to_Projectile(Player* player) {

	int xP = player->getX();
	int yP = player->getY();
	int xR, yR;										// projectile location
	bool inxRange, inyRange;						// within the x,y range of the hitbox
	char tag;										// only hits if tag is correct

	for(int k = 0; k < Projectile::projectileList.size(); k++) {

		xR = Projectile::projectileList[k]->getX() + Projectile::projectileList[k]->getdx();		// gets projectile location from static 
		yR = Projectile::projectileList[k]->getY() + Projectile::projectileList[k]->getdy();		// projectile vector
		tag = Projectile::projectileList[k]->getTag();

		inxRange = (xP >= xR && xP <= xR + 16) || (xP + 32 >= xR && xP + 32 <= xR + 16);			// checks for hitbox overlap
		inyRange = (yP >= yR && yP <= yR + 16) || (yP + 32 >= yR && yP + 32 <= yR + 16);

		if(inxRange && inyRange && (tag == 'a') && Projectile::projectileList[k]->isActive()  && player->isSailing()) {

			Projectile::projectileList[k]->setZ(0);							// evaluate for projectile collision if it's an enemy projectile
			player->subHealth(25);

		}

	}
}
