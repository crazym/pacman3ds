/*
 *  Vector.h
 *  Pacman3D
 *
 *  Source: http://www.dreamincode.net/code/snippet3151.htm
 *
 *  Modified by bronson
 *
 *  Copyright 2010 Concordia University. All rights reserved.
 *
 */
#ifndef _VECTOR_H_
#define _VECTOR_H_

#ifdef __APPLE__ /* OS X */
#include <cstdlib>
#include <GLUT/glut.h>
#elif defined(__linux__) /* LINUX */
#include <stdlib.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#else /* WINDOWS */
#include <stdlib.h>
#include <windows.h>
#include <GL/glut.h>
#endif

#include <iostream>
#include <cmath>
using namespace std;

class Vector {
private:
	GLdouble x, y, z;
public:
	explicit Vector();
	explicit Vector(GLdouble pX, GLdouble pY, GLdouble pZ);
	~Vector() {};
	void setX(GLdouble pX)						{ x = pX; };
	void setY(GLdouble pY)						{ y = pY; };
	void setZ(GLdouble pZ)						{ z = pZ; };
    void set( const Vector &other );
	GLdouble getX() const                       { return x; };
	GLdouble getY() const                       { return y; };
	GLdouble getZ() const                       { return z; };
	GLdouble getMagnitude() const; //see below
	
    void normalize();
    GLdouble dot( const Vector &other ) const;
    
    Vector operator+ ( const  Vector &other ) const;
    void operator+= ( Vector other );
    Vector operator- ( const Vector &other ) const;
    Vector operator-() const;
    void operator-= ( Vector other );
    Vector operator* ( const GLfloat amount ) const;
    void operator= ( Vector other );
	
    friend ostream& operator<< (ostream& os, Vector& vect)
	{
		os << "[" << vect.getX() << ", " << vect.getY() << ", " << 
        vect.getZ() << "]";
		return os;
	}
};

#endif