#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <string>


const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP = 32;


const int FRAMES_PER_SECOND = 30;
const int CRAB_WIDTH = 100;
const int CRAB_HEIGHT = 100;

SDL_Surface *crab = NULL;
SDL_Surface *screen = NULL;


SDL_Event event;

class Crab{
	public:
		Crab();
		void handle_input();
		void move();
		void show();

	private:
		int x, y;
		int xVel, yVel;
};

class Timer{
    public:
	    Timer();
	
	    void start();
	    void stop();
	    void pause();
	    void unpause();

	    int get_ticks();
 
	    bool is_started();
	    bool is_paused();

     private:
	    int startTicks;
            int pausedTicks;

            bool paused;
            bool started;
};

SDL_Surface *load_image( std::string filename ){
   SDL_Surface* loadedImage = NULL;

    SDL_Surface* optimizedImage = NULL;

    loadedImage = IMG_Load( filename.c_str() );

    if( loadedImage != NULL ){
        optimizedImage = SDL_DisplayFormat( loadedImage );

        SDL_FreeSurface( loadedImage );

        if( optimizedImage != NULL ){
            SDL_SetColorKey( optimizedImage, SDL_SRCCOLORKEY, SDL_MapRGB( optimizedImage->format, 0, 0xFF, 0xFF ) );
        }
    }

    return optimizedImage;
}

void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL ){

    SDL_Rect offset;

    offset.x = x;
    offset.y = y;

    SDL_BlitSurface( source, clip, destination, &offset );
}

bool init(){
    if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 ){
        return false;
    }

    screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE );

    if( screen == NULL ){
        return false;
    }

    SDL_WM_SetCaption( "Walking Crab", NULL );

    return true;
}

bool load_files(){
    crab = load_image( "crab.png" );
    if( crab == NULL ){
	return false;
    }
	return true;
   
}

void clean_up(){
    SDL_FreeSurface(crab);
    SDL_FreeSurface(screen);
    SDL_Quit();
}

Crab::Crab(){
    x = 0;
    y = 300;
    xVel = 0;
    yVel = 0;
}

void Crab::handle_input(){
    if( event.type == SDL_KEYDOWN ){
        switch( event.key.keysym.sym ){
            case SDLK_LEFT: xVel -= CRAB_WIDTH / 3; break;
            case SDLK_RIGHT: xVel += CRAB_WIDTH / 3; break;
	    case SDLK_UP: yVel -= CRAB_HEIGHT / 3; break;
	    case SDLK_DOWN: yVel += CRAB_HEIGHT / 3; break;        
	}
    } else if( event.type == SDL_KEYUP ){
        switch( event.key.keysym.sym ){
            case SDLK_LEFT: xVel += CRAB_WIDTH / 3; break;
            case SDLK_RIGHT: xVel -= CRAB_WIDTH / 3; break;
	    case SDLK_UP: yVel += CRAB_HEIGHT / 3; break;
	    case SDLK_DOWN: yVel -= CRAB_HEIGHT / 3; break;
        }
    }
}

void Crab::move(){
    x += xVel;
    y += yVel;

    if((x < 0) || (x + CRAB_WIDTH > SCREEN_WIDTH)){
        x -= xVel;
    }

    if((y < 0) || (y + CRAB_HEIGHT > SCREEN_HEIGHT)){
	y -= yVel;
    }
}		


void Crab::show(){
	apply_surface(x, y, crab, screen);
}


Timer::Timer(){
	startTicks = 0;
	pausedTicks = 0;
	started = false;
	paused = false;
}

void Timer::stop(){
	started = false;
	paused = false;
}

void Timer::start(){
	started = true;
	paused = false;
	startTicks= SDL_GetTicks();
}

void Timer::pause(){
	if ((started == true) && (paused == false)){
		paused = true;
		pausedTicks = SDL_GetTicks() - startTicks;
	}
}

void Timer::unpause(){
	if (paused == true){
		paused = false;
		startTicks = SDL_GetTicks() - pausedTicks;
		pausedTicks = 0;
	}
}

int Timer::get_ticks(){
	if(started==true){
		if(paused == true){
			return pausedTicks;
		} else{
			return SDL_GetTicks() - startTicks;
		}
	}
	return 0;
}

bool Timer::is_started(){
	return started;
}

bool Timer::is_paused(){
	return paused;
}



int main (int argc, char* args[]){
	
	bool quit = false;
	
	Crab coolCrab;

	Timer fps;


	if (init() == false){
		return 1;
	}

	if (load_files() == false){
		return 1;
	}

	while (quit == false){
		fps.start();
		while (SDL_PollEvent(&event)){
			coolCrab.handle_input();
			
			if (event.type == SDL_QUIT){
				quit = true;
			}
		}

			coolCrab.move();

			SDL_FillRect ( screen, &screen->clip_rect, SDL_MapRGB(screen->format, 0xFF, 0xFF, 0xFF));

			coolCrab.show();
			
			if(SDL_Flip(screen) == -1){
				return 1;
			}
			
			if(fps.get_ticks() < 1000 / FRAMES_PER_SECOND){
				SDL_Delay ((1000/FRAMES_PER_SECOND) - fps.get_ticks());
			}	
	}

	clean_up();
	return 0;
}
	
	
			
			
