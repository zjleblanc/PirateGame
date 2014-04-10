#ifndef CHEST_H
#define CHEST_H

#include "Entity.h"
#include <string>
using namespace std;

class Chest : public Entity {
public:
	Chest(int, int);
	void update(Display*);
	int getx();
	int gety();
	int isopen();
	void openChest();

private:
	int open;
};
#endif