#include <string>
#include "TextWriter.h"
#include "SDL_ttf.h"
#include "SDL_image.h"
#include "SDL.h"
#include "Textbox.h"

Textbox::Textbox(){
	char* text = NULL;
	isOpen = false;
	loadImage();
}

void Textbox::loadImage(){
	SDL_Surface* loadedImage = NULL;
	SDL_Surface* optimizedImage = NULL;
	loadedImage = IMG_Load("textbox.png");
	if(loadedImage!=NULL){
		optimizedImage = SDL_DisplayFormat(loadedImage);
		SDL_FreeSurface(loadedImage);
	}
	boxImage = optimizedImage;
}

void Textbox::display(SDL_Surface* screen, TextWriter* tw){
	SDL_Rect offset;
	offset.x = 100;
	offset.y = 320;

	SDL_BlitSurface(boxImage, NULL, screen, &offset);
	if(text){
		tw->write(text, 150, 340, screen); 
	}
}

void Textbox::changeText(char* statement){
	text = statement;
}

void Textbox::turnOn(){
	isOpen = true;
}

void Textbox::turnOff(){
	isOpen = false;
}

bool Textbox::checkDisplay(){
	return isOpen;
}




