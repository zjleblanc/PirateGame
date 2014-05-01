// Handles collisions between objects overlain on the main map. Collisions with the map are handled separately.

#include "Player.h"
#include "Projectile.h"
#include "AI_Unit.h"

#ifndef COLLISIONHANDLER_H
#define COLLISIONHANDLER_H

class CollisionHandler {
public:
	CollisionHandler();
	void handleAll(Player*);
	void handleAI_to_Projectile();
	void handleAI_to_Player(Player*);
	void handlePlayer_to_Projectile(Player*);
};

#endif
