/*
 *  Pacman.cpp
 * 
 *
 *  Created by carlos on 10-07-16.
 *  Copyright 2010 Concordia University. All rights reserved.
 *  References:
 *   http://users.encs.concordia.ca/~c371_1/skeleton.cpp
 *   http://ozark.hendrix.edu/~burch/cs/490/sched/feb8/
 *   http://www.codersger.de/mags/cscene/CS6/CS6-06.html
 *   http://users.encs.concordia.ca/~c371_1/skeleton.cpp
 */


//#include <stdlib.h>

#ifdef __APPLE__
#include <cstdlib>
#include <GLUT/glut.h>
#else 
#include <stdlib.h>
#include <GL/glut.h>
#endif

#include <cmath>

extern GLfloat mat_diffuse[];
extern GLfloat mat_ambient_color[];

//#include <iostream>
//#include <sstream>
//#include <iomanip>

/*
//GLOBAL Variables---------------------------------------
	// Initial size of graphics window.
	const int WIDTH  = 600;
	const int HEIGHT = 400;

	// Current size of window.
	int width  = WIDTH;
	int height = HEIGHT;

	// Mouse positions, normalized to [0,1].
	double xMouse = 0.5;
	double yMouse = 0.5;

	// Bounds of viewing frustum.
	double nearPlane =  2;
	double farPlane  = 20;

	// Viewing angle.
	double fovy = 100.0;

	// Variables.
	double alpha = 0.0;                   // Set by mouse X.
	double beta = 0.0;                    // Set by mouse Y.
	//double gamma = 0.0;                   // Set by mouse Z.
	double distance = - (farPlane + nearPlane) / 2;   
//--------------------------------------------------------
*/
void number8()
{
	float radius = 1.0;
	float vectorX = 0.0;
	float vectorY = 0.0;
    glLineWidth(3.0);
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

void hemisphere(double r, int lats, int longs) 
{
	int i, j;
	for(i = 1; i <= lats; i++) 
	{
		double lat0 = 3.14159265 * (-0.5 + (double) (i - 1) / lats);
		double z0  = r*sin(lat0);
		double zr0 =  r*cos(lat0);
    
		double lat1 = 3.14159265 * (-0.5 + (double) i / lats);
		double z1 = r*sin(lat1);
		double zr1 = r*cos(lat1);
    
		//changing the longs +1 to -5 opens pacmans mouth
		glBegin(GL_QUAD_STRIP);
		for(j = 0; j <= longs; j++) 
		{
			double lng = 2*3.14159265 * (double) (j - 1) / longs/2;
			double x = r*cos(lng);
			double y = r*sin(lng);
    
			//glNormal3f(x * zr0, y * zr0, r*z0);
			glVertex3f(x * zr0, y * zr0, r*z0);
			//glNormal3f(x * zr1, y * zr1, r*z1);
			glVertex3f(x * zr1, y * zr1, r*z1);
		}
		glEnd();
	}
}

void top_pacman(double r, int lats, int longs) 
{
	int i, j;
	for(i = 1; i <= lats; i++) 
	{
		double lat0 = 3.14159265 * (-0.5 + (double) (i - 1) / lats);
		double z0  = r*sin(lat0);
		double zr0 =  r*cos(lat0);
    
		double lat1 = 3.14159265 * (-0.5 + (double) i / lats);
		double z1 = r*sin(lat1);
		double zr1 = r*cos(lat1);
    
		//changing the longs +1 to -5 opens pacmans mouth
		glBegin(GL_QUAD_STRIP);
		for(j = 0; j <= longs-6; j++) 
		{
			double lng = 2*3.14159265 * (double) (j - 1) / longs/2;
			double x = r*cos(lng);
			double y = r*sin(lng);
    
			glNormal3f(x * zr0, y * zr0, r*z0);
			glVertex3f(x * zr0, y * zr0, r*z0);
			glNormal3f(x * zr1, y * zr1, r*z1);
			glVertex3f(x * zr1, y * zr1, r*z1);
		}
		glEnd();
	}
}

void palate(double r)
{
	float radius = r;
	float vectorX = 0.0;
	float vectorY = 0.0;
	glBegin(GL_POLYGON);			
	for(float angle = 3.14159/2; angle>=(-3.14159/2); angle-=0.01)
	{		
		vectorX = (radius*(float)sin((double)angle));
		vectorY = (radius*(float)cos((double)angle));
		glVertex2d(vectorX,vectorY);	
	}
	glEnd();
}

void bottom_pacman(double r, int lats, int longs) 
{
	int i, j;
	for(i = 1; i <= lats; i++) 
	{
		double lat0 = 3.14159265 * (-0.5 + (double) (i - 1) / lats);
		double z0  = r*sin(lat0);
		double zr0 =  r*cos(lat0);
    
		double lat1 = 3.14159265 * (-0.5 + (double) i / lats);
		double z1 = r*sin(lat1);
		double zr1 = r*cos(lat1);
    
		glBegin(GL_QUAD_STRIP);
		for(j = 1; j <= longs-5; j++) 
		{
			double lng = -2*3.14159265 * (double) (j - 1) / longs/2;
			double x = r*cos(lng);
			double y = r*sin(lng);
    
			glNormal3f(x * zr0, y * zr0, r*z0);
			glVertex3f(x * zr0, y * zr0, r*z0);
			glNormal3f(x * zr1, y * zr1, r*z1);
			glVertex3f(x * zr1, y * zr1, r*z1);
		}
		glEnd();
	}
}

void pupil()
{
	glPushMatrix();
	glColor3f(255, 255, 255);
	hemisphere(1, 8, 8);
	glPopMatrix();
}

void retina()
{
	glPushMatrix();
	glColor3f(0, 0, 0);
	hemisphere(0.6, 8, 8);
	glPopMatrix();
}

void DrawPacman()
{
	//Top and bottom parts of Pacman--
    glPushMatrix();
        glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient_color);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
		glColor3f(1, 1, 0);
		glTranslated(0.0, 0.0, 0.0);
		glRotatef(90, 0.0, 1, 0.0);
		top_pacman(2, 40, 40);
		bottom_pacman(2, 40, 40);
    glPopMatrix();
	//--------------------------------
	//Palate--------------------------
		glPushMatrix();
		glColor3f(1, 0, 0);	
		glRotatef(58, 1, 0, 0.0);
		glTranslated(0.0, 0.0, 0.0);
		palate(4.0);
		glPopMatrix();
	//--------------------------------
	//Bottom of mouth-----------------
		glPushMatrix();
		glColor3f(1, 0, 0);	
		glRotatef(116, 1, 0, 0.0);
		glTranslated(0.0, 0.0, 0.0);
		palate(4.0);
		glPopMatrix();
	//--------------------------------
	//Pupils--------------------------
		//Right Pupil-----------------
			glPushMatrix();
			glTranslated(1.3, 2.4, 2);
			glRotatef(70, 1, 0, 0);
			glRotatef(80, 0, 1, 0);
			glTranslated(0.0, 0.0, 0.0);
			pupil();
			glPopMatrix();
		//----------------------------

		//Left Pupil------------------
			glPushMatrix();
			glTranslated(-1.3, 2.4, 2);
			glRotatef(70, 1, 0, 0);
			glRotatef(80, 0, 1, 0);
			glTranslated(0.0, 0.0, 0.0);
			pupil();
			glPopMatrix();
		//----------------------------
	//--------------------------------
	//Retina--------------------------
		//Right Retina----------------
			glPushMatrix();
			glTranslated(1.2, 2.7, 2.8);
			glRotatef(70, 1, 0, 0);
			glRotatef(80, 0, 1, 0);
			glTranslated(0.0, 0.0, 0.0);
			retina();
			glPopMatrix();
		//----------------------------

		//Left Retina-----------------
			glPushMatrix();
			glTranslated(-1.2, 2.7, 2.8);
			glRotatef(70, 1, 0, 0);
			glRotatef(80, 0, 1, 0);
			glTranslated(0.0, 0.0, 0.0);
			retina();
			glPopMatrix();
		//----------------------------
	//--------------------------------
	//Group Number--------------------
		//Top part of number 8--------
			glPushMatrix();
			glColor3f(0, 0, 0);
			glTranslated(0, 3.9, 0);
			glRotatef(90, 1, 0, 0);
			glTranslated(0.0, 0.0, 0.0);
			number8();
			glPopMatrix();
		//----------------------------
		//Bottom part of number 8-----
			glPushMatrix();
			glColor3f(0, 0, 0);
			glTranslated(0, 3.4, -1.9);
			glRotatef(-120, 1, 0, 0);
			glTranslated(0.0, 0.0, 0.0);
			number8();
			glPopMatrix();
		//----------------------------

}

