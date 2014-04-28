#include "SDL.h"
#include "SDL_image.h"
#include "Chest.h"
#include "Keyboard.h"
#include "AudioHandler.h"
#include "Player.h"
#include "WorldObject.h"
#include "NPC.h"
#include "Warp.h"
#include "Pirate.h"
#include "Entity.h"
#include "Display.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h"
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
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
	void loadObjects();
	void loadWarps();
	void loadEnemies();
	void update();
	void render();
	bool start();
private:
	const int WIDTH, HEIGHT, BPP;
	Keyboard *keyboard;
	Display *display;
	AudioHandler* audio;
	Player *player;
	Mobile *rando;
	Area* mainArea;
	Area* house;
	Chest* chest1;
	Chest* chest2;
	Chest* chest3;
	vector<Pirate*> enemies;
	vector<WorldObject*> objects;
	vector<Warp*> warps;
};

////////////////////////// ENGINE FUNCTIONS /////////////////////////////////////

Engine::Engine() 
	: WIDTH(640),
	HEIGHT(480),
	BPP(32) {

	if(!start()) {
		close();
	}

	keyboard = new Keyboard();
	display = new Display(WIDTH, HEIGHT);

	mainArea = new Area("MainMap.txt");
	house = new Area("House.txt");
	chest1 = new Chest(164, 24);
	chest2 = new Chest(274, 59);
	chest3 = new Chest(290, 33);
	display->addChest(chest1);
	display->addChest(chest2);
	display->addChest(chest3);

	display->setArea(mainArea);

	player = new Player("Player3.png");
	player->setLocation(85 * 16, 85 * 16);
	rando = new NPC("Player3.png", 5, WIDTH / 16, HEIGHT / 16);
	audio = new AudioHandler();

	audio->initialize();
	audio->play(LANDMUSIC);
}

Engine::~Engine() {
	delete keyboard;
	delete display;
	delete player;
	for(int i = 0; i < objects.size(); i++) {
		delete objects[i];
	}
	for(int i = 0; i < enemies.size(); i++) {
		delete enemies[i];
	}
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

	loadObjects();
	loadWarps();
	loadEnemies();

	return true;
}

void Engine::close() {
	SDL_Quit();
	delete this;
}

void Engine::run() {
	bool quit = false;
	startTime = SDL_GetTicks();
	Uint32 last = SDL_GetTicks();
	Uint32 timer = last;
	Uint32 now;
	int upsPerSecond = 100;
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

void Engine::loadObjects() {

	//CAPITAL ISLAND TOP ROW

	objects.push_back(new WorldObject("Terrain.png", 3, 2, 3, 3, 50, 19));
	objects.push_back(new WorldObject("Terrain.png", 0, 5, 4, 4, 57, 18));
	objects.push_back(new WorldObject("Terrain.png", 6, 0, 6, 5, 40, 17));

	// CAPITAL ISLAND THIRD ROW

	objects.push_back(new WorldObject("Terrain.png", 12, 0, 4, 4, 40, 28));
	objects.push_back(new WorldObject("Terrain.png", 4, 5, 4, 4, 50, 28));
	objects.push_back(new WorldObject("Terrain.png", 8, 5, 4, 4, 35, 28));
	objects.push_back(new WorldObject("Terrain.png", 8, 5, 4, 4, 45, 28));
	objects.push_back(new WorldObject("Terrain.png", 12, 4, 4, 6, 57, 26));

	// CAPITAL ISLAND SECOND ROW

	objects.push_back(new WorldObject("Terrain.png", 0, 5, 4, 4, 35, 36));
	objects.push_back(new WorldObject("Terrain.png", 0, 5, 4, 4, 44, 36));
	objects.push_back(new WorldObject("Terrain.png", 0, 5, 4, 4, 53, 36));

	// CAPITAL ISLAND FIRST ROW

	objects.push_back(new WorldObject("Terrain.png", 0, 9, 4, 4, 41, 45));
	objects.push_back(new WorldObject("Terrain.png", 0, 9, 4, 4, 50, 45));
	objects.push_back(new WorldObject("Terrain.png", 0, 9, 4, 4, 59, 45));

	//Random Island
	objects.push_back(new WorldObject("Terrain.png", 11, 10, 2, 2, 83, 23));

	//Old Isle : Beach
	objects.push_back(new WorldObject("Terrain.png", 13, 10, 2, 2, 117, 78));
	objects.push_back(new WorldObject("Terrain.png", 11, 10, 2, 2, 126, 81));
	objects.push_back(new WorldObject("Terrain.png", 11, 9, 1, 1, 110, 80));
	objects.push_back(new WorldObject("Terrain.png", 11, 9, 1, 1, 139, 84));
	//Old Isle : Houses
	objects.push_back(new WorldObject("Terrain.png", 4, 12, 4, 4, 103, 54));
	objects.push_back(new WorldObject("Terrain.png", 0, 16, 4, 3, 113, 64));
	objects.push_back(new WorldObject("Terrain.png", 8, 12, 4, 4, 124, 58));
	objects.push_back(new WorldObject("Terrain.png", 12, 12, 4, 4, 136, 64));
}

void Engine::loadWarps() {
	warps.push_back(new Warp("Ships.png", 50, 22, 8, 15, mainArea, house));
}

void Engine::loadEnemies() {
	enemies.push_back(new Pirate("PirateShip.png", 100, 100, 50, 10, 2, AGGRESSIVE));
	enemies.push_back(new Pirate("PirateShip.png", 80, 80, 50, 10, 2, AGGRESSIVE));
	enemies.push_back(new Pirate("PirateShip.png", 89, 93, 50, 10, 2, AGGRESSIVE));
}

void Engine::update() {

	Area* currentArea = display->getCurrentArea();

	for(int i = 0; i < warps.size(); i++) {
		warps[i]->probeCollision(player, currentArea);
	}

	display->setArea(currentArea);
	player->update(display);
	rando->update(display);

	for(int i = 0; i < enemies.size(); i++) {
		enemies[i]->update(display);
		enemies[i]->runAI(player);
	}

	int xp = player->getX();
	int yp = player->getY();

	display->setOffsets(xp - WIDTH / 2, yp - HEIGHT / 2);

	if(player->isSailing()) {
		audio->switchTo(LANDMUSIC);
	} 
	else if(!(player->isSailing())) {
		audio->switchTo(LANDMUSIC);
	}

}

void Engine::render() {
	SDL_FillRect(screen, NULL, 0x000000);
	display->render(screen);

	for(int i = 0; i < objects.size(); i++) {
		int xRender = objects[i]->getX() - display->getXOffset();
		int yRender = objects[i]->getY() - display->getYOffset();
		objects[i]->render(xRender, yRender, screen);
	}


	for(int i = 0; i < enemies.size(); i++) {
		int xP = (WIDTH/2) + (enemies[i]->getX() - player->getX());
		int yP = (HEIGHT/2) + (enemies[i]->getY() - player->getY());

		enemies[i]->render(xP, yP, screen);
		enemies[i]->renderAttrib(screen, display, player);
	}

	int xR = (WIDTH/2) + (rando->getX() - player->getX());
	int yR = (HEIGHT/2) + (rando->getY() - player->getY());
	rando->render(xR, yR, screen);
	

	player->render(WIDTH/2, HEIGHT/2, screen);
	player->renderAttrib(screen, display);

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