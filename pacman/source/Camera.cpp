/*
 *  Camera.cpp
 *  Pacman3D
 *
 *  Created by bronson on 10-08-10.
 *  Copyright 2010 Concordia University. All rights reserved.
 *
 *
 *  Reference: http://nehe.gamedev.net/data/articles/article.asp?article=08
 *             http://www.codecolony.de/docs/camera2.htm
 *             http://www.opengl.org/resources/faq/technical/viewing.htm
 */

#ifdef __APPLE__ /* OS X */
#include "Camera.h"
#include "Vector.h"
#include "Common.h"
#elif defined(__linux__) /* LINUX */
#include "../include/Camera.h"
#include "../include/Vector.h"
#include "../include/Common.h"
#else /* WINDOWS */
#include "../include/Camera.h"
#include "../include/Vector.h"
#include "../include/Common.h"
#endif

#include <cmath>
#include <iostream>

#define radians 0.0174532925

const GLdouble initial_eye[3] = {14.0, 30.0, 35.0};
const GLdouble initial_center[3] = {14.0, 2.0, 11.0};

Camera::Camera(GLuint fixed)
{
    this->fixed = fixed;
    reset();
}




/**************************/
/* gluLookAt wrapper      */
/**************************/

void Camera::look( void )
{

    if (!fixed) 
    {
        //The point at which the camera looks:
        Vector viewPoint =  target*(-1*position.getMagnitude());
        
        //as we know the up vector, we can easily use gluLookAt:
        gluLookAt(	position.getX(),position.getY(),position.getZ(),
                  viewPoint.getX(),viewPoint.getY(),viewPoint.getZ(),
                  up.getX(),up.getY(),up.getZ());
    }
    else 
    {
        gluLookAt(this->position.getX(), this->position.getY(), this->position.getZ(),  
                  this->center.getX(), this->center.getY(), this->center.getZ(),
                  0, 1, 0);
    }

}



void Camera::reset()
{
    this->position.setX(initial_eye[0]);
    this->position.setY(initial_eye[1]);
    this->position.setZ(initial_eye[2]);

    this->center.setX(initial_center[0]);
    this->center.setY(initial_center[1]);
    this->center.setZ(initial_center[2]);


    this->target.setX(-0.25293);
    this->target.setY(0.781285);
    this->target.setZ(0.570632);
    
    this->right.setX(-0.967043);
    this->right.setY(-0.20254);
    this->right.setZ(-0.151522);
    
    this->up.setX(0.00280574);
    this->up.setY(0.5904);
    this->up.setZ(-0.807106);
    

    this->yRotation = 85;
    this->zRotation = 40;
	this->xRotation = 0;

    this->fovy = 60;
    this->nearPlane = 1.5;
    this->farPlane = 120;
}


void Camera::setViewport()
{
    // Must set it up in Projection Matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

    gluPerspective(this->fovy, (GLfloat) 1.0, this->nearPlane, this->farPlane);
    glMatrixMode(GL_MODELVIEW);
}



void Camera::setPosition(const Vector &position)
{
    this->position.setX(position.getX());
    this->position.setY(position.getY());
    this->position.setZ(position.getZ());
}


void Camera::setPosition(GLfloat x, GLfloat y, GLfloat z)
{
    Vector pos(x, y, z);
    setPosition(pos);
}


void Camera::setUp(const Vector &up)
{
    this->up.setX(up.getX());
    this->up.setY(up.getY());
    this->up.setZ(up.getZ());
    this->up.normalize();
}


void Camera::setUp(GLfloat x, GLfloat y, GLfloat z)
{
    Vector up(x, y, z);
    setUp(up);
}


void Camera::setCenter(const Vector &center)
{
    this->center.setX(center.getX());
    this->center.setY(center.getY());
    this->center.setZ(center.getZ());
}


void Camera::setCenter(GLfloat x, GLfloat y, GLfloat z)
{
    Vector center(x, y, z);

    setCenter(center);
}

/* Returns Distance from center to position */
GLfloat Camera::getDistance()
{
    GLfloat xd = center.getX() - position.getX();
    GLfloat yd = center.getY() - position.getY();
    GLfloat zd = center.getZ() - position.getZ();

    return sqrt(xd*xd + yd*yd + zd*zd);
}

/* Returns Target Vector */
Vector Camera::getTarget()
{
    Vector target(center.getX() - this->position.getX(),
                  center.getY() - this->position.getY(),
                  center.getZ() - this->position.getZ());

    target.normalize();

    return target;
}

/* Returns Right Vector */
Vector Camera::getRight()
{
    Vector right = crossProduct(getTarget(), this->up);
    right.normalize();
    return right;
}


