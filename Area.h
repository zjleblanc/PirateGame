#include "Sprite.h"
#include <vector>
#include <string>
using namespace std;

#ifndef AREA_H
#define AREA_H

class Area {
public:
	Area(string);
	Area(int, int);
	int getWidth();
	int getHeight();
	char getTile(int,int);
private:
	int width, height;
	vector< vector<char>> tileIndex;
	string fileName;
};

#endif
