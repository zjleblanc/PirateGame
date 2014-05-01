#include "SDL.h"
#include "SDL_image.h"
#include "Keyboard.h"
#include "AudioHandler.h"
#include "Player.h"
#include "WorldObject.h"
#include "NPC.h"
#include "Warp.h"
#include "Pirate.h"
#include "Iceberg.h"
#include "Entity.h"
#include "Display.h"
#include "CollisionHandler.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h"
#include "Windows.h"
#include <cmath>
#include <ctime>
#include <cstdlib>
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
	void runTitle();
	void runClosing();
	void loadObjects();
	void loadNPCs();
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
	Area* mainArea;
	Area* house;
	Chest* chest1;
	Chest* chest2;
	Chest* chest3;
	Chest* chest4;
	CollisionHandler* ch;
	vector<AI_Unit*> enemies;
	vector<WorldObject*> objects;
	vector<Warp*> warps;
	vector<NPC*> NPCs;
	int enemyCount;
};

////////////////////////// ENGINE FUNCTIONS /////////////////////////////////////

// CONSTRUCTOR

Engine::Engine() 
	: WIDTH(640),
	HEIGHT(480),
	BPP(32) {

	srand(time(NULL));

	if(!start()) {
		close();
	}

	keyboard = new Keyboard();

	display = new Display(WIDTH, HEIGHT);

	ch = new CollisionHandler();

	mainArea = new Area("MainMap.txt");

	chest1 = new Chest(164, 99);
	display->addChest(chest1);
	chest2 = new Chest(261, 86);
	display->addChest(chest2);
	chest3 = new Chest(314, 84);					// set up chests
	display->addChest(chest3);
	chest4 = new Chest(146, 22);
	display->addChest(chest4);

	display->setArea(mainArea);

	player = new Player("Player3.png");

	player->setLocation(85 * 16, 85 * 16);
	audio = new AudioHandler();

	audio->initialize();
	audio->play(OPENINGMUSIC);
}

// DECONSTRUCTOR

Engine::~Engine() {
	delete keyboard;
	delete display;
	delete player;
	delete chest1;
	for(int i = 0; i < objects.size(); i++) {
		delete objects[i];
	}
	for(int i = 0; i < enemies.size(); i++) {
		delete enemies[i];
	}
	for(int i = 0; i < NPCs.size(); i++) {
		delete NPCs[i];
	}
}

// METHODS

bool Engine::start() {					// starts engine, called immediately

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
	loadNPCs();
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
	int upsPerSecond = 70;
	int frames = 0;

	while(!quit && (player->getHealth() != 0)) {			// only update a fixed number of times a second
		now = SDL_GetTicks();

		if((now - last) > (1000/upsPerSecond)) {
			update();
			last = now;
			display->ctrIncrement();
		}

		render();						// but render as fast as possible
		frames++;

		if(timer - now >= 1000) {									// FPS counter
			stringstream fps;
			fps << "Reef Raider   |   " << frames << " FPS";
			SDL_WM_SetCaption(fps.str().c_str(), NULL);
			timer += 1000;
			frames = 0;
		}

		if(SDL_PollEvent(&event)) {
			if(event.type == SDL_QUIT) {					// quit if x is clicked
				quit = true;
			}
		}

	}

}

void Engine::runTitle() {				// runs initial screen

	bool advance = false;

	SDL_Surface* loadedImage = NULL;
	SDL_Surface* optImage = NULL;

	loadedImage = IMG_Load("TitleScreen.png");

	if(loadedImage != NULL) {
		optImage = SDL_DisplayFormat(loadedImage);
		SDL_FreeSurface(loadedImage);
	}

	SDL_BlitSurface(optImage, NULL, screen, NULL);
	SDL_Flip(screen);

	while(!advance) {
		if(SDL_PollEvent(&event)) {
			if(event.type = SDL_KEYDOWN) {
				if(event.key.keysym.sym == SDLK_r) {			// only start game when r is pressed
					advance = true;
				}
			}
		}
	}

	SDL_FreeSurface(optImage);

}