void Camera::moveForward(GLfloat amount)
{
    if (this->fixed) {
        return;
    }

    this->position.setZ(this->position.getZ() - amount);

    /* recalculate center */
    this->center.setZ(this->center.getZ() - amount);
}


void Camera::moveBackward(GLfloat amount)
{
    if (this->fixed) {
        return;
    }

    this->position.setZ(this->position.getZ() + amount);

    /* recalculate center */
    this->center.setZ(this->center.getZ() + amount);
}


void Camera::moveLeft(GLfloat amount)
{
    if (this->fixed) {
        return;
    }

    this->position.setX(this->position.getX() - amount);

    /* recalculate center */
    this->center.setX(this->center.getX() - amount);
}


void Camera::moveRight(GLfloat amount)
{
    if (this->fixed) {
        return;
    }

    this->position.setX(this->position.getX() + amount);

    /* recalculate center */
    this->center.setX(this->center.getX() + amount);
}


void Camera::zoomIn(GLfloat amount)
{
    if (this->fixed) {
        return;
    }

    Vector increment;
    increment = getTarget() * amount;
    increment.normalize();

    this->position += increment;

    /* recalculate center */
    Vector newCenter = getTarget() * getDistance();
    newCenter += this->position;

    setCenter(newCenter);
}

void Camera::zoomWithFovy(GLfloat amount)
{
    this->fovy += amount;
    setViewport();
}


void Camera::zoomOut(GLfloat amount)
{
    if (this->fixed) {
        return;
    }

    Vector increment;
    increment = getTarget() * amount;
    increment.normalize();

    this->position -= increment;

    /* recalculate center */
    Vector newCenter = getTarget() * getDistance();
    newCenter += this->position;

    setCenter(newCenter);
}

/**************************/
/* Camera Rolls Around Z  */
/**************************/
//ROLL
void Camera::roll (GLfloat angle)
{
    if (this->fixed) {
        return;
    }
	
	//Rotate viewdir around the right vector:
	right = (right*cos(angle*radians) + up*sin(angle*radians));
	right.normalize();

	//now compute the new UpVector (by cross product)
	up = crossProduct(target, right)*(-1);
}






/**************************/
/* Camera Rolls Around Y  */
/**************************/
//YAW
void Camera::yaw (GLfloat angle)
{
    if (this->fixed) {
        return;
    }
	
	//Rotate viewdir around the up vector:
	target = (target*cos(angle*radians) - right*sin(angle*radians));
	target.normalize();

	//now compute the new RightVector (by cross product)
	right = crossProduct(target, up);
    
    cout << target << endl;
    cout << right << endl;
    cout << up << endl;
}




/**************************/
/* Camera Rolls Around X  */
/**************************/
//PITCH
void Camera::pitch (GLfloat angle)
{
    if (this->fixed) {
        return;
    }
	//this->pitchAmount += angle;
	
	//Rotate viewdir around the right vector:
	target = (target*cos(angle*radians)+ up*sin(angle*radians));
	target.normalize();

	//now compute the new UpVector (by cross product)
	up = crossProduct(target, right)*(-1);
}


/*********************************/
/*  Camera Orbits around Y Axis  */
/*********************************/
void Camera::rotateY(GLfloat amount)
{
    if (this->fixed) {
        return;
    }

    Vector newPosition;  
    Vector newTarget;

    /* Calculate the radius of the orbit */
    GLfloat x1 = this->position.getX();
    GLfloat y1 = this->position.getZ();

    GLfloat x2 = this->center.getX();
    GLfloat y2 = this->center.getZ();

    GLfloat radius = sqrt( (x2-x1)*(x2-x1) + (y2-y1)*(y2-y1) );

    /* if the rotation surpasses 359 degrees, reset to 0 */
    this->yRotation += amount;
    if (this->yRotation > 359) {
        this->yRotation = 0;
    }

    /* calculate the coordinates using circle equation: 
        x = a + r cos t
        y = b + r sin t
     
     where: x,y are the new position; a,b is the center of the circle; t is the
     angle formed from the origin to x,y and the x-axis.
     */
    newPosition.setX( this->center.getX()+ radius * cos(this->yRotation*radians) );
    newPosition.setY( this->position.getY() );
    newPosition.setZ( this->center.getZ()+ radius * sin(this->yRotation*radians) );

    //yaw(-amount);

    newTarget = this->position - this->center;
    newTarget.normalize();
    this->target = newTarget;
    this->up = Vector(0, 1, 0);
    
    setPosition(newPosition);
}