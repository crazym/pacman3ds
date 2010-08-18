/*
 * audio.cpp
 *
 *  Created on: 2010-08-15
 *      Author: sid
 */




//#pragma comment(lib, "irrKlang.lib") // link with irrKlang.dll

// start the sound engine with default parameters

#include "../include/irrKlang.h"

using namespace irrklang;

ISoundEngine* intro_audio = createIrrKlangDevice();
ISoundEngine* game_ended_audio = createIrrKlangDevice();
ISoundEngine* pacman_eating_audio = createIrrKlangDevice();
ISoundEngine* pacman_dying_audio = createIrrKlangDevice();
ISoundEngine* frenzy_audio = createIrrKlangDevice();

 
void play_intro_audio(){

	if (!intro_audio)
	{
		return; // error starting up the engine
	}

	intro_audio->play2D("data/sound/starting_level.ogg", false);

	return;
}


void play_pacman_eating_audio(){

	if (!pacman_eating_audio)
	{
		return; // error starting up the engine
	}

	pacman_eating_audio->play2D("data/sound/pacman_eating.ogg", false);

	return;
}

void play_pacman_dying_audio(){

	if (!pacman_dying_audio)
	{
		return; // error starting up the engine
	}

	pacman_dying_audio->play2D("data/sound/pacman_dying.ogg", false);

	return;
}

void play_game_ended_audio(){

	if (!game_ended_audio)
	{
		return; // error starting up the engine
	}

	game_ended_audio->play2D("data/sound/game_end.ogg", false);

	return;
}


void play_frenzy_audio(){

	if (!frenzy_audio)
	{
		return; // error starting up the engine
	}

	frenzy_audio->play2D("data/sound/death_metal_song.ogg", false);

	return;
}

void stop_intro_audio(){

	intro_audio->stopAllSounds(); 
}

void stop_pacman_eating_audio(){

	pacman_eating_audio->stopAllSounds(); 
}

void stop_pacman_dying_audio(){

	pacman_dying_audio->stopAllSounds(); 
}

void stop_game_ended_audio(){

	game_ended_audio->stopAllSounds(); 
}

void stop_frenzy_audio(){

	frenzy_audio->stopAllSounds(); 
}
