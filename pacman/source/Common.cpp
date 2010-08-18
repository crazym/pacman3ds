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
#include "Map.h"

#include <cmath>
#include <iostream>

#define EPSILON 1.0e-8
#define ZERO EPSILON

const GLfloat DETECTION_RADIUS = 0.5;


void number()
{
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

void shadow()
{
	GLfloat radius  = 0.8;
	GLfloat vectorX = 0.0;
	GLfloat vectorY = 0.0;
    //glLineWidth(2.0);
	glBegin(GL_POLYGON);			
	
	for(GLfloat angle = 0.0; angle<=(2.0*3.14159); angle+=0.01)
	{		
		vectorX = (radius*(GLfloat)sin((GLdouble)angle));
		vectorY = (radius*(GLfloat)cos((GLdouble)angle));
		glVertex2d(vectorX,vectorY);	
	}
	glEnd();
    //glLineWidth(1.0);
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
GLint TestIntersionPlane(const Plane& plane, const Vector& position, const Vector& direction, GLdouble& lamda, const GLdouble leeway)
{
    /* If character isn't on (more or less) the same x or z position, return right away */
    //if (!(plane.position.getX() == position.getX() || plane.position.getZ() == position.getZ())) {
    if ( (fabs(plane.position.getX() - position.getX()) > leeway) ||
         (fabs(plane.position.getZ() - position.getZ()) > leeway))
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

void testWallCollision(const Vector& position, const Tile& wall, GLint& n, GLint& s, GLint& e, GLint& w, const GLdouble leeway)
{
    GLdouble lambda = 0;
    Vector direction = Vector(-1, 0, 0);
    
    if(TestIntersionPlane(wall.eastPlane, position, direction, lambda, leeway))
    {
        if (lambda > 0 && lambda <= DETECTION_RADIUS) 
        {
            w = 1;
#ifdef DEBUG
            cout << "Westward Collision with: [" << wall.x << ", " << wall.z << "]" << endl;
#endif
        }
    }
    
    lambda = 0;
    direction = Vector(0, 0, -1);
    
    if (TestIntersionPlane(wall.southPlane, position, direction, lambda, leeway))
    {
        if (lambda > 0 && lambda <= DETECTION_RADIUS)
        {
            n = 1;
#ifdef DEBUG
            cout << "Northward Collision with: [" << wall.x << ", " << wall.z << "]" << endl;
#endif
        }
    }
    
    lambda = 0;
    direction = Vector(1, 0, 0);
    
    if(TestIntersionPlane(wall.westPlane, position, direction, lambda, leeway))
    {
        if (lambda > 0 && lambda <= DETECTION_RADIUS) 
        {
            e = 1;
#ifdef DEBUG
            cout << "Eastward Collision with: [" << wall.x << ", " << wall.z << "]" << endl;
#endif
        }
    }
    
    lambda = 0;
    direction = Vector(0, 0, 1);
    
    if(TestIntersionPlane(wall.northPlane, position, direction, lambda, leeway))
    {
        if (lambda > 0 && lambda <= DETECTION_RADIUS) 
        {
            s = 1;
#ifdef DEBUG
            cout << "Southward Collision with: [" << wall.x << ", " << wall.z << "]" << endl;
#endif
        }
    }    
}


GLint getPositionInMapArray(GLint cols, GLint x, GLint z)
{
    return (cols*z + x); 
}

/* If a tile comes back as 1, it's a wall */
void getSurroundingTiles(const Map& theMap, GLint position, GLint& northTile, GLint& southTile, GLint& eastTile, GLint& westTile)
{
    northTile = southTile = eastTile = westTile = 1;
    
    if (theMap.mapArray[position - theMap.columns] != 'W') 
    {
        northTile = 0;
    }
    
    if (theMap.mapArray[position - 1] != 'W') 
    {
        westTile = 0;
    }
    
    if (theMap.mapArray[position + 1] != 'W') 
    {
        eastTile = 0;
    }
    
    if (theMap.mapArray[position + theMap.columns] != 'W') 
    {
        southTile = 0;
    }
}

//functions lifed off the redbook.
void print_stroke_string(void* font, char* s){
   if (s && strlen(s)) {
      while (*s) {
         glutStrokeCharacter(font, *s);
         s++;
      }
   }
   glutPostRedisplay();
}

void print_bitmap_string (void* font, char *string)
{
	int x = 5;
	int y = 5;

	int len, i;
	glRasterPos2f(x, y);
	len = (int) strlen(string);
	for (i = 0; i < len; i++)
	{
	 glutBitmapCharacter(font, string[i]);
	}

	glutPostRedisplay();
}


//wrapper for drwaing string
//makes print_stroke_string easier to use
void drawString(string timeString){

		char * drawString;
		drawString = new char[timeString.length()+1];
		strcpy(drawString,timeString.c_str());

		//print_stroke_string(GLUT_STROKE_ROMAN,drawString);
		print_bitmap_string(GLUT_BITMAP_HELVETICA_18,drawString);
}
