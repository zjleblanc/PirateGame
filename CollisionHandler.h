#include "Player.h"
#include "Projectile.h"
#include "AI_Unit.h"

#ifndef COLLISIONHANDLER_H
#define COLLISIONHANDLER_H

class CollisionHandler {
public:
	CollisionHandler();
	void handleAll(Player*);
private:
	void handleAI_to_AI();
	void handleAI_to_Projectile();
	void handleAI_to_Player(Player*);
	void handlePlayer_to_Projectile(Player*);
};

#endif
