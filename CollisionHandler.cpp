#include "CollisionHandler.h"

CollisionHandler::CollisionHandler() {

}

void CollisionHandler::handleAI_to_AI() {

	int w = 32;
	int h = 32;
	int x0, y0;
	int x1, y1;

	int d0, d1;

	bool inxRange, inyRange;

	for(int i = 1; i < AI_Unit::enemyList.size(); i++) {

		for(int k = i; k < AI_Unit::enemyList.size(); k++) {

			x0 = AI_Unit::enemyList[i-1]->getX();
			y0 = AI_Unit::enemyList[i-1]->getY();
			x1 = AI_Unit::enemyList[k]->getX();
			y1 = AI_Unit::enemyList[k]->getY();

			inxRange = (x0 >= x1 && x0 <= x1 + w) || (x0 + w >= x1 && x0 + w <= x1 + w);
			inyRange = (y0 >= y1 && y0 <= y1 + h) || (y0 + h >= y1 && y0 + h <= y1 + h);

			if(inxRange && inyRange) {

				d0 = AI_Unit::enemyList[i-1]->getDirection();
				d1 = AI_Unit::enemyList[k]->getDirection();

			}

		}

	}

}

void CollisionHandler::handleAI_to_Projectile() {

	int xAI, yAI;
	int xP, yP;
	bool inxRange, inyRange;
	char tag;

	for(int i = 0; i < AI_Unit::enemyList.size(); i++) {

		for(int k = 0; k < Projectile::projectileList.size(); k++) {

			xAI = AI_Unit::enemyList[i]->getX();
			yAI = AI_Unit::enemyList[i]->getY();
			xP = Projectile::projectileList[k]->getX();
			yP = Projectile::projectileList[k]->getY();
			tag = Projectile::projectileList[k]->getTag();

			inxRange = (xAI >= xP && xAI <= xP + 16) || (xAI + 32 >= xP && xAI + 32 <= xP + 16);
			inyRange = (yAI >= yP && yAI <= yP + 16) || (yAI + 32 >= yP && yAI + 32 <= yP + 16);

			if(inxRange && inyRange && (tag == 'p')) {

				Projectile::projectileList[k]->setZ(0);
				AI_Unit::enemyList[i]->subHealth(25);

			}

		}

	}

}
