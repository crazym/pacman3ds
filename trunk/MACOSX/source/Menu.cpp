/*
main menu

1.single player
2.automated scene (for camera view)
3.multiplayer
4.help
5.quit
*/

#ifdef __APPLE__ /* OS X */
#include <cstdlib>
#include <GLUT/glut.h>

#include "Menu.h"
#include "Common.h"

#elif defined(__linux__) /* LINUX */
#include <stdlib.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include "../include/Menu.h"
#include "../include/Common.h"

#else /* WINDOWS */
#include <stdlib.h>
#include <windows.h>
#include <GL/glut.h>
#include <ctime>

#include "../include/Menu.h"
#include "../include/Common.h"

#endif

#include <sstream>
#include <iostream>
#include <string.h>
#include <cstring>



using namespace std;


void Menu::printMenu(char level){

	string hmenuString[] = { 

         "F1 : toggle between ortho/perspective mode of viewing",
         "F2 : toggle between continuous rotation about y-axis and stop rotation",
         "Directional Arrows: move Pacman",
         "F10: reset view in case your view parameters get out of control",
         "W : Forward",
         "S : Backward",
         "A : Strafe Left",
         "D : Strafe Right",
         "= : Zoom In with Motion",
         "- : Zoom Out with Motion",
         "+ : Zoom In with Fovy",
         "_ : Zoom Out with Fovy", 
         "[ and ] for roll",
         ", and . for orbit",
         "F: Toggle Fullscreen",
         "I: Pitch Up",
         "K: Pitch Down",
         "J: Yaw Left",
         "L: Yaw Right",
         "R: Reset View",
         "M: Enables Menu",
         "Right Mouse Button: Menu",
         "F5: Light 1 on/off",
         "F6: Light 2 on/off",
         "F7: Light 3 on/off",
         "F8: Light 4 on/off",
         "F9: All Lights on/off",
         "F11: Ambient Light on/off",
         "F12: Turn OFF all the Lamps",
         "1: Pacman cam",
         "2, 3, 4, 5: Ghost1, Ghost2, Ghost3, Ghost4 Cam",
         "6, 7, 8, 9: Light1, Light2, Light3, Light4 Cam",
         "0: Initial Cam",
         "P: pause",
         "B: Pacman Outfit Toggling",
         "C: Toggle Textures",
         "X: Pellet Texture Toggling",
         "Z: Shading Toggling",
         "H: Help"
	};

	int i = 0;

	switch(level){


		//level zero
		case '0' :

				glPopMatrix();	
				
					glTranslatef(0,2,0);
					drawString("1.single player");

					glTranslatef(0,-3,0);
					drawString("Esc: quit");

				glPushMatrix();

		break;

		
		case '1' :


			for(; i < 24; i++){
				glPushMatrix();
				glTranslatef(0,10-2*i,0);
				drawString(hmenuString[i]);
				glPopMatrix();
			}
			
		break;

		default:

			cout << "wrong choice" << endl;
			break;


	}

	// drawstring(Menustring.str());

}

Menu::Menu(){


	MenuString << endl;

}

Menu::~Menu(){}
