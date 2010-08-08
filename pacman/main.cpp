/*
 *  main.cpp
 * 
 *
 *  Created by carlos, bronson, sid, andrew, allan on 10-07-16.
 *  Copyright 2010 Concordia University. All rights reserved.
 *	Carlos Pinto (Team Leader)
 *	ID: 9343911
 *
 *	Bronson Zgeb
 *	ID: 9402268
 *
 *	Andrew Wolczak
 *	ID: 9095543
 *
 *	Allan Tran
 *	ID: 9099824
 *
 *	Siddhartha Kattoju
 *	ID: 9209905
 */

/*
 *  References:
 *      OpenGl Superbible, fourth edition, Richard S. Wright, Jr et al, Addison-Wesley
 *      http://www.opengl.org/documentation/red_book/
 *      http://users.encs.concordia.ca/~c371_1/skeleton.cpp
 *      http://ozark.hendrix.edu/~burch/cs/490/sched/feb8/
 *      http://www.codersger.de/mags/cscene/CS6/CS6-06.html
 *      http://users.encs.concordia.ca/~c371_1/skeleton.cpp
 *      http://www.nullterminator.net/gltexture.html
 */


/*
 *  Texture Sources: 
 *              Various: OpenGl Superbible, fourth edition, Richard S. Wright, Jr et al, Addison-Wesley
 *              Pumpkin: http://www.filterforge.com/filters/7893.html
 *              Floor Tile: Autodesk 3DsMax
 *              Paper: http://www.cgtextures.com/
 */

// This program uses sampleprogram.cpp as a template
// This Program Draws a scene in a Pacman game.

// Function Keys support:
//   1. F1 : toggle between ortho/perspective mode of viewing.
//   2. F2 : toggle between continuous rotation about y-axis and stop rotation
//   3. Up and Down Arrow keys for rotating view about  x-axis
//	 4. Left and Right Arrow keys for rotating about z-axis
//   5. [ and ] for roll
//	 6.	F10: reset view in case your view parameters get out of control.
//	 7. W : Forward
//   8. S : Backward
//   9. A : Strafe Left
//   10. D : Strafe Right
//   11. , : Lower Camera
//   12. . : Raise Camera
//   13. F5: Light 1 on/off
//   14. F6: Light 2 on/off
//   15. F7: Light 3 on/off
//   16. F8: Light 4 on/off
//   17. F9: All Lights on/off
//   18. F11: Ambient Light on/off
//   19. 1: Pacman Cam
//   20. 2-3-4-5: Ghost1-2-3-4 Cam
//   21. 6-7-8-9: Light1-2-3-4 Cam
//   22. 0: Initial Cam


// Link with: opengl32.lib, glu32.lib, glut32.lib.
// glut includes links to the other two libraries.
#ifdef __APPLE__ /* OS X */
#include <cstdlib>
#include <GLUT/glut.h>
#elif defined(__linux__) /* LINUX */
#include <cstdlib>
#include <GL/glut.h>
#else /* WINDOWS */
#include <stdlib.h>
#include <windows.h>
#include <GL/glut.h>
#endif

#include <cmath>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>

#include "Ghost.h"
#include "Pacman.h"
#include "Material.h"
#include "Common.h"

#include "Map.h"
#include "Tile.h"
#include "Lamp.h"
#include "Timer.h"
#include "stdio.h"
#include "string.h"

using namespace std;

void ProcessMenu(GLint value);
void resetViewParameters();
void functionKeys (int key, int x, int y);
void graphicKeys (unsigned char key, int x, int y);


/**************************
 Game Objects
 **************************/
static Pacman *pacman;
static Ghost *ghost1;
static Ghost *ghost2;
static Ghost *ghost3;
static Ghost *ghost4;
static Map *map1;
static Lamp *lamp1;
static Lamp *lamp2;
static Lamp *lamp3;
static Lamp *lamp4;
static Timer *timer1;

