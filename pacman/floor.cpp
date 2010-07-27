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

extern GLfloat low_shininess[];
extern GLfloat no_shininess[];

using namespace std;

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
    glMaterialfv(GL_FRONT, GL_SHININESS, low_shininess);
    
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
    glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);
}