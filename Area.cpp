#include "Area.h"
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <string>
using namespace std;

// CONSTRUCTOR (FILE GENERATED MAPS)

Area::Area(string path) {

	fileName = path;

	ifstream areaFile(path.c_str());					// prepares input file

	vector<char> temp;									// stores each line as a temporary vector
	string currentLine;
	height = 0;
	unsigned int i;

	while(!areaFile.eof()) {
		
		temp.clear();									// clear last line in temp, load in next line
		getline(areaFile,currentLine); 
		
		for(i = 0; i < currentLine.length(); i++) {
			if(currentLine[i] != ' ') {
				temp.push_back(currentLine[i]);			// adds chars from file to vector
			}
		}
		
		height++;
		tileIndex.push_back(temp);						// pushes line into map vector
		
	}

	width = tileIndex[0].size();

}

// CONSTRUCTOR (RANDOMLY GENERATED MAPS - used for debugging)

/* Area::Area(int areaW, int areaH) {
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
				temp.push_back('G');
				break;
			case 2:
				temp.push_back('W');
				break;
			case 3: 
				temp.push_back('B');
				break;
			default:
				temp.push_back('I');
			}
		}

		tileIndex.push_back(temp);
		temp.clear();

	}
} */

// PUBLIC METHODS

// GETTERS AND SETTERS

int Area::getWidth() const {
	return width;
}

int Area::getHeight() const {
	return height;
}

char Area::getTile(int x, int y) {
	 return tileIndex[y][x];
}

string Area::getPath() const{
	return fileName;
}