static GLchar map[483] = {										 
    //23 Rows
    //21 Cols
    'W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W',	 // Current map
    'W','X','Z','Z','Z','Z','Z','Z','Z','Z','W','Z','Z','Z','Z','Z','Z','Z','Z','X','W',
    'W','Z','W','W','W','Z','W','W','W','Z','W','Z','W','W','W','Z','W','W','W','Z','W',
    'W','Z','W','W','W','Z','W','W','W','Z','W','Z','W','W','W','Z','W','W','W','Z','W',
    'W','Z','Z','Z','Z','Z','Z','Z','Z','Z','W','Z','Z','Z','Z','Z','Z','Z','Z','Z','W',
    'W','Z','W','W','W','Z','W','Z','W','W','W','W','W','Z','W','Z','W','W','W','Z','W',
    'W','Z','Z','Z','Z','Z','W','Z','Z','Z','W','Z','Z','Z','W','Z','Z','Z','Z','Z','W',
    'W','W','W','W','W','Z','W','W','W','Z','W','Z','W','W','W','Z','W','W','W','W','W',
    'Y','Y','Y','Y','W','Z','W','Z','Z','Z','Z','Z','Z','Z','W','Z','W','Y','Y','Y','Y',
    'W','W','W','W','W','Z','W','Z','W','W','Y','W','W','Z','W','Z','W','W','W','W','W',
    'Y','Y','Y','Y','Y','X','Z','Z','W','Y','Y','Y','W','Z','Z','X','Y','Y','Y','Y','Y',
    'W','W','W','W','W','Z','W','Z','W','Y','Y','Y','W','Z','W','Z','W','W','W','W','W',
    'Y','Y','Y','Y','W','Z','W','Z','W','W','W','W','W','Z','W','Z','W','Y','Y','Y','Y',
    'Y','Y','Y','Y','W','Z','W','Z','Z','Z','Z','Z','Z','Z','W','Z','W','Y','Y','Y','Y',
    'W','W','W','W','W','Z','W','Z','W','W','W','W','W','Z','W','Z','W','W','W','W','W',
    'W','Z','Z','Z','Z','Z','Z','Z','Z','Z','W','Z','Z','Z','Z','Z','Z','Z','Z','Z','W',
    'W','Z','W','W','W','Z','W','W','W','Z','W','Z','W','W','W','Z','W','W','W','Z','W',
    'W','Z','Z','Z','W','Z','Z','Z','Z','Z','Z','Z','Z','Z','Z','Z','W','Z','Z','Z','W',
    'W','W','W','Z','W','Z','W','Z','W','W','W','W','W','Z','W','Z','W','Z','W','W','W',
    'W','Z','Z','Z','Z','Z','W','Z','Z','Z','W','Z','Z','Z','W','Z','Z','Z','Z','Z','W',
    'W','Z','W','W','W','W','W','W','W','Z','W','Z','W','W','W','W','W','W','W','Z','W',
    'W','X','Z','Z','Z','Z','Z','Z','Z','Z','Z','Z','Z','Z','Z','Z','Z','Z','Z','X','W',
    'W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W'
    
};

// Initial size of graphics window on your screen.
const GLint WIDTH  = 800; // in pixels
const GLint HEIGHT = 600; //

// increment for idle function rotation and zoom
const GLdouble RotSTEP = 0.2;
const GLdouble mvSTEP = 5.0;
const GLdouble ALL_ROUND = 360;
const GLdouble ZoomSTEP = 0.9;
const GLdouble zoomFactor = 1.03;

// Current size of window (will change when you resize window)
GLint width  = WIDTH;
GLint height = HEIGHT;

// Mouse positions, normalized to [0,1].
GLdouble xMouse = 0.5;
GLdouble yMouse = 0.5;

// Bounds of viewing frustum, maintain uniform scaling.
GLdouble viewWindowLeft =  -40;
GLdouble viewWindowRight  = 40;
GLdouble viewWindowBottom =  -40;
GLdouble viewWindowTop  = 40;
GLdouble nearPlane =  1.5;
GLdouble farPlane  = 120;

// Viewing angle.
GLdouble fovy = 60;

/* Rotation */
GLdouble yaw = 0;                                  // rotation angle about Y axis.
GLdouble pitch = 0;                                   // rotation angle about X axis.
GLdouble roll = 0;

/* misc */
static GLdouble halfway = - (farPlane + nearPlane) / 2;	   // half way between near and far planes
static GLint ambient_light = 0;
static GLint textures_enabled = 1;
static GLint color_material_enabled = 1;
static GLint pacman_outfit = 0;

static GLint texturePellets = 1;
static GLint texturePPellets = 1;

/* Camera */
/* Set initial values */
const GLdouble initial_eye[3] = {10.0, 30.0, 35.0};
const GLdouble initial_center[3] = {10.0, 2.0, 11.0};

GLdouble fw_rw=0;
GLdouble up_dn=0;
GLdouble lt_rt=0;

GLdouble eye_x=10.0;
GLdouble eye_y=30.0;
GLdouble eye_z=35.0;

GLdouble center_x=10.0;
GLdouble center_y=2.0;
GLdouble center_z=11.0;

GLdouble up_x=0.0;
GLdouble up_y=1.0;
GLdouble up_z=0.0;

GLboolean idleEnable = 0;	// flags that set continuous rotation on/off
GLboolean projType = 1;      // flag for proj type; ortho = 0, perspective = 1
GLboolean isWireFrame =0;    // flag for setting wire frame mode

void resetViewParameters()
{
	// resets 3D synthetic camera parameters to default values

	viewWindowLeft =  -60;
	viewWindowRight  = 60;
	viewWindowBottom =  -60;
	viewWindowTop  = 60;
    
	nearPlane =  60;
	farPlane  = 120;
    
	fovy = 60;
	yaw = 0.0;
	pitch = 0.0;
	roll = 0.0;
    
	projType = 1;
	idleEnable = 0;
    
    fw_rw=0;
    up_dn=0;
    lt_rt=0;
}


