/*
main menu

1.single player
2.automated scene (for camera view)
3.multiplayer
4.help
5.quit
*/

#include <sstream>
#include <iostream>
#include <GL/glut.h>
#include <string.h>
#include <cstring>

#include "../include/Menu.h"

using namespace std;

void Menu::print_bitmap_string (void* font, char *string)
{
	int x = 5;
	int y = 3;

	int len, i;
	glRasterPos2f(x, y);

	cout << string << endl;

	len = (int) strlen(string);
	for (i = 0; i < len; i++)
	{
		//translates to newline
		glutBitmapCharacter(font, string[i]);
		//if(i == '\n') glTranslatef(0,-0.5,0);
	}

	glutPostRedisplay();
}




/*
3D text menu:
void Menu::print_stroke_string(void* font, char* s){
   if (s && strlen(s)) {
      while (*s) {
		 
		 // if(*s == '\n') glTranslatef(0,-0.5,0);
         glutStrokeCharacter(font, *s);
         s++;
      }
   }
   glutPostRedisplay();
}
*/


//wrapper for drwaing string
//makes print_stroke_string easier to use
void Menu::drawString(string timestring){

		char * drawstring;
		drawstring = new char[timestring.length()+1];
		strcpy(drawstring,timestring.c_str());

		//print_stroke_string(GLUT_STROKE_ROMAN,drawstring);
		print_bitmap_string(GLUT_BITMAP_HELVETICA_18,drawstring);

}

void Menu::printMenu(char level){

	string hmenuString[] = { 

	"F1 : toggle between ortho/perspective mode of viewing" ,
	"F2 : toggle between continuous rotation about y-axis and stop rotation",
	"Up and Down Arrow keys for rotating view about  x-axis",
	"Left and Right Arrow keys for rotating about z-axis",
	"[ and ] for roll",
	"F10: reset view in case your view parameters get out of control",
	"W : Forward",
	"s : Backward",
	"A : strafe Left",
	"D : strafe Right",
	"+ : Zoom in Camera",
	"- : Zoom out Camera", 
	"Right Mouse Button: Menu",
	"F5: Light 1 on/off",
	"F6: Light 2 on/off",
	"F7: Light 3 on/off",
	"F8: Light 4 on/off",
	"F9: All Lights on/off",
	"F11: Ambient Light on/off",
	"1: Pacman cam",
	"2, 3, 4, 5: Ghost1, 2, 3, 4 Cam",
	"6, 7, 8, 9: Light1, 2, 3, 4 Cam",
	"0: Initial Cam",
	"p: pause"

	};

	int i = 0;

	switch(level){


		case '1' :


			for(; i < 24; i++){
					
				glTranslatef(0,-1,0);
				drawString(hmenuString[i]);
		
			}
		
		/*

		MenuString

		<< "F1 : toggle between ortho/perspective mode of viewing" << '\n'
		<< "F2 : toggle between continuous rotation about y-axis and stop rotation" << '\n'
		<< "Up and Down Arrow keys for rotating view about  x-axis" << '\n'
		<< "Left and Right Arrow keys for rotating about z-axis" << '\n'
        << "[ and ] for roll" << '\n'
		<< "F10: reset view in case your view parameters get out of control" << '\n'
		<< "W : Forward" << '\n'
		<< "s : Backward" << '\n'
		<< "A : strafe Left" << '\n'
		<< "D : strafe Right" << '\n'
		<< "+ : Zoom in Camera" << '\n'
		<< "- : Zoom out Camera" << '\n' 
        << "Right Mouse Button: Menu" << '\n'
        << "F5: Light 1 on/off" << '\n'
        << "F6: Light 2 on/off" << '\n'
        << "F7: Light 3 on/off" << '\n'
        << "F8: Light 4 on/off" << '\n'
        << "F9: All Lights on/off" << '\n'
        << "F11: Ambient Light on/off" << '\n'
        << "1: Pacman cam" << '\n'
        << "2, 3, 4, 5: Ghost1, 2, 3, 4 Cam" << '\n'
        << "6, 7, 8, 9: Light1, 2, 3, 4 Cam" << '\n'
        << "0: Initial Cam" << '\n'
        << "p: pause" << '\n'

        << endl;

		*/

		break;


		//level zero
		case '0' :

				glPopMatrix();	
				
					glTranslatef(0,2,0);
					drawString("1.single player");
				 
					glTranslatef(0,-3,0);
					drawString("2.automated scene");
				
					glTranslatef(0,-3,0);
					drawString("3.multiplayer");

					glTranslatef(0,-3,0);
					drawString("4.help");

					glTranslatef(0,-3,0);
					drawString("Esc: quit");

				glPushMatrix();

		break;



		default:

			cout << "wrong choice" << endl;


	}

	// drawstring(Menustring.str());

}

Menu::Menu(){


	MenuString << endl;

}

Menu::~Menu(){}
