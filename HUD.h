// Handles rendering and updating of the main HUD display based on data from the player

#include "Entity.h"
#include "Display.h"
#include "TextWriter.h"
#include <string>
using namespace std;

#ifndef HUD_H
#define HUD_H

class HUD : public Entity {
public:

	HUD(string, int, int);

	void render(int, int, SDL_Surface*);
	void update(Display*);

	void setCurrentShot(double);
	void setCurrentHealth(double);
	void setDoubloons(double);
	void setSinks(double);

private:

	void load();

	TextWriter HUD_writer;
	SDL_Rect statusBar;
	SDL_Rect tick;
	SDL_Rect scoring;
	double currentShot;
	double currentHealth;
	int maxCB, maxHP;
	string doubloons;
	string sinks;
};

#endif