void setView()
{
	// Must set it up in Projection Matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
    
	if(projType) {
        gluPerspective(fovy, (GLfloat) 1.0, nearPlane, farPlane);
    }
	else {
        glOrtho
		(
         viewWindowLeft,
         viewWindowRight,
         viewWindowBottom,
         viewWindowTop,
         nearPlane,
         farPlane
         );
    }
		
}

void zoom(unsigned char direction)
{
   // for zoom in reduces viewWindow size and for zoom out increases it.

	if (direction == '+') {
			viewWindowLeft += ZoomSTEP; viewWindowRight -= ZoomSTEP;
			viewWindowBottom += ZoomSTEP; viewWindowTop -= ZoomSTEP;
			fovy = fovy / zoomFactor;
		}
		else if (direction == '-') {
			viewWindowLeft -= ZoomSTEP; viewWindowRight += ZoomSTEP;
			viewWindowBottom -= ZoomSTEP; viewWindowTop += ZoomSTEP;
			fovy = fovy * zoomFactor;
		}

}

void drawAxes(){

	glPushMatrix();
		glBegin(GL_LINES);
		// X axis
		glColor3f(1, 0, 0);
		glVertex3f(0, 0, 0);
		glVertex3f(10, 0, 0);
		// Y axis
		glColor3f(0, 1, 0);
		glVertex3f(0, 0, 0);
		glVertex3f(0, 10, 0);
		// Z axis
		glColor3f(0, 0, 1);
		glVertex3f(0, 0, 0);
		glVertex3f(0, 0, 10);
		glEnd();
    glPopMatrix();
}

void numbertest(){

	glPushMatrix();
	    glColor3f(1,1,1);
	    glLineWidth(2.0);
	    glTranslatef(1,1,0);
			for(char n=0; n<10; n++){

				glTranslatef(1.5,0,0);
				number(n);
			}
    glPopMatrix();
}

// This function is called to display the scene.
void display ()
{
    GLfloat spotlightPosition1[] = { 0.0f, 4.0f, 0.0f, 1.0f };
    GLfloat spotlightPosition2[] = { 20.0f, 4.0f, 0.0f, 1.0f };
    GLfloat spotlightPosition3[] = { 0.0f, 4.0f, 22.0f, 1.0f };
    GLfloat spotlightPosition4[] = { 20.0f, 4.0f, 22.0f, 1.0f };
    
    /* The projection of the spotlight onto the x-z plane is 4.
     * In order to obtain a 45 degree projection between the x-plane and the
     * z-plane the value must be 2sqrt(2) = ~2.82.  The value was calculated using
     * the pythagorean theorem.*/
    
    GLfloat spotlightDirection1[] = { 2.82f, -4.0f, 2.82f, 1.0f };
    GLfloat spotlightDirection2[] = { -2.82f, -4.0f, 2.82f, 1.0f };
    GLfloat spotlightDirection3[] = { 2.82f, -4.0f, -2.82f, 1.0f };
    GLfloat spotlightDirection4[] = { -2.82f, -4.0f, -2.82f, 1.0f };
    
    GLfloat eye_position[3] = { eye_x+lt_rt, eye_y+up_dn, eye_z+fw_rw };
    GLfloat center_position[3] = { center_x+lt_rt, center_y+up_dn, center_z+fw_rw };
    
    glClearColor(0,0,0,1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
    // set modelling mode
	glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    gluLookAt(eye_position[0], eye_position[1], eye_position[2], 
              center_position[0], center_position[1], center_position[2], 
              0.0, 1.0, 0.0);
    
    glTranslatef(10.5, 0.0, 11.5);
    glRotatef(pitch, up_y*(center_z - eye_z) - up_z*(center_y - eye_y), 
              up_z*(center_x - eye_x) - up_x*(center_z - eye_z), 
              up_x*(center_y - eye_y) - up_y*(center_x - eye_x));
	glRotatef(yaw, up_x, up_y, up_z);
	//glRotatef(roll, center_x - eye_x, center_y - eye_y, center_z - eye_z);
    glRotatef(roll, 0.0, 0.0, 10.5);
    glTranslatef(-10.5, 0.0, -11.5);
    
    lamp1->setLightPosition(spotlightPosition1, spotlightDirection1);
    lamp2->setLightPosition(spotlightPosition2, spotlightDirection2);
    lamp3->setLightPosition(spotlightPosition3, spotlightDirection3);
    lamp4->setLightPosition(spotlightPosition4, spotlightDirection4);                    
        
	// Draw model axes in centre of room.
    //drawAxes();
    
    if(isWireFrame) glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    else glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);

    if(color_material_enabled) glEnable(GL_COLOR_MATERIAL);
    else glDisable(GL_COLOR_MATERIAL);

    if (textures_enabled) glEnable(GL_TEXTURE_2D);
    else glDisable(GL_TEXTURE_2D);


    pacman->draw(pacman_outfit);
    map1->draw(texturePellets, texturePPellets);
    
    lamp1->draw();
    lamp2->draw();
    lamp3->draw();
    lamp4->draw();    
    ghost1->draw();
    ghost2->draw();
    ghost3->draw();
    ghost4->draw();

    //glPopMatrix();
		glColor3f(1,1,1);
		glTranslatef(6,4,0);
		glScalef(0.01,0.01,0.01);
		timer1->drawTimer();
	//glPushMatrix();

    // now swap buffer
    glutSwapBuffers();
   
    //gluDeleteQuadric(quadric);
}



