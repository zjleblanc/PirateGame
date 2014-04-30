#include "Chest.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

Chest::Chest(int xplace, int yplace){
	x = xplace;		//set x and y coordinates for Chest
	y = yplace;		//used to identify chests in chestArray in display
	open = 0;

	
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




