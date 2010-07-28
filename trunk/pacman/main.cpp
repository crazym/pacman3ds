/*
 *  main.cpp
 * 
 *
 *  Created by carlos, bronson, sid, andrew, allan on 10-07-16.
 *  Copyright 2010 Concordia University. All rights reserved.
	Carlos Pinto (Team Leader)
	ID: 9343911

	Bronson Zgeb
	ID: 9402268

	Andrew Wolczak
	ID: 9095543

	Allan Tran
	ID: 9099824

	Siddhartha Kattoju
	ID: 9209905
 */

// This program uses sampleprogram.cpp as a template
// This Program Draws a scene in a Pacman game.

// Function Keys support:
//   1. F1 : toggle between ortho/perspective mode of viewing.
//   2. F2 : toggle between continuous rotation about y-axis and stop rotation
//   3. Up and Down Arrow keys for rotating view about  x-axis
//	 4. Left and Right Arrow keys for rotating about z-axis
//	 5.	F10: reset view in case your view parameters get out of control.
//	 6. W : Forward
//   7. S : Backward
//   8. A : Strafe Left
//   9. D : Strafe Right
//   10. , : Lower Camera
//   11. . : Raise Camera


// Link with: opengl32.lib, glu32.lib, glut32.lib.
// glut includes links to the other two libraries.
#ifdef __APPLE__
#include <cstdlib>
#include <GLUT/glut.h>
#else 
#include <stdlib.h>
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

#include "Map.h"
#include "Tile.h"

using namespace std;


/**************************
 Game Objects
 **************************/
static Pacman *pacman;
static Ghost *ghost1;
static Ghost *ghost2;
static Ghost *ghost3;
static Ghost *ghost4;
static Map *map1;

static char map[483] = {										 
    
    'W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W',	 // Current map
    'W','Z','Z','Z','Z','Z','Z','Z','Z','Z','W','Z','Z','Z','Z','Z','Z','Z','Z','Z','W',
    'W','Z','W','W','W','Z','W','W','W','Z','W','Z','W','W','W','Z','W','W','W','Z','W',
    'W','Z','W','W','W','Z','W','W','W','Z','W','Z','W','W','W','Z','W','W','W','Z','W',
    'W','Z','Z','Z','Z','Z','Z','Z','Z','Z','W','Z','Z','Z','Z','Z','Z','Z','Z','Z','W',
    'W','Z','W','W','W','Z','W','Z','W','W','W','W','W','Z','W','Z','W','W','W','Z','W',
    'W','Z','Z','Z','Z','Z','W','Z','Z','Z','W','Z','Z','Z','W','Z','Z','Z','Z','Z','W',
    'W','W','W','W','W','Z','W','W','W','Z','W','Z','W','W','W','Z','W','W','W','W','W',
    'Y','Y','Y','Y','W','Z','W','Z','Z','Z','Z','Z','Z','Z','W','Z','W','Y','Y','Y','Y',
    'W','W','W','W','W','Z','W','Z','W','W','Y','W','W','Z','W','Z','W','W','W','W','W',
    'Y','Y','Y','Y','Y','Z','Z','Z','W','Y','Y','Y','W','Z','Z','Z','Y','Y','Y','Y','Y',
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
    'W','Z','Z','Z','Z','Z','Z','Z','Z','Z','Z','Z','Z','Z','Z','Z','Z','Z','Z','Z','W',
    'W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W'
    
};

// Initial size of graphics window on your screen.
const int WIDTH  = 800; // in pixels
const int HEIGHT = 600; //

// increment for idle function rotation and zoom
const double RotSTEP = 0.2;
const double mvSTEP = 5.0;
const double ALL_ROUND = 360;
const double ZoomSTEP = 0.9;
const double zoomFactor = 1.03;

// Current size of window (will change when you resize window)
int width  = WIDTH;
int height = HEIGHT;

// Mouse positions, normalized to [0,1].
double xMouse = 0.5;
double yMouse = 0.5;

// Bounds of viewing frustum, maintain uniform scaling.
double viewWindowLeft =  -40;
double viewWindowRight  = 40;
double viewWindowBottom =  -40;
double viewWindowTop  = 40;
double nearPlane =  1.5;
double farPlane  = 120;

// Viewing angle.
double fovy = 60;

/* Rotation */
double alpha = 0;                                  // rotation angle about Y axis.
double beta = 0;                                   // rotation angle about X axis.
double yamma = 0;

/* misc */
double halfway = - (farPlane + nearPlane) / 2;	   // half way between near and far planes

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