// This function is called when there is nothing else to do.
void idle ()
{

   if (idleEnable)
   {	
       yaw += RotSTEP;
       if (yaw > ALL_ROUND){
           yaw -= ALL_ROUND;           
       }
       // Display normalized coordinates in title bar.
       //const int BUFSIZE = 200;
       //static char buffer[BUFSIZE];
       //ostringstream s(buffer, BUFSIZE);
       ostringstream s;
       s    << resetiosflags(ios::floatfield) 
            << setiosflags(ios::fixed) 
            << setprecision(3) 
            << "Mouse at (" 
            << xMouse << ", " 
            << yMouse 
            << setprecision(0) 
            << ").  Alpha=" 
            << setw(3) 
            << yaw 
            << ".  Beta=" 
            << setw(3) 
            << pitch 
            << setprecision(2)
            << ". Distance=" 
            << halfway 
            << "." 
            << ends;

       string tmp = s.str();

       char* thing;
       thing = new char[tmp.length()+1];
       strcpy(thing,tmp.c_str());

       glutSetWindowTitle(thing);

       glutPostRedisplay();
   }
}

//capture mouse movement
void mouseMovement (int mx, int my)
{
   // Normalize mouse coordinates.
   xMouse = double(mx) / double(width);
   yMouse = 1 - double(my) / double(height);

   // Redisplay image.
   glutPostRedisplay();
}

// Respond to window resizing, preserving proportions.
// Parameters give new window size in pixels.
void reshapeMainWindow (int newWidth, int newHeight)
{
    GLfloat eye_position[3] = { eye_x+lt_rt, eye_y+up_dn, eye_z+fw_rw };
    GLfloat center_position[3] = { center_x+lt_rt, center_y+up_dn, center_z+fw_rw };

	width = newWidth;
	height = newHeight;
	glViewport(0, 0, width, height);
    setView();
	glMatrixMode (GL_MODELVIEW);
    gluLookAt(eye_position[0], eye_position[1], eye_position[2], 
              center_position[0], center_position[1], center_position[2], 
              up_x, up_y, up_z);
}

// Display Help.
void help()
{
   cout << "F1 : toggle between ortho/perspective mode of viewing" << endl
		<< "F2 : toggle between continuous rotation about y-axis and stop rotation" << endl
		<< "Up and Down Arrow keys for rotating view about  x-axis" << endl
		<< "Left and Right Arrow keys for rotating about z-axis" << endl
        << "[ and ] for roll" << endl
		<< "F10: reset view in case your view parameters get out of control" << endl
		<< "W : Forward" << endl
		<< "S : Backward" << endl
		<< "A : Strafe Left" << endl
		<< "D : Strafe Right" << endl
		<< ", : Lower Camera" << endl
		<< ". : Raise Camera" << endl 
        << "Right Mouse Button: Menu" << endl
        << "F5: Light 1 on/off" << endl
        << "F6: Light 2 on/off" << endl
        << "F7: Light 3 on/off" << endl
        << "F8: Light 4 on/off" << endl
        << "F9: All Lights on/off" << endl
        << "F11: Ambient Light on/off" << endl
        << "1: Pacman cam" << endl
        << "2-3-4-5: Ghost1-2-3-4 Cam" << endl
        << "6-7-8-9: Light1-2-3-4 Cam" << endl
        << "0: Initial Cam" << endl
        << endl;
}

