/*
 * audio.cpp
 *
 *  Created on: 2010-08-15
 *      Author: sid
 */




//#pragma comment(lib, "irrKlang.lib") // link with irrKlang.dll

// start the sound engine with default parameters

#include "irrKlang.h"

#ifdef __APPLE__ /* OS X */
#define startLevelSound "starting_level.ogg"
#define pacmanEatingSound "pacman_eating.ogg"
#define pacmanDyingSound "pacman_dying.ogg"
#define gameOverSound "game_end.ogg"
#define frenzySound "FrenzyMusic.ogg"
#elif defined(__linux__) /* LINUX */
#define startLevelSound "data/sound/starting_level.ogg"
#define pacmanEatingSound "data/sound/pacman_eating.ogg"
#define pacmanDyingSound "data/sound/pacman_dying.ogg"
#define gameOverSound "data/sound/game_end.ogg"
#define frenzySound "data/sound/FrenzyMusic.ogg"
#else /* WINDOWS */
#define startLevelSound "data/sound/starting_level.ogg"
#define pacmanEatingSound "data/sound/pacman_eating.ogg"
#define pacmanDyingSound "data/sound/pacman_dying.ogg"
#define gameOverSound "data/sound/game_end.ogg"
#define frenzySound "data/sound/FrenzyMusic.ogg"
#endif


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

	intro_audio->play2D(startLevelSound, false);

	return;
}


void play_pacman_eating_audio(){

	if (!pacman_eating_audio)
	{
		return; // error starting up the engine
	}

	pacman_eating_audio->play2D(pacmanEatingSound, false);

	return;
}

void play_pacman_dying_audio(){

	if (!pacman_dying_audio)
	{
		return; // error starting up the engine
	}

	pacman_dying_audio->play2D(pacmanDyingSound, false);

	return;
}

void play_game_ended_audio(){

	if (!game_ended_audio)
	{
		return; // error starting up the engine
	}

	game_ended_audio->play2D(gameOverSound, false);

	return;
}


void play_frenzy_audio(){

	if (!frenzy_audio)
	{
		return; // error starting up the engine
	}

	frenzy_audio->play2D(frenzySound, false);

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