/*
 * audio.cpp
 *
 *  Created on: 2010-08-15
 *      Author: sid
 */




//#pragma comment(lib, "irrKlang.lib") // link with irrKlang.dll

// start the sound engine with default parameters

#ifdef __APPLE__ /* OS X */
#define startLevelSound "starting_level.ogg"
#define pacmanEatingSound "pacman_eating.ogg"
#define pacmanDyingSound "pacman_dying.ogg"
#define gameOverSound "game_end.ogg"
#define frenzySound "FrenzyMusic.ogg"

#include "irrKlang.h"

#elif defined(__linux__) /* LINUX */
#define startLevelSound "data/sound/starting_level.ogg"
#define pacmanEatingSound "data/sound/pacman_eating.ogg"
#define pacmanDyingSound "data/sound/pacman_dying.ogg"
#define gameOverSound "data/sound/game_end.ogg"
#define frenzySound "data/sound/FrenzyMusic.ogg"

#include "../include/irrKlang.h"

#else /* WINDOWS */
#define startLevelSound "data/sound/starting_level.ogg"
#define pacmanEatingSound "data/sound/pacman_eating.ogg"
#define pacmanDyingSound "data/sound/pacman_dying.ogg"
#define gameOverSound "data/sound/game_end.ogg"
#define frenzySound "data/sound/FrenzyMusic.ogg"

#include "../include/irrKlang.h"

#endif


using namespace irrklang;

ISoundEngine* engine = createIrrKlangDevice();
//ISoundEngine* musicSoundEngine = createIrrKlangDevice();
//ISoundEngine* introSoundEngine = createIrrKlangDevice();
//ISoundEngine* soundEffectsEngine = createIrrKlangDevice();
 
void play_intro_audio()
{
	if (!engine)
	{
		return; // error starting up the engine
	}

    engine->play2D(startLevelSound, false);

	return;
}


void play_pacman_eating_audio()
{
	if (!engine)
	{
		return; // error starting up the engine
	}

    engine->play2D(pacmanEatingSound, false);
    
	return;
}

void play_pacman_dying_audio()
{
	if (!engine)
	{
		return; // error starting up the engine
	}

    engine->play2D(pacmanDyingSound, false);

	return;
}

void play_game_ended_audio()
{
	if (!engine)
	{
		return; // error starting up the engine
	}

    engine->play2D(gameOverSound, false);

	return;
}


void play_frenzy_audio()
{
	if (!engine)
	{
		return; // error starting up the engine
	}

    engine->play2D(frenzySound, false);

	return;
}

void stop_pacman_eating_audio()
{
	engine->stopAllSounds(); 
}

void stop_pacman_dying_audio()
{
	engine->stopAllSounds(); 
}

void stop_game_ended_audio()
{
	engine->stopAllSounds(); 
}

void stop_frenzy_audio()
{
	engine->stopAllSounds(); 
}