// Respond to graphic character keys.
// Parameters give key code and mouse coordinates.
void graphicKeys (unsigned char key, int x, int y)
{
	switch (key)
	{
		case 'h':
            help();
            break;
            
        case 27:
            exit(0);
            break;
            
        case 'w':
            fw_rw -= 0.2*mvSTEP;
            break;
        case 's':
            fw_rw += 0.2*mvSTEP;
            break;
        case 'a':
            lt_rt -= 0.2*mvSTEP;
            break;
        case 'd':
            lt_rt += 0.2*mvSTEP;
            break;
		case ',':
			up_dn -= 0.2*mvSTEP;
            break;
		case '.':
			up_dn += 0.2*mvSTEP;
            break;
        case ']':
            roll -= 10*RotSTEP;
		    if (roll < -ALL_ROUND) {
                roll += ALL_ROUND;
            }
            break;
        case '[':
            roll += 10*RotSTEP;
            if (roll > -ALL_ROUND) {
                roll += ALL_ROUND;
            }
            break;
            
        case '1':
            ProcessMenu(5);
            break;
        case '2':
            ProcessMenu(6);
            break;
        case '3':
            ProcessMenu(7);
            break;
        case '4':
            ProcessMenu(8);
            break;
        case '5':
            ProcessMenu(9);
            break;
        case '6':
            ProcessMenu(10);
            break;
        case '7':
            ProcessMenu(11);
            break;
        case '8':
            ProcessMenu(12);
            break;
        case '9':
            ProcessMenu(13);
            break;
        case '0':
            ProcessMenu(16);
            break;

        case 't' :
        	timer1->startTimer();

        default:
            cout << key << endl;
	}
    glutPostRedisplay();
}

//updates the scene according to menu selection
void ProcessMenu(GLint value)
{
	switch(value)
	{
		case 1:
			isWireFrame = false;
			break;
            
		case 2:
			isWireFrame = true;
			break;
            
        case 3:
            glShadeModel(GL_SMOOTH);
            break;
            
        case 4:
            glShadeModel(GL_FLAT);
            break;
            
            /* Pacman-cam */
        case 5:
            eye_x = pacman->x;
            eye_y = pacman->y+1.0;
            eye_z = pacman->z;
            
            center_x = pacman->x;
            center_y = pacman->y;
            center_z = pacman->z+5.0;
            
            fw_rw = 0;
            up_dn = 0;
            lt_rt = 0;
            
            yaw = 0;
            pitch  = 0;
            roll = 0;   
            
            break;
            
            /* Ghost1-Cam */    
        case 6:
            eye_x = ghost1->x;
            eye_y = ghost1->y+1.0;
            eye_z = ghost1->z;
            
            center_x = ghost1->x;
            center_y = ghost1->y;
            center_z = ghost1->z+5.0;
            
            fw_rw = 0;
            up_dn = 0;
            lt_rt = 0;
            
            yaw = 0;
            pitch  = 0;
            roll = 0;   
            
            break;
            
            /* Ghost2-Cam */
        case 7:
            eye_x = ghost2->x;
            eye_y = ghost2->y+1.0;
            eye_z = ghost2->z;
            
            center_x = ghost2->x;
            center_y = ghost2->y;
            center_z = ghost2->z+5.0;
            
            fw_rw = 0;
            up_dn = 0;
            lt_rt = 0;
            
            yaw = 0;
            pitch  = 0;
            roll = 0;   
            
            break;
            
            /* Ghost3-Cam */    
        case 8:
            eye_x = ghost3->x;
            eye_y = ghost3->y+1.0;
            eye_z = ghost3->z;
            
            center_x = ghost3->x;
            center_y = ghost3->y;
            center_z = ghost3->z+5.0;            
            
            fw_rw = 0;
            up_dn = 0;
            lt_rt = 0;
            
            yaw = 0;
            pitch  = 0;
            roll = 0;   
            
            break;
            
            /* Ghost4-Cam */
        case 9:
            eye_x = ghost4->x;
            eye_y = ghost4->y+1.0;
            eye_z = ghost4->z;
            
            center_x = ghost4->x;
            center_y = ghost4->y;
            center_z = ghost4->z+5.0;            
            
            fw_rw = 0;
            up_dn = 0;
            lt_rt = 0;
            
            yaw = 0;
            pitch  = 0;
            roll = 0;   
            
            break;
            
            /* Light1-Cam */
        case 10:
            eye_x = lamp1->x;
            eye_y = lamp1->y;
            eye_z = lamp1->z;
            
            //center_x = initial_center[0];
            //center_y = initial_center[1];
            //center_z = initial_center[2];
            center_x = lamp1->x +2.82;
            center_y = lamp1->y -4;
            center_z = lamp1->z +2.82;
            
            
            fw_rw = 0;
            up_dn = 0;
            lt_rt = 0;
            
            yaw = 0;
            pitch  = 0;
            roll = 0;
            
            break;
            
            /* Light2-Cam */
        case 11:
            eye_x = lamp2->x;
            eye_y = lamp2->y;
            eye_z = lamp2->z;
            
            //center_x = initial_center[0];
            //center_y = initial_center[1];
            //center_z = initial_center[2];
            
            center_x = lamp2->x -2.82;
            center_y = lamp2->y -4;
            center_z = lamp2->z +2.82;
            
            fw_rw = 0;
            up_dn = 0;
            lt_rt = 0;
            
            yaw = 0;
            pitch  = 0;
            roll = 0;   
            
            break;
            
            /* Light3-Cam */
		case 12:
            eye_x = lamp3->x;
            eye_y = lamp3->y;
            eye_z = lamp3->z;
            
            //center_x = initial_center[0];
            //center_y = initial_center[1];
            //center_z = initial_center[2];
            center_x = lamp3->x + 2.82;
            center_y = lamp3->y - 4;
            center_z = lamp3->z -2.82;
            
            fw_rw = 0;
            up_dn = 0;
            lt_rt = 0;
            
            yaw = 0;
            pitch  = 0;
            roll = 0;                        
            
            break;
            
            /* Light4-Cam */
		case 13:
            eye_x = lamp4->x;
            eye_y = lamp4->y;
            eye_z = lamp4->z;
            
            //center_x = initial_center[0];
            //center_y = initial_center[1];
            //center_z = initial_center[2];
            center_x = lamp4->x -2.82;
            center_y = lamp4->y -4;
            center_z = lamp4->z -2.82;
            
            fw_rw = 0;
            up_dn = 0;
            lt_rt = 0;
            
            yaw = 0;
            pitch  = 0;
            roll = 0;                        
            
            break;
            
            /* Enable Ambient Light */
        case 14:
            glEnable(GL_LIGHT0);
            break;
            
            /* Disable Ambient Light */
        case 15:
            glDisable(GL_LIGHT0);
            break;
            
            /* Initial-Cam */
        case 16:
            eye_x = initial_eye[0];
            eye_y = initial_eye[1];
            eye_z = initial_eye[2];
            
            center_x = initial_center[0];
            center_y = initial_center[1];
            center_z = initial_center[2];
            
            fw_rw = 0;
            up_dn = 0;
            lt_rt = 0;
            
            yaw = 0;
            pitch  = 0;
            roll = 0;            
            
            break;
            
            /* Enable/Disable Color Material */
        case 17:
            if (color_material_enabled) {
                color_material_enabled = false;
            } else {
                color_material_enabled = true;

            }
            break;
            
            /* Enable Light 1 */
        case 19:
            lamp1->turnOn();
            break;
            
            /* Disable Light 1 */
        case 20:
            lamp1->turnOff();
            break;
            
            /* Enable Light 2 */
        case 21:
            lamp2->turnOn();
            break;
            
            /* Disable Light 2 */
        case 22:
            lamp2->turnOff();
            break;
            
            /* Enable Light 3 */
        case 23:
            lamp3->turnOn();
            break;
            
            /* Disable Light 3 */
        case 24:
            lamp3->turnOff();
            break;
            
            /* Enable Light 4 */
        case 25:
            lamp4->turnOn();
            break;
            
            /* Disable Light 4 */
        case 26:
            lamp4->turnOff();
            break;
            
            /* Enable Lamps */
        case 27:
            lamp1->turnOn();
            lamp2->turnOn();
            lamp3->turnOn();
            lamp4->turnOn();
            break;
            
            /* Disable Lamps */
        case 28:
            lamp1->turnOff();
            lamp2->turnOff();
            lamp3->turnOff();
            lamp4->turnOff();
            break;
            
            /* Enable/Disable Textures */
        case 29:
            textures_enabled = 1 - textures_enabled;
            break;
        
            /* Pacman Outfit 1 */
        case 30:
            pacman_outfit = 0;
            break;
            
            /* Pacman Outfit 2 */
        case 31:
            pacman_outfit = 1;
            break;
            
            /* Pacman Outfit 3 */
        case 32:
            pacman_outfit = 2;
            break;

            /* Enable/Disable Pellet Texture */
        case 33:
            texturePellets = 1 - texturePellets;
            break;

            /* Enable/Disable Power Pellet Texture */
        case 34:
            texturePPellets = 1 - texturePPellets;
            break;

            /* Enable/Disable All Pellet Texture */
        case 35:
            if (texturePellets || texturePPellets) {
                texturePellets = 0;
                texturePPellets = 0;
            } else {
                texturePellets = 1;
                texturePPellets = 1;
            }
            break;
            

        default:
            break;
	}
    
	glutPostRedisplay();
}

