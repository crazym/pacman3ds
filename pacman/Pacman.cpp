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


#include "Pacman.h"
#include "Common.h"

#include <cmath>
#include <iostream>

using namespace std;

Pacman::Pacman()
{
#ifdef DEBUG
    cout << "Allocating Pacman" << endl;
#endif
    this->listID = glGenLists(1);
    glNewList(listID, GL_COMPILE);

   	//Top and bottom parts of Pacman--
    glPushMatrix();
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
    glScalef(10.0, 10.0, 10.0);
    number();
    glPopMatrix();
    //----------------------------
    //Bottom part of number 8-----
    glPushMatrix();
    glColor3f(0, 0, 0);
    glTranslated(0, 3.4, -1.9);
    glRotatef(-120, 1, 0, 0);
    glScalef(10.0, 10.0, 10.0);
    number();
    glPopMatrix();
    //----------------------------
    
    glEndList();
}

Pacman::~Pacman()
{
#ifdef DEBUG
    cout << "Deallocating Pacman" << endl;
#endif
    glDeleteLists(this->listID, 1);
}

void Pacman::initPosition(GLfloat x, GLfloat y, GLfloat z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

void Pacman::draw()
{
    glPushMatrix();
    glTranslatef(this->x, this->y, this->z);
    glScalef(0.125, 0.125, 0.125);
    glCallList(this->listID);
    glPopMatrix();
}


void Pacman::hemisphere(double r, int lats, int longs) 
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


void Pacman::top_pacman(double r, int lats, int longs) 
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

void Pacman::palate(double r)
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

void Pacman::bottom_pacman(double r, int lats, int longs) 
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

void Pacman::pupil()
{
	glPushMatrix();
	glColor3f(255, 255, 255);
	hemisphere(1, 8, 8);
	glPopMatrix();
}

void Pacman::retina()
{
	glPushMatrix();
	glColor3f(0, 0, 0);
	hemisphere(0.6, 8, 8);
	glPopMatrix();
}
