/*
 *  Vector.cpp
 *  Pacman3D
 *
 *  Source: http://www.dreamincode.net/code/snippet3151.htm
 *  Copyright 2010 Concordia University. All rights reserved.
 *
 *  Modified by bronson
 */
#ifdef __APPLE__ /* OS X */
#include "Vector.h"
#elif defined(__linux__) /* LINUX */
#include "../include/Vector.h"
#else /* WINDOWS */
#include "../include/Vector.h"
#endif

Vector::Vector():
x(0), y(0), z(0)
{
}

Vector::Vector(GLdouble pX, GLdouble pY, GLdouble pZ):
x(pX), y(pY), z(pZ)
{
}

GLdouble Vector::getMagnitude() const
{
	GLdouble magnitude = sqrt(x*x+y*y+z*z);
	return magnitude;
}

void Vector::normalize()
{
    GLdouble length = this->getMagnitude();

    this->setX(this->getX()/length);
    this->setY(this->getY()/length);
    this->setZ(this->getZ()/length);
}

GLdouble Vector::dot( const Vector &other ) const
{
    return (getX() * other.getX() + getY() * other.getY() + getZ() * other.getZ());
}

Vector Vector::operator+ ( const Vector &other ) const
{
    Vector result(this->x + other.getX(), this->y + other.getY(), this->z + other.getZ());
    return result;
}

void Vector::operator+= ( Vector other )
{
    this->x += other.getX();
    this->y += other.getY();
    this->z += other.getZ();
}

Vector Vector::operator- ( const Vector &other ) const
{
    Vector result(this->x - other.getX(), this->y - other.getY(), this->z - other.getZ());
    return result;
}

Vector Vector::operator- () const
{
    Vector result(-this->x, -this->y, -this->z);
    return result;
}

void Vector::operator-= ( Vector other )
{
    this->x -= other.getX();
    this->y -= other.getY();
    this->z -= other.getZ();
}

Vector Vector::operator* ( const GLfloat amount ) const
{
    Vector result(this->x * amount, this->y * amount, this->z * amount);
    return result;
}

void Vector::operator= ( Vector other )
{
    this->x = other.getX();
    this->y = other.getY();
    this->z = other.getZ();
}

void Vector::set( const Vector &other )
{
    this->x = other.getX();
    this->y = other.getY();
    this->z = other.getZ();
}