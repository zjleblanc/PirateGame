#include "SDL.h"
#include "SDL_mixer.h"

#ifndef AUDIOHANDLER_H
#define AUDIOHANDLER_H

enum track {BOATMUSIC = 1, LANDMUSIC = 2};

class AudioHandler {
public:
	AudioHandler();
	~AudioHandler();
	void initialize();
	void play(track);
	void switchTo(track);
private:
	Mix_Music* boatTrack;
	Mix_Music* islandTrack;
	track CURRENTTRACK;
};

#endif