// Respond to function keys.
// Parameters give key code and mouse coordinates.
void functionKeys (int key, int x, int y)
{
   switch (key)
   {
       case GLUT_KEY_F10:
           resetViewParameters();
           break;
           
       case GLUT_KEY_F1:
           projType = 1 - projType;
           break;
           
       case GLUT_KEY_F2:
           idleEnable = 1 - idleEnable;
           break;
           
       case GLUT_KEY_F3:
           zoom('+');
           break;
           
       case GLUT_KEY_F4:
           zoom('-');
           break;
           
       case GLUT_KEY_F5:
           if (lamp1->isOn) {
               lamp1->turnOff();
           } else {
               lamp1->turnOn();
           }
           break;
           
       case GLUT_KEY_F6:
           if (lamp2->isOn) {
               lamp2->turnOff();
           } else {
               lamp2->turnOn();
           }
           
           break;
           
       case GLUT_KEY_F7:
           if (lamp3->isOn) {
               lamp3->turnOff();
           } else {
               lamp3->turnOn();
           }
           
           break;
           
       case GLUT_KEY_F8:
           if (lamp4->isOn) {
               lamp4->turnOff();
           } else {
               lamp4->turnOn();
           }
           
           break;
           
       case GLUT_KEY_F9:
           if (lamp1->isOn || lamp2->isOn || lamp3->isOn || lamp4->isOn) {
               lamp1->turnOff();
               lamp2->turnOff();
               lamp3->turnOff();
               lamp4->turnOff();
           } else {
               lamp1->turnOn();
               lamp2->turnOn();
               lamp3->turnOn();
               lamp4->turnOn();
           }

           break;
           
       case GLUT_KEY_F11:
           ProcessMenu(15-ambient_light);
           ambient_light = 1 - ambient_light;
           break;
           
       case GLUT_KEY_UP:
           pitch += 10*RotSTEP;
           if (pitch > ALL_ROUND)
               pitch -= ALL_ROUND;
           break;
           
       case GLUT_KEY_DOWN:
           pitch -= 10*RotSTEP;
           if (pitch < -ALL_ROUND)
               pitch += ALL_ROUND;
           break; 

		case GLUT_KEY_RIGHT:
            yaw -= 10*RotSTEP;
		    if (yaw < -ALL_ROUND) {
                yaw += ALL_ROUND;
            }
            break;
           
        case GLUT_KEY_LEFT:
            yaw += 10*RotSTEP;
            if (yaw > -ALL_ROUND) {
                yaw += ALL_ROUND;
            }
            break;  
   }

    glutPostRedisplay();
}



