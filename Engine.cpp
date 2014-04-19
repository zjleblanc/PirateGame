#include "SDL.h"
#include "SDL_image.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "TextWriter.h"
#include "AudioHandler.h"
#include "Player.h"
#include "NPC.h"
#include "Entity.h"
#include "Display.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h"
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <Windows.h>
#include <stdio.h>
using namespace std;

////////////////////////// GLOBALS //////////////////////////////////////////////

SDL_Event event;
SDL_Surface* screen = NULL;
Uint32 startTime = 0;

////////////////////////// ENGINE INTERFACE /////////////////////////////////////

class Engine {
public:
	Engine();
	~Engine();
	void close();
	void run();
	void update();
	void render();
	bool start();
private:
	void eliminateCollisions();
	const int WIDTH, HEIGHT, BPP;
	int leftReleased, rightReleased;
	Keyboard *keyboard;
	Mouse *mouse;
	Display *display;
	TextWriter *textWriter;
	AudioHandler* audio;
	Player *player;
	//Mobile *rando;
	vector< Mobile * > randos;
};

////////////////////////// ENGINE FUNCTIONS /////////////////////////////////////

Engine::Engine() 
	: WIDTH(640),
	HEIGHT(480),
	BPP(32) {

	if(!start()) {
		close();
	}

	leftReleased=1;
	rightReleased=1;
	keyboard = new Keyboard();
	mouse = new Mouse();
	display = new Display(WIDTH, HEIGHT);
	textWriter = new TextWriter(30);
	player = new Player("Player3.png");
	player->setLocation(WIDTH, HEIGHT);
	//rando = new NPC("Player3.png", 5, (WIDTH) / 16, (HEIGHT) / 16);
	for(int i=-5; i<6; i++){
		Mobile * temp = new NPC("Player3.png", 50, (WIDTH + 32*i) / 16, (HEIGHT+32*i) / 16);
		randos.push_back(temp);
	}
	audio = new AudioHandler();

	audio->initialize();
	audio->play(LANDMUSIC);
}

Engine::~Engine() {
	delete keyboard;
	delete mouse;
	delete display;
	delete textWriter;
	delete player;
	for(int i=0; i<randos.size(); i++)
		delete randos[i];
}

bool Engine::start() {

	// Open SDL

	if(SDL_Init(SDL_INIT_EVERYTHING) == -1) {
		return false;
	}

	// Setup Window

	screen = SDL_SetVideoMode(WIDTH, HEIGHT, BPP, SDL_HWSURFACE | SDL_DOUBLEBUF);
	if(!screen) {
		return false;
	}
	
	SDL_WM_SetCaption("Reef Raider", NULL);

	SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY, SDL_DEFAULT_REPEAT_INTERVAL);

	return true;
}

void Engine::close() {
	SDL_Quit();
	delete this;
}

void Engine::eliminateCollisions(){
	for(int i=0; i<randos.size(); i++){
		if(randos[i]->getX()/16 == player->getX()/16 && randos[i]->getY()/16 == player->getY()/16){
			randos.erase(randos.begin()+i);
			return;
		}
	}
}

void Engine::run() {
	bool quit = false;
	startTime = SDL_GetTicks();
	Uint32 last = SDL_GetTicks();
	Uint32 timer = last;
	Uint32 now;
	int upsPerSecond = 70;
	int frames = 0;

	while(!quit) {
		now = SDL_GetTicks();

		if((now - last) > (1000/upsPerSecond)) {
			update();
			last = now;
			display->ctrIncrement();
		}

		render();
		frames++;

		if(timer - now >= 1000) {
			stringstream fps;
			fps << "Reef Raider   |   " << frames << " FPS";
			SDL_WM_SetCaption(fps.str().c_str(), NULL);
			timer += 1000;
			frames = 0;
		}

		if(SDL_PollEvent(&event)) {
			if(event.type == SDL_QUIT) {
				quit = true;
			}
		}

	}

}

void Engine::update() {
	if(!leftReleased)
		if(mouse->buttonReleased(1)) leftReleased=1;
	if(!rightReleased)
		if(mouse->buttonReleased(3)) rightReleased=1;
	player->update(display);
	//if(updateTimer!=0) updateTimer++;	//timer used to correct multiple spawns from one click
	//if(updateTimer>=10) updateTimer=0;
	//rando->update(display);
	if(mouse->buttonPressed()==1 && leftReleased && randos.size() > 0){ //last check to prevent crash when left click and no NPCs present
		randos.pop_back();
		leftReleased=0;
	}
	else if(mouse->buttonPressed()==3 && rightReleased){ 
		//add new NPC at location of mouse click
		randos.push_back(new NPC("Player3.png", 50,player->getX()/16 - 20 + mouse->getX()/16,player->getY()/16 - 15 + mouse->getY()/16));
		rightReleased=0;
	}
	/*ostringstream os_;    
	os_ << "X: " << player->getX()/16 << " Y: " << player->getY()/16 << endl;
	os_ << "X: " << randos[1]->getX()/16 << " Y: " << randos[1]->getY()/16 << endl; 
	OutputDebugString( os_.str().c_str() );  // Debugging Player location */
	Engine::eliminateCollisions();

	for(int i=0; i<randos.size(); i++){
		randos[i]->update(display);
	}

	int xp = player->getX();
	int yp = player->getY();

	display->setOffsets(xp - WIDTH / 2, yp - HEIGHT / 2);

	if(player->isSailing()) {
		audio->switchTo(BOATMUSIC);
	} 
	else if(!(player->isSailing())) {
		audio->switchTo(LANDMUSIC);
	}

}

void Engine::render() {
	SDL_FillRect(screen, NULL, 0x000000);
	display->render(screen);
	player->render(WIDTH/2, HEIGHT/2, screen);
	player->renderAttrib(screen, display);
	for(int i=0; i<randos.size(); i++){
		int xR = (WIDTH/2) + (randos[i]->getX() - player->getX());
		int yR = (HEIGHT/2) + (randos[i]->getY() - player->getY());
		randos[i]->render(xR,yR,screen);
	}
	//rando->render(xR, yR, screen);
	//textWriter->write(display->getCurrentTile(), 50, 50, screen);
	//textWriter->write(display->getOffsets(), 50, 50, screen);
	//display->getOffsets();
	SDL_Flip(screen);
}

////////////////////////// DRIVER /////////////////////////////////////

int main(int argc, char **args) {
	Engine *engine = new Engine;

	if(!engine->start()) {
		return 1;
	}

	engine->run();

	engine->close();
}
