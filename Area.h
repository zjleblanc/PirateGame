// Reads in a map, or generates one, and stores this info as a vector for other objects to access

#include "Sprite.h"
#include <iostream>
#include <vector>
#include <string>
using namespace std;

#ifndef AREA_H
#define AREA_H

class Area {
public:
	Area(string);
	Area(int, int);
	int getWidth() const;
	int getHeight() const;
	char getTile(int,int);
	string getPath() const;
private:
	int width, height;
	vector< vector<char>> tileIndex;
	string fileName;
};

#endif
