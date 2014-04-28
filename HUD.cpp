#include "HUD.h"
#include "Textbox.h"
#include <sstream>

HUD::HUD(string pathName, int hpMax, int shotMax) 
	:Entity(pathName),
	HUD_writer(20)
{
		load();
		currentShot = 1;
		currentHealth = 1;
		maxCB = shotMax;
		maxHP = hpMax;
		setDoubloons(0);
		setSinks(0);
		textbox = new Textbox();
}

void HUD::load() {

	// Set rectangle bounds for loading images from the spritesheet

	statusBar.x = 0;
	statusBar.y = 0;
	statusBar.h = 64;
	statusBar.w = 144;

	tick.x = 0;
	tick.y = 64;
	tick.h = 8;
	tick.w = 1;

	scoring.x = 0;
	scoring.y = 128;
	scoring.h = 64;
	scoring.w = 144;
}

void HUD::render(int xRender, int yRender, SDL_Surface* screen) {

	if(textbox->checkDisplay()){
		textbox->display(screen, &HUD_writer);
	}


	// Set location offsets for rendering status bar to screen

	SDL_Rect statusBarOffset;
	statusBarOffset.x = 10;
	statusBarOffset.y = 10;

	SDL_BlitSurface(sheet.getSurface(), &statusBar, screen, &statusBarOffset);

	// Add damage counters to health bar, empty counters to cannonball bar

	int barLength = 70;

	// Get number of counters to be rendered

	int damageCtrs = (maxHP - currentHealth) / (maxHP / barLength);
	int emptyCtrs = (maxCB - currentShot) / (maxCB / barLength);

	// Render all damage counters

	for(int i = barLength; i > barLength - damageCtrs; i--) {
		statusBarOffset.x = x + 67 + i;
		statusBarOffset.y = y + 27;

		SDL_BlitSurface(sheet.getSurface(), &tick, screen, &statusBarOffset);
	}

	// Render all empty counters

	for(int i = barLength; i > barLength - emptyCtrs; i--) {
		statusBarOffset.x = x + 67 + i;
		statusBarOffset.y = y + 48;

		SDL_BlitSurface(sheet.getSurface(), &tick, screen, &statusBarOffset);
	}

	// Set location offsets for rendering status bar to screen

	SDL_Rect scoringOffset;
	scoringOffset.x = 500;
	scoringOffset.y = 10;

	SDL_BlitSurface(sheet.getSurface(), &scoring, screen, &scoringOffset);

	// Write current scores to textbox

	HUD_writer.write(doubloons.c_str(), 513, 15, screen);
	HUD_writer.write(sinks.c_str(), 513, 40, screen);

}

void HUD::update(Display* display) {

}

void HUD::setCurrentShot(double newPercent) {
	currentShot = newPercent;
}

void HUD::setCurrentHealth(double newPercent) {
	currentHealth = newPercent;
}

void HUD::setDoubloons(double dubs) {

	// converts incoming doubloon values to a string so it can be written to the HUD with TextWriter
	numdubs = dubs;
	if (dubs != 0){
		char* message = "        YOU FOUND A DOUBLOON!!!";
		textbox->changeText(message);
		textbox->turnOn();
	}
	
	ostringstream converter;
	converter << "Doubloons: ";
	converter << dubs;
	doubloons = converter.str();

}

void HUD::IncreaseDoubloons(){
	numdubs++;
	setDoubloons(numdubs);
}


void HUD::setSinks(double newSinks) {

	// converts incoming sink values to a string so it can be written to the HUD with TextWriter

	ostringstream converter;
	converter << "Sinks: ";
	converter << newSinks;
	sinks = converter.str();
	
}
