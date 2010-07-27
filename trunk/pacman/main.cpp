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
//   1. F2 : toggle between continuous rotation about y-axis and stop rotation
//   2. Up and Down Arrow keys for rotating view about  x-axis
//	 3. Left and Right Arrow keys for rotating about z-axis
//	 4.	F10: reset view in case your view parameters get out of control.
//	 5. W : Forward
//   6. S : Backward
//   7. Q : Strafe Left
//   8. E : Strafe Right
//   9. A : Left Rotation around Y-axis
//   10. D : Right Rotation around Y-axis


// Link with: opengl32.lib, glu32.lib, glut32.lib.
// glut includes links to the other two libraries.
#ifdef __APPLE__
#include <GLUT/glut.h>
#else 
#include <GL/glut.h>
#endif

#include <cmath>
#include <iostream>
#include <sstream>
#include <iomanip>

#include "Maze.h"
#include "Ghost.h"
#include "Pacman.h"

using namespace std;

static Ghost *ghost1;
static Ghost *ghost2;
static Ghost *ghost3;
static Ghost *ghost4;


// Initial size of graphics window on your screen.
const int WIDTH  = 600; // in pixels
const int HEIGHT = 400; //

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

// Variables.
double alpha = 0;                                  // rotation angle about Y axis.
double beta = 0;                                   // rotation angle about X axis.
double yamma = 0;
double halfway = - (farPlane + nearPlane) / 2;	   // half way between near and far planes

//camera
double fw_rw=0;
double up_dn=0;
double lt_rt=0;

double eye_x=-20;
double eye_y=-20;
double eye_z=-20;



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

void drawMaze(GLdouble x, GLdouble y, GLdouble z)
{
	// Draw everything as wireframe only, if flag is set
		if(isWireFrame)
			glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
		else
			glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);

	// will be mapped to a text file.
	char map[483] = {										 
        
        'H','N','N','N','N','N','N','N','N','N','D','N','N','N','N','N','N','N','N','N','I',	 // Current map
        'L','Z','Z','Z','Z','Z','Z','Z','Z','Z','B','Z','Z','Z','Z','Z','Z','Z','Z','Z','M',
        'L','Z','H','N','I','Z','H','N','I','Z','B','Z','H','N','I','Z','H','N','I','Z','M',
        'L','Z','K','O','J','Z','K','O','J','Z','B','Z','K','O','J','Z','K','O','J','Z','M',
        'L','Z','Z','Z','Z','Z','Z','Z','Z','Z','B','Z','Z','Z','Z','Z','Z','Z','Z','Z','M',
        'L','Z','A','A','A','Z','B','Z','A','A','C','A','A','Z','B','Z','A','A','A','Z','M',
        'L','Z','Z','Z','Z','Z','B','Z','Z','Z','B','Z','Z','Z','B','Z','Z','Z','Z','Z','M',
        'K','O','O','O','O','Z','B','A','A','Z','B','Z','A','A','B','Z','O','O','O','O','J',
        'Y','Y','Y','Y','M','Z','B','Z','Z','Z','Z','Z','Z','Z','B','Z','L','Y','Y','Y','Y',
        'O','O','O','O','J','Z','B','Z','O','O','Z','O','O','Z','B','Z','K','O','O','O','O',
        'Y','Y','Y','Y','Y','Z','Z','Z','L','Y','Y','Y','M','Z','Z','Z','Y','Y','Y','Y','Y',
        'N','N','N','N','I','Z','B','Z','L','Y','Y','Y','M','Z','B','Z','H','N','N','N','N',
        'Y','Y','Y','Y','M','Z','B','Z','N','N','N','N','N','Z','B','Z','L','Y','Y','Y','Y',
        'Y','Y','Y','Y','M','Z','B','Z','Z','Z','Z','Z','Z','Z','B','Z','L','Y','Y','Y','Y',
        'O','O','O','O','J','Z','B','Z','N','N','D','N','N','Z','B','Z','K','O','O','O','O',
        'L','Z','Z','Z','Z','Z','Z','Z','Z','Z','B','Z','Z','Z','Z','Z','Z','Z','Z','Z','M',
        'L','Z','O','O','Z','Z','O','O','O','Z','B','Z','O','O','O','Z','Z','O','O','Z','M',
        'L','Z','Z','M','Z','Z','Z','Z','Z','Z','Z','Z','Z','Z','Z','Z','Z','M','Z','Z','M',
        'E','A','Z','M','Z','Z','B','Z','N','N','D','N','N','Z','B','Z','Z','M','Z','A','G',
        'L','Z','Z','Z','Z','Z','B','Z','Z','Z','B','Z','Z','Z','B','Z','Z','Z','Z','Z','M',
        'L','Z','Z','O','O','O','F','O','Z','Z','B','Z','Z','O','F','O','O','O','Z','Z','M',
        'L','Z','Z','Z','Z','Z','Z','Z','Z','Z','Z','Z','Z','Z','Z','Z','Z','Z','Z','Z','M',
        'K','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','O','J'
        
    };
    glPushMatrix();
            glScalef(0.2,0.2,0.2);
            glTranslatef(x,y,z);
            DrawMaze(map);
		glPopMatrix();

}

