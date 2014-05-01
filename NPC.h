// Handles logic for all neutral non-playable characters

#include "Mobile.h"
#include "Display.h"
#include <string>
using namespace std;

#ifndef NPC_H
#define NPC_H

class NPC : public Mobile {
public:

	static vector<NPC*> NPC_list;

	NPC(string, int, int, int);
	void update(Display*);

private:

	bool toMove();
	void move(Display* display);

	int range;
	int xInit, yInit;
	int xMax, yMax;
	int xMin, yMin;
};

#endif
