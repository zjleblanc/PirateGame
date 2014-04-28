#include "Chest.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

Chest::Chest(int xplace, int yplace){
	x = (xplace / 2);
	y = yplace;
	open = 0;

	string line;
	fstream file("MainMap.txt", ios::in | ios::out);
	for(int i = 0; i < yplace; i++){
		getline(file, line);
	}
	file.seekp(xplace, ios_base::cur);
	file << "C";
	file.close();
	
}
		

int Chest::getx(){
	return x;
}

int Chest::gety(){
	return y;
}

int Chest::isOpen(){
	if (open){
		return 1;
	} else{
		return 0;
	}
}

void Chest::openChest(){
		open = 1;
}




