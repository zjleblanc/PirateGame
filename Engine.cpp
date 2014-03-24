#include "SDL.h"
#include "SDL_image.h"
#include "Keyboard.h"
#include "TextWriter.h"
#include "Player.h"
#include "Display.h"
#include "SDL_ttf.h"
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;

////////////////////////// GLOBALS //////////////////////////////////////////////

SDL_Event event;
SDL_Surface* screen = NULL;

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
	const int WIDTH, HEIGHT, BPP;
	Keyboard *keyboard;
	Display *display;
	TextWriter *textWriter;
	Player *player;
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
	textWriter = new TextWriter(30);
	player = new Player();
	player->setLocation(WIDTH, HEIGHT);
}

Engine::~Engine() {
	delete keyboard;
	delete display;
	delete textWriter;
	delete player;
}

bool Engine::start() {

	// Open SDL

	if(SDL_Init(SDL_INIT_EVERYTHING) == -1) {
		return false;
	}

	// Setup Window

	screen = SDL_SetVideoMode(WIDTH, HEIGHT, BPP, SDL_DOUBLEBUF);
	if(!screen) {
		return false;
	}
	SDL_WM_SetCaption("Game", NULL);

	return true;
}

void Engine::close() {
	SDL_Quit();
	delete this;
}

void Engine::run() {
	bool quit = false;
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
		}

		render();
		frames++;

		if(timer - now >= 1000) {
			stringstream fps;
			fps << "Game   |   " << frames << " FPS";
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
	player->update(display);
	int x = player->getX();
	int y = player->getY();
	display->setOffsets(x,y);
}

void Engine::render() {
	SDL_FillRect(screen, NULL, 0x000000);
	display->render(screen);
	player->render(WIDTH/2, HEIGHT/2, screen);
	textWriter->write(display->getCurrentTile(), 50, 50, screen);
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
