#include "TextWriter.h"
#include "SDL_ttf.h"
#include "SDL_image.h"
#include "SDL.h"
using namespace std;

#ifndef TEXTBOX_H
#define TEXTBOX_H


class Textbox{
public:
	Textbox();
	void display(SDL_Surface*, TextWriter*);
	void changeText(char*);
	bool checkDisplay();
	void turnOn();
	void loadImage();
	void turnOff();

private:
	char* text;
	bool isOpen;
	SDL_Surface* boxImage;

};
#endif