//////////////////// Default Camera Positions ///////////////
/*
key 6: Bottom left Corner 
eye_x=-10.0;
eye_y=2.5;
eye_z=40.5;
center_x=28.0;
center_y=0.0;
center_z=0.0;

key 7: Bottom right Corner 
eye_x=37.0;
eye_y=2.5;
eye_z=39.5;
center_x=2.0;
center_y=0.0;
center_z=0.0;

key 8: Top right Corner 
eye_x=35.5;
eye_y=2.5;
eye_z=-6.5;
center_x=27.5;
center_y=0.0;
center_z=0.0;

key 9: Top left Corner 
eye_x=-7.5;
eye_y=2.5;
eye_z=-11.5;
center_x=0.0;
center_y=0.0;
center_z=0.0;

	// gluLookAt Calibration
    //gluLookAt(eye_x, eye_y, eye_z, center_x, center_y, center_z, up_x, up_y, up_z);
		case '1':
            eye_x+=0.5;
			cout << "eye_x : " << eye_x << endl;
            break;
		case '2':
            eye_x-=0.5;
			cout << "eye_x : " << eye_x << endl;
            break;
		case '3':
            eye_y+=0.5;
			cout << "eye_y : " << eye_y << endl;
            break;
		case '4':
            eye_y-=0.5;
			cout << "eye_y : " << eye_y << endl;
            break;
		case '5':
            eye_z+=0.5;
			cout << "eye_z : " << eye_z << endl;
            break;
		case '6':
            eye_z-=0.5;
			cout << "eye_z : " << eye_z << endl;
            break;
 		case '7':
            center_x+=0.5;
			cout << "center_x : " << center_x << endl;
            break;
		case '8':
            center_x-=0.5;
			cout << "center_x : " << center_x << endl;
            break;
		case '9':
            center_y+=0.5;
			cout << "center_y : " << center_y << endl;
            break;
		case '0':
            center_y-=0.5;
			cout << "center_y : " << center_y << endl;
            break;
		case '-':
            center_z+=0.5;
			cout << "center_z : " << center_z << endl;
            break;
		case '=':
            center_z-=0.5;
			cout << "center_z : " << center_z << endl;
            break;

*/
bool idleEnable = 0;	// flags that set continuous rotation on/off
bool projType = 1;      // flag for proj type; ortho = 0, perspective = 1
bool isWireFrame =0;    // flag for setting wire frame mode

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
	alpha = 0.0;
	beta = 0.0;
	yamma = 0.0;
    
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

// This function is called to display the scene.
void display ()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
    // set modelling mode
	glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(eye_x, eye_y, eye_z, center_x, center_y, center_z, up_x, up_y, up_z);

    //translate along Z, Y, X
	glTranslatef(0,0,fw_rw);
	glTranslatef(0,up_dn,0);
	glTranslatef(lt_rt,0,0);
    
	glRotatef(beta, 1, 0, 0);
	glRotatef(alpha, 0, 1, 0);
	glRotatef(yamma, 0, 0, 1);

	// Draw model axes in centre of room.
    //drawAxes();

    // Draw the scene in double buffer.
    glColor3f(0, 1, 1);
    //drawScene(20.0, 20.0, 20.0);
    
    if(isWireFrame) {
        glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    } else {
        glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
    }
    
    map1->draw();
    pacman->draw();
    ghost1->draw();
    ghost2->draw();
    ghost3->draw();
    ghost4->draw();
    
    // now swap buffer
    glutSwapBuffers();
}

