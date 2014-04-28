#include "Entity.h"
#include "Display.h"
#include "TextWriter.h"
#include "Textbox.h"
#include <string>
using namespace std;

#ifndef HUD_H
#define HUD_H

class HUD : public Entity {
public:
	HUD(string, int, int);
	void load();
	void render(int, int, SDL_Surface*);
	void update(Display*);
	void setCurrentShot(double);
	void setCurrentHealth(double);
	void setDoubloons(double);
	void setSinks(double);
	void IncreaseDoubloons();
private:
	TextWriter HUD_writer;
	Textbox* textbox;
	SDL_Rect statusBar;
	SDL_Rect tick;
	SDL_Rect scoring;
	double currentShot;
	double currentHealth;
	int maxCB, maxHP;
	string doubloons;
	double numdubs;
	string sinks;
};

#endif
