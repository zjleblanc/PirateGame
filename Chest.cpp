#include "Chest.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

//CONSTRUCTOR

Chest::Chest(int xplace, int yplace){
	x = (xplace);
	y = yplace;
	open = 0;
	
}
	
// PUBLIC METHODS

// GETTERS AND SETTERS

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




