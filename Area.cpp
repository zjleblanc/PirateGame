#include "Area.h"
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <string>
using namespace std;

Area::Area(string path) {
	fileName = path;

	ifstream areaFile(path.c_str());

	vector<char> temp;
	string currentLine;
	int i;

	while(!areaFile.eof()) {
		
		temp.clear();
		getline(areaFile,currentLine); 
		
		for(i = 0; i < currentLine.length(); i++) {
			if(currentLine[i] != ' ') {
				temp.push_back(currentLine[i]);
			}
		}
		
		tileIndex.push_back(temp);
	
	}

	width = i;
	height = tileIndex[0].size();

}

Area::Area(int areaW, int areaH) {
	srand(time(NULL));

	height = areaH;
	width = areaW;

	vector<char> temp;

	for(int y = 0; y < height; y++) {
		
		for(int x = 0; x < width; x++) {
			switch(rand() % 8) {
			case 0:
				temp.push_back('I');
				break;
			case 1:
				temp.push_back('B');
				break;
			case 2:
				//temp.push_back('A');
			default:
				temp.push_back('I');
			}
		}

		tileIndex.push_back(temp);
		temp.clear();

	}
}

int Area::getWidth() {
	return width;
}

int Area::getHeight() {
	return height;
}

char Area::getTile(int x, int y) {
	 return tileIndex[y][x];
}