void Engine::runClosing() {

	bool quit = false;

	audio->switchTo(CLOSINGMUSIC);

	SDL_Surface* loadedImage = NULL;
	SDL_Surface* optImage = NULL;

	loadedImage = IMG_Load("EndScreen.png");				// start closing music, display end screen

	if(loadedImage != NULL) {
		optImage = SDL_DisplayFormat(loadedImage);
		SDL_FreeSurface(loadedImage);
	}

	SDL_BlitSurface(optImage, NULL, screen, NULL);
	SDL_Flip(screen);

	while(!quit) {
		if(SDL_PollEvent(&event)) {
			if(event.type == SDL_QUIT) {					// quit if x is clicked
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

	// OLD ISLAND BEACH

	objects.push_back(new WorldObject("Terrain.png", 13, 10, 2, 2, 237, 109));
	objects.push_back(new WorldObject("Terrain.png", 11, 10, 2, 2, 246, 112));
	objects.push_back(new WorldObject("Terrain.png", 11, 9, 1, 1, 230, 111));
	objects.push_back(new WorldObject("Terrain.png", 11, 9, 1, 1, 259, 115));

	// OLD ISLAND BUILDINGS

	objects.push_back(new WorldObject("Terrain.png", 4, 12, 4, 4, 223, 85));
	objects.push_back(new WorldObject("Terrain.png", 0, 16, 4, 3, 233, 95));
	objects.push_back(new WorldObject("Terrain.png", 8, 12, 4, 4, 244, 89));
	objects.push_back(new WorldObject("Terrain.png", 12, 12, 4, 4, 256, 95));

}

void Engine::loadNPCs() {
	NPCs.push_back(new NPC("Player3R.png", 10, WIDTH / 16, HEIGHT / 16));
	NPCs.push_back(new NPC("Player3R.png", 10, 41, 36));
	NPCs.push_back(new NPC("Player3R.png", 10, 26, 50));
	NPCs.push_back(new NPC("Player3R.png", 10, 50, 57));
	NPCs.push_back(new NPC("Player3R.png", 10, 234, 113));
	NPCs.push_back(new NPC("Player3R.png", 10, 253, 109));
	NPCs.push_back(new NPC("Player3R.png", 10, 253, 90));
	NPCs.push_back(new NPC("Player3R.png", 10, 225, 97));
}

void Engine::loadEnemies() {																	
	enemies.push_back(new Pirate("PirateShip.png", 100, 100, 50, 10, 2));
	enemies.push_back(new Pirate("PirateShip.png", 80, 80, 50, 10, 2));
	enemies.push_back(new Pirate("PirateShip.png", 89, 93, 50, 10, 2));
	enemies.push_back(new Pirate("PirateShip.png", 100, 50, 50, 10, 2));

	enemies.push_back(new Pirate("PirateShip.png", 190, 100, 50, 10, 2));
	enemies.push_back(new Pirate("PirateShip.png", 190, 100, 50, 10, 2));

	for(int i = 0; i < 8; i++) {
		enemies.push_back(new Pirate("PirateShip.png", 300, 40, 50, 10, 2));
		enemies.push_back(new Pirate("PirateShip.png", 200, 40, 50, 10, 2));		
		enemies.push_back(new Pirate("PirateShip.png", 150, 40, 50, 10, 2));
		enemies.push_back(new Pirate("PirateShip.png", 50, 110, 50, 10, 2));
	}

	for(int i = 0; i < 6; i++) {
		enemies.push_back(new Iceberg("Iceberg.png", 300, 100, 50, 10, 2));
	}

	enemies.push_back(new Iceberg("Iceberg.png", 110, 110, 50, 10, 2));

	enemyCount = 37;
}

void Engine::update() {

	Area* currentArea = display->getCurrentArea();

	display->setArea(currentArea);

	player->update(display);

	for(int i = 0; i < NPCs.size(); i++) {
		NPCs[i]->update(display);
	}

	for(int i = 0; i < enemies.size(); i++) {				// update player, NPCs, enemies
		enemies[i]->update(display);
		enemies[i]->runAI(player, display);
	}

	int xp = player->getX();
	int yp = player->getY();

	display->setOffsets(xp - WIDTH / 2, yp - HEIGHT / 2);				// update display based on player

	if(player->isSailing()) {
		audio->switchTo(BOATMUSIC);
	} 
	else if(player->getCurrentTile(display) == display->getIceHandle()) {				// update audio
		audio->switchTo(ICEMUSIC);
	}
	else if(!(player->isSailing())) {
		audio->switchTo(LANDMUSIC);
	}

	ch->handleAI_to_Projectile();
	ch->handlePlayer_to_Projectile(player);												// update collisions
	ch->handleAI_to_Player(player);

	if(enemyCount < 5) {															// make new enemies

		int xSpawn, ySpawn;

		do {

			double rads = ((rand() % 360) * 3.14) / 180;
			ySpawn = (10 * sin(rads)) + (player->getX() >> 4);
			xSpawn = (10 * cos(rads)) + (player->getY() >> 4);

		} while(!(display->getSprite(xSpawn,ySpawn) == display->getWaterHandle(1)) && !(display->getSprite(xSpawn,ySpawn) == display->getWaterHandle(2)));

		if(rand() % 10 < 3) {
			enemies.push_back(new Iceberg("Iceberg.png", xSpawn, ySpawn, 50, 10, 2));
		}
		else {
			enemies.push_back(new Pirate("PirateShip.png", xSpawn, ySpawn, 50, 10, 2));
		}

	}

}

void Engine::render() {
	SDL_FillRect(screen, NULL, 0x000000);						// clear the screen
	display->render(screen);

	for(int i = 0; i < objects.size(); i++) {
		int xRender = objects[i]->getX() - display->getXOffset();
		int yRender = objects[i]->getY() - display->getYOffset();			// render the display, characters, objects
		objects[i]->render(xRender, yRender, screen);
	}


	for(int i = 0; i < enemies.size(); i++) {
		if(enemies[i]->isSunk()) {
			int xP = (WIDTH/2) + (enemies[i]->getX() - player->getX());
			int yP = (HEIGHT/2) + (enemies[i]->getY() - player->getY());

			enemies[i]->render(xP, yP, screen);
			enemies[i]->renderAttrib(screen, display, player);
		}
	}

	enemyCount = 0;

	for(int i = 0; i < enemies.size(); i++) {
		if(!enemies[i]->isSunk()) {
			int xP = (WIDTH/2) + (enemies[i]->getX() - player->getX());
			int yP = (HEIGHT/2) + (enemies[i]->getY() - player->getY());

			enemies[i]->render(xP, yP, screen);
			enemies[i]->renderAttrib(screen, display, player);
			enemyCount++;
		}
	}

	int xR, yR;

	for(int i = 0; i < NPCs.size(); i++) {
		xR = (WIDTH/2) + (NPCs[i]->getX() - player->getX());
		yR = (HEIGHT/2) + (NPCs[i]->getY() - player->getY());
		NPCs[i]->render(xR, yR, screen);
	}

	player->render(WIDTH/2, HEIGHT/2, screen);
	player->renderAttrib(screen, display);

	SDL_Flip(screen);
}

////////////////////////// DRIVER /////////////////////////////////////

int main(int argc, char **args) {
	Engine *engine = new Engine;

	engine->runTitle();

	engine->run();

	engine->runClosing();

	engine->close();

	return 1;
}