void drawPacman(GLdouble x, GLdouble y, GLdouble z)
{

	// Draw everything as wireframe only, if flag is set
    if(isWireFrame) {
        glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    } else {
        glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
    }
    
	glPushMatrix();
		drawAxes();
		glTranslatef(x,y,z);
		glScalef(0.4,0.4,0.4);
		DrawPacman();
	glPopMatrix();

}

void drawGhost(GLdouble x, GLdouble y, GLdouble z, Ghost *ghost)
{
    
	// Draw everything as wireframe only, if flag is set
    if(isWireFrame) {
        glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    } else {
        glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
    }
    
    glPushMatrix();
    
        drawAxes();
        glTranslatef(x,y,z);
        glScalef(2,2,2);
        ghost->draw();
    
    glPopMatrix();
    
}


void drawSpecial(GLdouble Radius, GLdouble x, GLdouble y, GLdouble z)
{

	//anything else we might want to draw..

}



void drawScene(GLdouble scenewidth, GLdouble sceneheight, GLdouble scenedepth)
{
	/* container/sky  box */
	glPushMatrix();
	   glColor3f(0, 0.5, 0.5);
		glScaled(scenewidth, sceneheight, scenedepth);
		glutWireCube(1.0);
	glPopMatrix();

	glPushMatrix();
		drawMaze(-40,-40,-40);
		drawPacman(-5,-6,3);
		drawGhost(10,-6,14, ghost1);
        drawGhost(0,-6,5, ghost2);
        drawGhost(13,-6,14, ghost3);
        drawGhost(-6,-6,24, ghost4);
	glPopMatrix();
}


// This function is called to display the scene.
void display ()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
    // set modelling mode
	glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0, 20.0, 65.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    
    //translate along Z, Y, X
	glTranslatef(0,0,fw_rw);
	glTranslatef(0,up_dn,0);
	glTranslatef(lt_rt,0,0);
    
	glRotatef(beta, 1, 0, 0);
	glRotatef(alpha, 0, 1, 0);
	glRotatef(yamma, 0, 0, 1);

	// Draw model axes in centre of room.
    drawAxes();
    
    // Draw the scene in double buffer.
    glColor3f(0, 1, 1);
    drawScene(200.0, 200.0, 200.0);

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

// Display AAA.
void help()
{
   cout << "F1 : toggle between ortho/perspective mode of viewing"
		<< "F2 : toggle between continuous rotation about y-axis and stop rotation"
		<< "Up and Down Arrow keys for rotating view about  x-axis"
		<< "Left and Right Arrow keys for rotating about z-axis"
		<< "F10: reset view in case your view parameters get out of control"
		<< "W : Forward"
		<< "S : Backward"
		<< "Q : Strafe Left"
		<< "E : Strafe Right"
		<< "A : Left Rotation around Y-axis"
		<< "D : Right Rotation around Y-axis" << endl;
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
        case 'd':
            alpha -= 10*RotSTEP;
		    if (alpha < -ALL_ROUND) {
                alpha += ALL_ROUND;
            }
            break;
        case 'a':
            alpha += 10*RotSTEP;
            if (alpha > -ALL_ROUND) {
                alpha += ALL_ROUND;
            }
            break;
        case 'w':
            fw_rw += 0.2*mvSTEP;
            break;
            
        case 's':
            fw_rw -= 0.2*mvSTEP;
            break;
        case 'q':
            lt_rt += 0.2*mvSTEP;
            break;
        case 'e':
            lt_rt -= 0.2*mvSTEP;
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
           
       case GLUT_KEY_LEFT:
           yamma -= 10*RotSTEP;
           if (yamma > ALL_ROUND)
               yamma -= ALL_ROUND;
           break;
           
       case GLUT_KEY_RIGHT:
           yamma += 10*RotSTEP;
           if (yamma > ALL_ROUND)
               yamma += ALL_ROUND;           
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
	}

	glutPostRedisplay();
}

void setupLighting()
{
    // Light values and coordinates
    GLfloat  whiteLight[] = { 0.45f, 0.45f, 0.45f, 1.0f };
    GLfloat  sourceLight[] = { 0.25f, 0.25f, 0.25f, 1.0f };
    GLfloat	 lightPos[] = { -50.f, 25.0f, 250.0f, 0.0f };

    glPushMatrix();
		glTranslatef(-50.f, 25.0f, 250.0f);
		drawAxes();
    glPopMatrix();

    glEnable(GL_DEPTH_TEST);	// Hidden surface removal
    glFrontFace(GL_CCW);		// Counter clock-wise polygons face out
    //glEnable(GL_CULL_FACE);		// Do not calculate inside of jet

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
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f );

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
	glutAddMenuEntry("Flat ",1);
	glutAddMenuEntry("Wire",2);
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
    setupLighting();
    
	//initialise models
    //maze = new maze
    ghost1 = new Ghost(1.0, 0.0, 0.0, false);
    ghost2 = new Ghost(0.0, 1.0, 0.0, false);
    ghost3 = new Ghost(1.0, 0.5, 0.7, false);
    ghost4 = new Ghost(1.0, 0.5, 0.0, false);
    
    //pacman = new pacman
    
    // Enter GLUT loop.
	glutMainLoop();
}
