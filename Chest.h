// Handles the placing of chests on the map, as well as interactions with them

#ifndef CHEST_H
#define CHEST_H
#include "Mouse.h"
#include <string>
using namespace std;

class Chest {
public:
        Chest(int, int);
        int getx();
        int gety();
        int isOpen();
        void openChest();

private:
		int x, y;
        int open;
};
#endif
