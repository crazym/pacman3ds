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

ISoundEngine* musicSoundEngine = createIrrKlangDevice();
ISoundEngine* soundEffectsEngine = createIrrKlangDevice();
 
void play_intro_audio(){

	if (!musicSoundEngine)
	{
		return; // error starting up the engine
	}

    musicSoundEngine->play2D(startLevelSound, false);

	return;
}


void play_pacman_eating_audio(){

	if (!soundEffectsEngine)
	{
		return; // error starting up the engine
	}

    soundEffectsEngine->play2D(pacmanEatingSound, false);
    
	return;
}

void play_pacman_dying_audio(){

	if (!soundEffectsEngine)
	{
		return; // error starting up the engine
	}

    soundEffectsEngine->play2D(pacmanDyingSound, false);

	return;
}

void play_game_ended_audio(){

	if (!soundEffectsEngine)
	{
		return; // error starting up the engine
	}

    soundEffectsEngine->play2D(gameOverSound, false);

	return;
}


void play_frenzy_audio(){

	if (!musicSoundEngine)
	{
		return; // error starting up the engine
	}

    musicSoundEngine->play2D(frenzySound, false);

	return;
}

void stop_intro_audio(){

	musicSoundEngine->stopAllSounds(); 
}

void stop_pacman_eating_audio(){

	soundEffectsEngine->stopAllSounds(); 
}

void stop_pacman_dying_audio(){

	soundEffectsEngine->stopAllSounds(); 
}

void stop_game_ended_audio(){

	soundEffectsEngine->stopAllSounds(); 
}

void stop_frenzy_audio(){

	musicSoundEngine->stopAllSounds(); 
}