void setupLighting()
{
    // Light values and coordinates
    GLfloat lightModelIntensity[] = { 0.1f, 0.1f, 0.1f, 1.0f };
    
    /* Ambient Light Values */
    
    GLfloat lightAmbient[]  = { 0.7f, 0.7f, 0.7f, 1.0f };
    GLfloat lightDiffuse[]  = { 0.7f, 0.7f, 0.7f, 1.0f };
    GLfloat lightSpecular[] = { 0.7f, 0.7f, 0.7f, 1.0f };
    GLfloat lightPosition[] = { 0.0f, 1.0f, 0.0f, 0.0f }; /* Point down Y-Axis */
    
    /* Spotlight Values */
    GLfloat spotlightAmbient[]  = { 0.5f, 0.5f, 0.0f, 1.0f };
    GLfloat spotlightDiffuse[]  = { 0.5f, 0.5f, 0.0f, 1.0f };
    GLfloat spotlightSpecular[] = { 0.5f, 0.5f, 0.0f, 1.0f };
    GLfloat spotlightPosition1[] = { 0.5f, 1.0f, 0.5f, 1.0f };
    GLfloat spotlightPosition2[] = { 19.5f, 1.0f, 0.5f, 1.0f };
    GLfloat spotlightPosition3[] = { 0.5f, 1.0f, 21.5f, 1.0f };
    GLfloat spotlightPosition4[] = { 19.5f, 1.0f, 21.5f, 1.0f };
    GLfloat spotlightDirection1[] = { 1.0f, 0.0f, 1.0f};
    GLfloat spotlightDirection2[] = { -1.0f, 0.0f, 1.0f};
    GLfloat spotlightDirection3[] = { 1.0f, 0.0f, -1.0f};
    GLfloat spotlightDirection4[] = { -1.0f, 0.0f, -1.0f};

    
    lamp1 = new Lamp(GL_LIGHT1, spotlightDirection1);
    lamp2 = new Lamp(GL_LIGHT2, spotlightDirection2);
    lamp3 = new Lamp(GL_LIGHT3, spotlightDirection3);
    lamp4 = new Lamp(GL_LIGHT4, spotlightDirection4);
        
    lamp1->setAmbDiffSpec(spotlightAmbient, spotlightDiffuse, spotlightSpecular);
    lamp2->setAmbDiffSpec(spotlightAmbient, spotlightDiffuse, spotlightSpecular);
    lamp3->setAmbDiffSpec(spotlightAmbient, spotlightDiffuse, spotlightSpecular);
    lamp4->setAmbDiffSpec(spotlightAmbient, spotlightDiffuse, spotlightSpecular);

    /* setup where the lamps are modeled */
    lamp1->setModelPosition(spotlightPosition1);
    lamp2->setModelPosition(spotlightPosition2);
    lamp3->setModelPosition(spotlightPosition3);
    lamp4->setModelPosition(spotlightPosition4);

    glEnable(GL_DEPTH_TEST);	// Hidden surface removal
    glFrontFace(GL_CCW);		// Counter clock-wise polygons face out
 
    // Enable lighting
    glEnable(GL_LIGHTING);

    /* Setup and enable light 0 */    
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lightModelIntensity);
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
    glEnable(GL_LIGHT0);
    
    // Set Material properties to follow glColor values
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

    // Black blue background
    glClearColor(0.0f, 0.0f, 0.4f, 1.0f );
    
    // Enable Transparency
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    //Rescale Normals if needed
    glEnable(GL_NORMALIZE);
}

