#include "Chest.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

Chest::Chest(int xplace, int yplace)
	: Entity("Terrain.png")
{
	x = xplace;
	y = yplace;
	open = 0;

	string line;
	fstream file("MainMap.txt", ios::in | ios::out);
	for(int i = 0; i < y; i++){
		getline(file, line);
	}
	file.seekp(x, ios_base::cur);
	file << "C";
	file.close();
	
}
		

int Chest::getx(){
	return x;
}

int Chest::gety(){
	return y;
}

int Chest::isopen(){
	if (open){
		return 1;
	} else{
		return 0;
	}
}

void Chest::openChest(){
	open = 1;
}

void Chest::update(Display* display) {

}