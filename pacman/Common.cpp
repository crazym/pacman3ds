/*
 *  Common.cpp
 *  Pacman3D
 *
 *  Created by bronson, carlos on 10-07-27.
 *  Copyright 2010 Concordia University. All rights reserved.
 *
 *  Reference: http://nehe.gamedev.net/data/lessons/lesson.asp?lesson=30
 */

#include "Common.h"
#include "Vector.h"
#include "Tile.h"

#include <cmath>
#include <iostream>

#define EPSILON 1.0e-8
#define ZERO EPSILON

/* How close pacman has to be to collide with a wall when turning */
const GLfloat PACMAN_LEEWAY = 0.7;

void number0();
void number1();
void number2();
void number3();
void number4();
void number5();
void number6();
void number7();
void number8();
void number9();

void number(char num = 8)
{
	switch(num){


	case 1 :
		number1();
		break;

	case 2 :
		number2();
		break;

	case 3 :
		number3();
		break;

	case 8 :
		number8();
		break;

	case 4 :
		number4();
		break;

	case 5 :
		number5();
		break;

	case 6 :
		number6();
		break;

	case 7 :
		number7();
		break;

	case 9 :
		number9();
		break;

	}

}


void number1(){

	glBegin(GL_LINE_STRIP);

		glVertex2f(0.5,0);
		glVertex2f(0.5,1);
		glVertex2f(0.25,0.75);

	glEnd();
}

void number2(){

	glBegin(GL_LINE_STRIP);

			glVertex2f(1,0);
			glVertex2f(0,0);
			glVertex2f(0,0.5);
			glVertex2f(1,0.5);
			glVertex2f(1,1);
			glVertex2f(0,1);

	glEnd();

}

void number3(){

	glBegin(GL_LINE_STRIP);

			glVertex2f(0,0);
			glVertex2f(1,0);
			glVertex2f(1,0.5);
			glVertex2f(0,0.5);
			glVertex2f(1,0.5);
			glVertex2f(1,1);
			glVertex2f(0,1);

	glEnd();
}


void number4(){

	glBegin(GL_LINE_STRIP);

			glVertex2f(0.75,0);
			glVertex2f(0.75,1);
			glVertex2f(0,0.25);
			glVertex2f(1,0.25);

	glEnd();
}

void number5(){

	glBegin(GL_LINE_STRIP);

				glVertex2f(0,0);
				glVertex2f(1,0);
				glVertex2f(1,0.5);
				glVertex2f(0,0.5);
				glVertex2f(0,1);
				glVertex2f(1,1);

		glEnd();

}

void number6(){

	glBegin(GL_LINE_STRIP);

				glVertex2f(1,1);
				glVertex2f(0,1);
				glVertex2f(0,0);
				glVertex2f(1,0);
				glVertex2f(1,0.5);
				glVertex2f(0,0.5);

		glEnd();
}

void number7(){

	glBegin(GL_LINE_STRIP);

				glVertex2f(0,0);
				glVertex2f(1,1);
				glVertex2f(0,1);


		glEnd();

}

void number8(){

	glBegin(GL_LINE_STRIP);

				glVertex2f(0,0);
				glVertex2f(1,0);
				glVertex2f(1,0.5);
				glVertex2f(0,0.5);
				glVertex2f(0,1);
				glVertex2f(1,1);
				glVertex2f(1,0.5);
				glVertex2f(0,0.5);
				glVertex2f(0,0);

		glEnd();


}

void number8c(){

		GLfloat radius  = 0.1;
		GLfloat vectorX = 0.0;
		GLfloat vectorY = 0.0;
	    glLineWidth(2.0);
		glBegin(GL_LINE_STRIP);

		for(GLfloat angle = 0.0; angle<=(2.0*3.14159); angle+=0.01)
		{
			vectorX = (radius*(GLfloat)sin((GLdouble)angle));
			vectorY = (radius*(GLfloat)cos((GLdouble)angle));
			glVertex2d(vectorX,vectorY);
		}
		glEnd();
	    glLineWidth(1.0);

}

void number9(){

	glBegin(GL_LINE_STRIP);

				glVertex2f(0,0);
				glVertex2f(1,0);
				glVertex2f(1,1);
				glVertex2f(0,1);
				glVertex2f(0,0.5);
				glVertex2f(1,0.5);

		glEnd();
}