void cleanup()
{
    /* Clean up */
    delete pacman;
    delete ghost1;
    delete ghost2;
    delete ghost3;
    delete ghost4;
    delete map1;
    delete lamp1;
    delete lamp2;
    delete lamp3;
    delete lamp4;
    
}

int main (int argc, char **argv)
{
    // GLUT initialization. Enable double buffer mode
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(width, height);
	glutCreateWindow("Pacman3D Assignment3");
    
	GLint nModeMenu; // menu identifier used when calling glutsetmenu
	nModeMenu = glutCreateMenu(ProcessMenu);
	glutAddMenuEntry("Solid",1);
	glutAddMenuEntry("Wire",2);
    glutAddMenuEntry("-------------", 0);
    glutAddMenuEntry("Smooth Shading", 3);
    glutAddMenuEntry("Flat Shading", 4);
    glutAddMenuEntry("-------------", 0);
    glutAddMenuEntry("Initial Cam", 16);
    glutAddMenuEntry("Pacman-Cam", 5);
    glutAddMenuEntry("Ghost1-Cam", 6);
    glutAddMenuEntry("Ghost2-Cam", 7);
    glutAddMenuEntry("Ghost3-Cam", 8);
    glutAddMenuEntry("Ghost4-Cam", 9);
    glutAddMenuEntry("Light1-Cam", 10);
    glutAddMenuEntry("Light2-Cam", 11);
    glutAddMenuEntry("Light3-Cam", 12);
    glutAddMenuEntry("Light4-Cam", 13);
    glutAddMenuEntry("-------------", 0);
    glutAddMenuEntry("Enable Ambient Light", 14);
    glutAddMenuEntry("Disable Ambient Light",15);
    glutAddMenuEntry("-------------", 0);
    glutAddMenuEntry("Enable/Disable Color Material", 17);
    glutAddMenuEntry("-------------", 0);
    glutAddMenuEntry("Enable Lamp 1", 19);
    glutAddMenuEntry("Disable Lamp 1", 20);
    glutAddMenuEntry("Enable Lamp 2", 21);
    glutAddMenuEntry("Disable Lamp 2", 22);
    glutAddMenuEntry("Enable Lamp 3", 23);
    glutAddMenuEntry("Disable Lamp 3", 24);
    glutAddMenuEntry("Enable Lamp 4", 25);
    glutAddMenuEntry("Disable Lamp 4", 26);
    glutAddMenuEntry("Enable All Lamps", 27);
    glutAddMenuEntry("Disable All Lamps", 28);
    glutAddMenuEntry("-------------", 0);
    glutAddMenuEntry("Enable/Disable Textures", 29);
    glutAddMenuEntry("-------------", 0);
    glutAddMenuEntry("Pacman Outfit 1", 30);
    glutAddMenuEntry("Pacman Outfit 2", 31);
    glutAddMenuEntry("Pacman Outfit 3", 32);
    glutAddMenuEntry("-------------", 0);
    glutAddMenuEntry("Enable/Disable Pellet Texture", 33);
    glutAddMenuEntry("Enable/Disable Power Pellet Texture", 34);
    glutAddMenuEntry("Enable/Disable All Pellet Texture", 35);


	glutAttachMenu(GLUT_RIGHT_BUTTON);
    
	// Register call backs for standard tasks such as:
	// display, windowresize, keypress, functionkey press, mouse movement.
	glutDisplayFunc(display);
	glutReshapeFunc(reshapeMainWindow);
	glutKeyboardFunc(graphicKeys);
    glutSpecialFunc(functionKeys);
    glutMotionFunc(mouseMovement);
	glutIdleFunc(idle);
    
    // Display help.
	help();
    
    //init scene
    glShadeModel(GL_SMOOTH);
    setupLighting();
    
	/* init ghosts */
    pacman = new Pacman();
    pacman->initPosition(1.0f, 0.2f, 3.0f);
    
    timer1 = new Timer();

    ghost1 = new Ghost(1.0, 0.0, 0.0);
    ghost2 = new Ghost(0.0, 1.0, 0.0);
    ghost3 = new Ghost(1.0, 0.5, 0.7);
    ghost4 = new Ghost(1.0, 0.5, 0.0);
    
    ghost1->initPosition(9.0f,  0.2f, 11.0f);
    ghost2->initPosition(10.0f, 0.2f, 11.0f);
    ghost3->initPosition(11.0f, 0.2f, 11.0f);
    ghost4->initPosition(10.0f, 0.2f, 10.0f);
        
    /* init map */
    srand(time(NULL)); //seed rand for pellet colours
    map1 = new Map(map, 23, 21);        
    
    glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
    glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);

    atexit(cleanup);
    
    // Enter GLUT loop.
	glutMainLoop();
    
}

