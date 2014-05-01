// This class handles all enemies that make use of AI state machines 

#include "Mobile.h"
#include "Player.h"
#include "HealthBar.h"

#ifndef AI_UNIT_H
#define AI_UNIT_H

class AI_Unit : public Mobile {
public:

	static vector<AI_Unit*> enemyList;

	AI_Unit(string, int, int, int, int, int);
	~AI_Unit();
	virtual void update(Display*) = 0;
	virtual void runAI(Player*, Display*) = 0;
	virtual void renderAttrib(SDL_Surface*, Display*, Player*) = 0;
	void subHealth(int);
	bool isSunk();
	bool canContactDamage();
	void sink();
	double getDoubloons();
	bool isPillaged();
	void setPillaged();
protected:
	int xInit, yInit;
	int range;
	double getDistance(Player*);
	bool atRangeLimit();
	int updateCount;			// updateCount % difficulty determines how fast AI can respond to events
	int difficulty;				// lower # -> higher difficulty
	HealthBar* enemyHealth;
	bool sunk;
	bool contactDamages;
	bool pillaged;
};

#endif
