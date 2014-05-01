#include "AudioHandler.h"

// CONSTRUCTOR

AudioHandler::AudioHandler() {

}

// DECONSTRUCTOR

AudioHandler::~AudioHandler() {
	Mix_FreeMusic(boatTrack);
	Mix_CloseAudio();
}

// PUBLIC METHODS

void AudioHandler::initialize() {
	Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);			// open Audio, load files (called once)
	islandTrack = Mix_LoadMUS("Island.wav");
	boatTrack = Mix_LoadMUS("Opening.wav");
	iceTrack = Mix_LoadMUS("Ice.wav");
	openingTrack = Mix_LoadMUS("Opening.wav");
	closingTrack = Mix_LoadMUS("EndTheme.wav");
}

void AudioHandler::play(track toPlay) {							// plays given track, sets CURRENTTRACK to this track
	if(Mix_PlayingMusic() == 0)
		if(toPlay == BOATMUSIC) {
			Mix_PlayMusic(openingTrack, -1);
			CURRENTTRACK = BOATMUSIC;
		} 
		else if(toPlay == LANDMUSIC) {
			Mix_PlayMusic(islandTrack, -1);
			CURRENTTRACK = LANDMUSIC;
		} 
		else if(toPlay == ICEMUSIC) {
			Mix_PlayMusic(islandTrack, -1);
			CURRENTTRACK = ICEMUSIC;
		}
		else if(toPlay == OPENINGMUSIC) {
			Mix_PlayMusic(openingTrack, -1);
			CURRENTTRACK = OPENINGMUSIC;
		} 
		else if(toPlay == CLOSINGMUSIC) {
			Mix_PlayMusic(closingTrack, -1);
			CURRENTTRACK = CLOSINGMUSIC;
		}
}

void AudioHandler::switchTo(track NEWTRACK) {					// switches song in the event that it is not the song currently playing
	if(NEWTRACK != CURRENTTRACK) {
		Mix_HaltMusic();
		if(NEWTRACK == BOATMUSIC) {
			Mix_PlayMusic(openingTrack, -1);
			CURRENTTRACK = BOATMUSIC;
		} 
		else if(NEWTRACK == LANDMUSIC) {
			Mix_PlayMusic(islandTrack, -1);
			CURRENTTRACK = LANDMUSIC;
		}
		else if(NEWTRACK == ICEMUSIC) {
			Mix_PlayMusic(iceTrack, -1);
			CURRENTTRACK = ICEMUSIC;
		}
		else if(NEWTRACK == OPENINGMUSIC) {
			Mix_PlayMusic(openingTrack, -1);
			CURRENTTRACK = OPENINGMUSIC;
		}
		else if(NEWTRACK == CLOSINGMUSIC) {
			Mix_PlayMusic(closingTrack, -1);
			CURRENTTRACK = CLOSINGMUSIC;
		}
	}
}
