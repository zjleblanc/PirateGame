// Handles loading, playing, and switching main audio tracks in the game

#include "SDL.h"
#include "SDL_mixer.h"

#ifndef AUDIOHANDLER_H
#define AUDIOHANDLER_H

enum track {BOATMUSIC = 1, LANDMUSIC = 2, ICEMUSIC = 3, OPENINGMUSIC = 4, CLOSINGMUSIC = 5};

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
	Mix_Music* iceTrack;
	Mix_Music* openingTrack;
	Mix_Music* closingTrack;
	track CURRENTTRACK;
};

#endif