void number0(){

	glBegin(GL_LINE_STRIP);

				glVertex2f(0,0);
				glVertex2f(1,0);
				glVertex2f(1,1);
				glVertex2f(0,1);
				glVertex2f(0,0);

		glEnd();
}

void number(){

	number8c();

}


Vector crossProduct(const Vector& a, const Vector& b)
{
    GLdouble c[3];
    
    c[0] = a.getY() * b.getZ() - b.getY() * a.getZ();
	c[1] = a.getZ() * b.getX() - b.getZ() * a.getX();
	c[2] = a.getX() * b.getY() - b.getX() * a.getY();
    
    Vector result(c[0], c[1], c[2]);
    
    return result;
}

GLdouble dotProduct(const Vector& a, const Vector& b)
{
    GLdouble x = (a.getX() * b.getX());
    GLdouble y = (a.getY() * b.getY());
    GLdouble z = (a.getZ() * b.getZ());
    
    return (x + y + z);
}

/**  Reference: http://nehe.gamedev.net/data/lessons/lesson.asp?lesson=30 **/
GLint TestIntersionPlane(const Plane& plane, const Vector& position, const Vector& direction, GLdouble& lamda)
{
    /* If pacman isn't on (more or less) the same x or z position, return right away */
    //if (!(plane.position.getX() == position.getX() || plane.position.getZ() == position.getZ())) {
    if ( (fabs(plane.position.getX() - position.getX()) > PACMAN_LEEWAY) ||
         (fabs(plane.position.getZ() - position.getZ()) > PACMAN_LEEWAY))
    {
        return 0;
    }
    
    /* Dot Product between the plane normal and ray direction */
	GLdouble theDotProduct = dotProduct(direction, plane.normal);
    
	GLdouble l2;
    
	// Determine If Ray Parallel To Plane
	if ((theDotProduct<ZERO)&&(theDotProduct>-ZERO))
		return 0;
    
    /* Find the distance to the collision point */
    l2 = dotProduct(plane.position-position, plane.normal);
    l2 /= theDotProduct;
    
	if (l2<-ZERO)							// Test If Collision Behind Start
		return 0;

    
	lamda=l2;
	return 1;
}

GLdouble testDistance(const Vector& point1, const Vector& point2)
{
    GLdouble xd = point1.getX() - point2.getX();
    GLdouble zd = point1.getZ() - point2.getZ();
    
    return sqrt((xd * xd) + (zd * zd));
}

void testWallCollision(const Vector& position, const Tile& wall, GLint& n, GLint& s, GLint& e, GLint& w)
{
    GLdouble lambda = 0;
    Vector direction = Vector(-1, 0, 0);
    
    if(TestIntersionPlane(wall.eastPlane, position, direction, lambda))
    {
        if (lambda > 0 && lambda <= 0.5) 
        {
            w = 1;
#ifdef DEBUG
            cout << "Westward Collision with: [" << wall.x << ", " << wall.z << "]" << endl;
#endif
        }
    }
    
    lambda = 0;
    direction = Vector(0, 0, -1);
    
    if (TestIntersionPlane(wall.southPlane, position, direction, lambda))
    {
        if (lambda > 0 && lambda <= 0.5)
        {
            n = 1;
#ifdef DEBUG
            cout << "Northward Collision with: [" << wall.x << ", " << wall.z << "]" << endl;
#endif
        }
    }
    
    lambda = 0;
    direction = Vector(1, 0, 0);
    
    if(TestIntersionPlane(wall.westPlane, position, direction, lambda))
    {
        if (lambda > 0 && lambda <= 0.5) 
        {
            e = 1;
#ifdef DEBUG
            cout << "Eastward Collision with: [" << wall.x << ", " << wall.z << "]" << endl;
#endif
        }
    }
    
    lambda = 0;
    direction = Vector(0, 0, 1);
    
    if(TestIntersionPlane(wall.northPlane, position, direction, lambda))
    {
        if (lambda > 0 && lambda <= 0.5) 
        {
            s = 1;
#ifdef DEBUG
            cout << "Southward Collision with: [" << wall.x << ", " << wall.z << "]" << endl;
#endif
        }
    }    
}