// This function is called when there is nothing else to do.
void idle ()
{

   if (idleEnable)
   {	
       alpha += RotSTEP;
       if (alpha > ALL_ROUND){
           alpha -= ALL_ROUND;           
       }
       // Display normalized coordinates in title bar.
       const int BUFSIZE = 200;
       static char buffer[BUFSIZE];
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
            << alpha 
            << ".  Beta=" 
            << setw(3) 
            << beta 
            << setprecision(2)
            << ". Distance=" 
            << halfway 
            << "." 
            << ends;

       glutSetWindowTitle(buffer);

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
	width = newWidth;
	height = newHeight;
	glViewport(0, 0, width, height);
    setView();
	glMatrixMode (GL_MODELVIEW);
    gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

// Display Help.
void help()
{
   cout << "F1 : toggle between ortho/perspective mode of viewing" << endl
		<< "F2 : toggle between continuous rotation about y-axis and stop rotation" << endl
		<< "Up and Down Arrow keys for rotating view about  x-axis" << endl
		<< "Left and Right Arrow keys for rotating about z-axis" << endl
		<< "F10: reset view in case your view parameters get out of control" << endl
		<< "W : Forward" << endl
		<< "S : Backward" << endl
		<< "A : Strafe Left" << endl
		<< "D : Strafe Right" << endl
		<< ", : Lower Camera" << endl
		<< ". : Raise Camera" << endl 
        << "Right Mouse Button: Menu" << endl
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
            fw_rw += 0.2*mvSTEP;
            break;
        case 's':
            fw_rw -= 0.2*mvSTEP;
            break;
        case 'a':
            lt_rt += 0.2*mvSTEP;
            break;
        case 'd':
            lt_rt -= 0.2*mvSTEP;
            break;
		case ',':
			up_dn += 0.2*mvSTEP;
            break;
		case '.':
			up_dn -= 0.2*mvSTEP;
            break;
        default:
            cout << key << endl;
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
           
       case GLUT_KEY_UP:
           beta += 10*RotSTEP;
           if (beta > ALL_ROUND)
               beta -= ALL_ROUND;
           break;
           
       case GLUT_KEY_DOWN:
           beta -= 10*RotSTEP;
           if (beta < -ALL_ROUND)
               beta += ALL_ROUND;
           break; 

		case GLUT_KEY_RIGHT:
            alpha -= 10*RotSTEP;
		    if (alpha < -ALL_ROUND) {
                alpha += ALL_ROUND;
            }
            break;
           
        case GLUT_KEY_LEFT:
            alpha += 10*RotSTEP;
            if (alpha > -ALL_ROUND) {
                alpha += ALL_ROUND;
            }
            break;  
   }

    glutPostRedisplay();
}

//updates the scene according to menu selection
void ProcessMenu(int value)
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
            
            alpha = 0;
            beta  = 0;
            yamma = 0;   
            
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
            
            alpha = 0;
            beta  = 0;
            yamma = 0;   
            
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
            
            alpha = 0;
            beta  = 0;
            yamma = 0;   
            
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
            
            alpha = 0;
            beta  = 0;
            yamma = 0;   
            
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
            
            alpha = 0;
            beta  = 0;
            yamma = 0;   
            
            break;
            
        /* Light1-Cam */
        case 10:
            eye_x = -2;
            eye_y = 3.5;
            eye_z = -2;
            center_x = initial_center[0];
            center_y = initial_center[1];
            center_z = initial_center[2];
            
            fw_rw = 0;
            up_dn = 0;
            lt_rt = 0;
            
            alpha = 0;
            beta  = 0;
            yamma = 0;
            
            break;
        
        /* Light2-Cam */
        case 11:
            eye_x = 23;
            eye_y = 3.5;
            eye_z = -2;
            center_x = initial_center[0];
            center_y = initial_center[1];
            center_z = initial_center[2];
            
            fw_rw = 0;
            up_dn = 0;
            lt_rt = 0;
            
            alpha = 0;
            beta  = 0;
            yamma = 0;   
            
            break;
            
        /* Light3-Cam */
		case 12:
			eye_x = -2;
			eye_y = 3.5;
			eye_z = 24;
            center_x = initial_center[0];
            center_y = initial_center[1];
            center_z = initial_center[2];
            
            fw_rw = 0;
            up_dn = 0;
            lt_rt = 0;
            
            alpha = 0;
            beta  = 0;
            yamma = 0;                        
            
            break;
           
        /* Light4-Cam */
		case 13:
			eye_x = 23;
			eye_y = 3.5;
			eye_z = 24;
            center_x = initial_center[0];
            center_y = initial_center[1];
            center_z = initial_center[2];
            
            fw_rw = 0;
            up_dn = 0;
            lt_rt = 0;
            
            alpha = 0;
            beta  = 0;
            yamma = 0;                        
            
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
            
            alpha = 0;
            beta  = 0;
            yamma = 0;            
            
            break;

        default:
            break;
	}

	glutPostRedisplay();
}

void setupLighting()
{
    // Light values and coordinates
    GLfloat  whiteLight[] = { 0.45f, 0.45f, 0.45f, 1.0f };
    GLfloat  sourceLight[] = { 0.25f, 0.25f, 0.25f, 1.0f };
    //GLfloat	 lightPos[] = { -50.0f, 25.0f, 250.0f, 0.0f };
    GLfloat	 lightPos[] = { 11.0f, 25.0f, 10.0f, 0.0f };

    glEnable(GL_DEPTH_TEST);	// Hidden surface removal
    glFrontFace(GL_CCW);		// Counter clock-wise polygons face out
 
    // Enable lighting
    glEnable(GL_LIGHTING);

    // Setup and enable light 0
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT,whiteLight);
    glLightfv(GL_LIGHT0,GL_AMBIENT,sourceLight);
    glLightfv(GL_LIGHT0,GL_DIFFUSE,sourceLight);
    glLightfv(GL_LIGHT0,GL_POSITION,lightPos);
    glEnable(GL_LIGHT0);

    // Enable color tracking
    glEnable(GL_COLOR_MATERIAL);

    // Set Material properties to follow glColor values
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

    // Black blue background
    glClearColor(0.0f, 0.0f, 0.4f, 1.0f );
    
    // Enable Transparency
    glEnable (GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

int main (int argc, char **argv)
{
    // GLUT initialization. Enable double buffer mode
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(width, height);
	glutCreateWindow("GLUT Skeleton Program");
    
	int nModeMenu; // menu identifier used when calling glutsetmenu
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
    pacman->initPosition(1.0f, 0.2f, 1.0f);
    
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
    
    // Enter GLUT loop.
	glutMainLoop();
    
    /* Clean up */
    delete pacman;
    delete ghost1;
    delete ghost2;
    delete ghost3;
    delete ghost4;
    delete map1;
}