/*

void display ()
{
	//Initializing-----------------------------
 	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	//Translation
	glTranslatef(0, 0, distance);

	// Rotation using x mouse.
	alpha = 720.0 * yMouse;
	glRotatef(alpha, 1, 0, 0);

	// Rotation using Y mouse.
	beta = 720.0 * xMouse;
	glRotatef(beta, 0, 1, 0);	

		// Draw model axes.---------------------
		glPushMatrix();
		glBegin(GL_LINES);
		// X axis
		glColor3f(1, 0, 0);//red
		glVertex3f(0, 0, 0);
		glVertex3f(8, 0, 0);
		// Y axis
		glColor3f(0, 1, 0);
		glVertex3f(0, 0, 0);
		glVertex3f(0, 8, 0);
		// Z axis
		glColor3f(0, 0, 1);
		glVertex3f(0, 0, 0);
		glVertex3f(0, 0, 8);
		glEnd();
		glPopMatrix();
		//---------------------------------------
	//-------------------------------------------

	//Pacman-------------------
	DrawPacman();
	//-------------------------

	//-------------------------
	//Disabling Flickering
	glutSwapBuffers();
	//-------------------------

	
}

void reshapeMainWindow (int newWidth, int newHeight)
{
	width = newWidth;
	height = newHeight;
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(fovy, GLfloat(width) / GLfloat(height), nearPlane, farPlane);
}

void mouseMovement (int mx, int my)
{
	// Normalize mouse coordinates.
	xMouse = double(mx) / double(width);
	yMouse = 1 - double(my) / double(height);

	// Redisplay image.
	glutPostRedisplay();
}

int main3(int argc, char **argv)
{
	// GLUT initialization.
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(width, height);
	glutCreateWindow("GLUT Skeleton Program");

	// Register call backs.
	glutDisplayFunc(display);
	glutReshapeFunc(reshapeMainWindow);
	//glutKeyboardFunc(graphicKeys);
	//glutSpecialFunc(functionKeys);
	glutMotionFunc(mouseMovement);

	// Enter GLUT loop.
	glutMainLoop();
}
*/

