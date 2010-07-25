/*
 *  Floor.cpp
 * 
 *
 *  Created by allan tran on 10-07-16.
 *  Copyright 2010 Concordia University. All rights reserved.
 *	References: http://users.encs.concordia.ca/~c371_1/skeleton.cpp
 *				OpenGL SuperBible, Fourth Edition, Wright, Lipchak, Haemel, Addison-Wesley 2007
 *	July 18, 2010
 */

#include <iostream>
#include <strstream>
#include <iomanip>

#ifdef __APPLE__
#include <cstdlib>
#include <GLUT/glut.h>
#else 
#include <stdlib.h>
#include <GL/glut.h>
#endif

#include <cmath>

using namespace std;
/*
//GLOBAL VARIABLES
	//Initial size of graphics window
	const int WIDTH = 1000;
	const int HEIGHT = 1000;

	//Current size of window
	int width = WIDTH;
	int height = HEIGHT;

	//Bounds of viewing frustum
	double nearPlane =  0;
	double farPlane  = 500;

	//Viewing angle
	double fovy = 45.0;

	// Mouse positions, normalized to [0,1].
	double xMouse = 0.5;
	double yMouse = 0.5;

	//Variables
	double alpha = 0;								//Set by idle function
	double beta = 0;								//Set by mouse X
	double distanced = - (farPlane - nearPlane) / 2;    // Set by mouse Y

*/

void number()
{
	float radius = 15.0;
	float vectorX = 0.0;
	float vectorY = 0.0;
    glLineWidth(4.0);
	glBegin(GL_LINE_STRIP);			
	
	for(float angle = 0.0; angle<=(2.0*3.14159); angle+=0.01)
	{		
		vectorX = (radius*(float)sin((double)angle));
		vectorY = (radius*(float)cos((double)angle));
		glVertex2d(vectorX,vectorY);	
	}
	glEnd();
    glLineWidth(1.0);
}

void drawTile()
{
	// Draw model axes.
	/*glBegin(GL_LINES);
		// X axis
		glColor3f(1, 0, 0);
		glVertex3f(0, 0, 0);
		glVertex3f(120, 0, 0);
		// Y axis
		glColor3f(0, 1, 0);
		glVertex3f(0, 0, 0);
		glVertex3f(0, 120, 0);
		// Z axis
		glColor3f(0, 0, 1);
		glVertex3f(0, 0, 0);
		glVertex3f(0, 0, 120);
	glEnd();*/

	// Draw tile
	glBegin(GL_POLYGON);
		glColor3f( 0.8, 0.8, 0.8);
		//bottom face
		glNormal3f(0, -1, 0);

		glVertex3f(0, 0, 0);
		glVertex3f(100, 0, 0);
		glVertex3f(100, 0, -100);
		glVertex3f(0, 0, -100);
		glVertex3f(0, 0, 0);

		//front face
		glNormal3f(0, 0, 1);

		glVertex3f(0, 0, 0);
		glVertex3f(100, 0, 0);
		glVertex3f(100, -10, 0);
		glVertex3f(0, -10, 0);
		glVertex3f(0, 0, 0);

		//right face
		glNormal3f(1, 0, 0);
		
		glVertex3f(100, 0, 0);
		glVertex3f(100, -10, 0);
		glVertex3f(100, -10, -100);
		glVertex3f(100, 0, -100);
		glVertex3f(100, 0, 0);

		//back face
		glNormal3f(0, 0, -1);
		
		glVertex3f(0, 0, -100);
		glVertex3f(0, -10, -100);
		glVertex3f(100, -10, -100);
		glVertex3f(100, 0, -100);
		glVertex3f(0, 0, -100);

		//left face
		glNormal3f(-1, 0, 0);
		
		glVertex3f(0, 0, 0);
		glVertex3f(0, -10, 0);
		glVertex3f(0, -10, -100);
		glVertex3f(0, 0, -100);
		glVertex3f(0, 0, 0);

		//top face
		glNormal3f(0, 1, 0);
		
		glVertex3f(0, -10, 0);
		glVertex3f(0, -10, -100);
		glVertex3f(100, -10, -100);
		glVertex3f(100, -10, 0);
		glVertex3f(0, -10, 0);

	glEnd();

	//Group Number--------------------
	//Top part of number 8--------
	glPushMatrix();
		glColor3f(0, 0, 0);
		glTranslated(15, 0, -15);
		glRotatef(90, 1, 0, 0);
		number();
	glPopMatrix();
	//----------------------------
	//Bottom part of number 8-----
	glPushMatrix();
		glColor3f(0, 0, 0);
		glTranslated(35, 0, -15);
		glRotatef(90, 1, 0, 0);
		number();
	glPopMatrix();
	//----------------------------

}

/*
// This function is called when there is nothing else to do.
void idle ()
{
	const double STEP = 0.0;
	const double ALL_ROUND = 360;
	alpha += STEP;
	if (alpha > ALL_ROUND)
		alpha -= ALL_ROUND;

	glutPostRedisplay();
}

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
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(fovy, GLfloat(width) / GLfloat(height), nearPlane, farPlane);
}
void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Translate using Y mouse.
	distanced = - (yMouse * (farPlane - nearPlane) + nearPlane);
	glTranslatef(0, 0, distanced);

	// Rotation from idle function.
	alpha = 720 * yMouse;
	glRotatef(alpha, 0, 1, 0);

	// Rotation using X mouse.
	beta = 720 * xMouse;
	glRotatef(beta, 1, 0, 0);

	drawTile();

	glutSwapBuffers();
}


void main(int argc, char **argv)
{
	// GLUT initialization.
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(width, height);
	glutCreateWindow("Floor tiles");

	// Register call backs.
	glutDisplayFunc(display);
	glutReshapeFunc(reshapeMainWindow);
	glutMotionFunc(mouseMovement);
	glutIdleFunc(idle);


	// Enter GLUT loop.
	glutMainLoop();
}
*/
