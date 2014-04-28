#include "AudioHandler.h"

AudioHandler::AudioHandler() {

}

AudioHandler::~AudioHandler() {
	Mix_FreeMusic(boatTrack);
	Mix_CloseAudio();
}

void AudioHandler::initialize() {
	Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);
	islandTrack = Mix_LoadMUS("Island.wav");
	boatTrack = Mix_LoadMUS("OnABoat.wav");
}

void AudioHandler::play(track toPlay) {
	if(Mix_PlayingMusic() == 0)
		if(toPlay == BOATMUSIC) {
			Mix_PlayMusic(boatTrack, -1);
			CURRENTTRACK = BOATMUSIC;
		} else if(toPlay == LANDMUSIC) {
			Mix_PlayMusic(islandTrack, -1);
			CURRENTTRACK = LANDMUSIC;
		}
}

void AudioHandler::switchTo(track NEWTRACK) {
	if(NEWTRACK != CURRENTTRACK) {
		Mix_HaltMusic();
		if(NEWTRACK == BOATMUSIC) {
			Mix_PlayMusic(boatTrack, -1);
			CURRENTTRACK = BOATMUSIC;
		} else {
			Mix_PlayMusic(islandTrack, -1);
			CURRENTTRACK = LANDMUSIC;
		}
	}
}
