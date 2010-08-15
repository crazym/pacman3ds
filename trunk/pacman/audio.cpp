/*
 * audio.cpp
 *
 *  Created on: 2010-08-15
 *      Author: sid
 */

#include "klang/conio.h"
#include "klang/irrKlang.h"
#include <iostream>

using namespace irrklang;
// start the sound engine with default parameters
	ISoundEngine* engine = createIrrKlangDevice();

void init_audio(){


	if (!engine)
	{
		printf("Could not startup engine\n");
		return; // error starting up the engine
	}

	// To play a sound, we only to call play2D(). The second parameter
	// tells the engine to play it looped.

	// play some sound stream, looped
	engine->play2D("data/sound/getout.ogg", true);

	// In a loop, wait until user presses 'q' to exit or another key to
	// play another sound.

	printf("\nHello World!\n");

	do
	{
		printf("Press any key to play some sound, press 'q' to quit.\n");

		// play a single sound
		engine->play2D("/data/sound/explosion.wav");
	}
	while(getch() != 'q');

	// After we are finished, we have to delete the irrKlang Device created earlier
	// with createIrrKlangDevice(). Use ::drop() to do that. In irrKlang, you should
	// delete all objects you created with a method or function that starts with 'create'.
	// (an exception is the play2D()- or play3D()-method, see the documentation or the
	// next example for an explanation)
	// The object is deleted simply by calling ->drop().

	engine->drop(); // delete engine
	return;
}
