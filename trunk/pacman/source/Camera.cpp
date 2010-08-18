/*
 *  Camera.cpp
 *  Pacman3D
 *
 *  Created by bronson on 10-08-10.
 *  Copyright 2010 Concordia University. All rights reserved.
 *
 *
 *  Reference: http://nehe.gamedev.net/data/articles/article.asp?article=08
 */

#include "Camera.h"
#include "Vector.h"
#include "Common.h"

#include <cmath>
#include <iostream>

#define radians 0.0174532925

const GLdouble initial_eye[3] = {14.0, 30.0, 35.0};
const GLdouble initial_center[3] = {14.0, 2.0, 11.0};
const GLdouble initial_up[3] = {0.0, 1.0, 0.0};

Camera::Camera(GLuint fixed)
{
    this->fixed = fixed;
    reset();
}

void Camera::reset()
{
    this->up.setX(initial_up[0]);
    this->up.setY(initial_up[1]);
    this->up.setZ(initial_up[2]);
    
    this->position.setX(initial_eye[0]);
    this->position.setY(initial_eye[1]);
    this->position.setZ(initial_eye[2]);
    
    this->center.setX(initial_center[0]);
    this->center.setY(initial_center[1]);
    this->center.setZ(initial_center[2]);
    
    this->yRotation = 85;
    this->zRotation = 40;
    
    this->pitchAmount = 0;
    this->yawAmount = 0;
    this->rollAmount = 85;

    this->fovy = 60;
    this->nearPlane = 1.5;
    this->farPlane = 120;
    
    //setViewport();
}


void Camera::setViewport()
{
    // Must set it up in Projection Matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
    
    gluPerspective(this->fovy, (GLfloat) 1.0, this->nearPlane, this->farPlane);
    glMatrixMode(GL_MODELVIEW);
}


void Camera::look()
{
    gluLookAt(this->position.getX(), this->position.getY(), this->position.getZ(),  
              this->center.getX(), this->center.getY(), this->center.getZ(),
              this->up.getX(), this->up.getY(), this->up.getZ());
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
    /*
    Vector target(center.getX() - this->position.getX(),
                  center.getY() - this->position.getY(),
                  center.getZ() - this->position.getZ());
    
    return target.getMagnitude();
     */
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
void Camera::roll(GLfloat amount)
{
    if (this->fixed) {
        return;
    }
    
    Vector newUp;
    
    GLfloat radius = 1;
    
    this->rollAmount += amount;
    if (this->rollAmount > 359) {
        this->rollAmount = 0;
    }
    
    /* calculate the vector using circle equation: 
     x = a + r cos t
     y = b + r sin t
     
     where: x,y are the new position; a,b is the center of the circle; t is the
     angle formed from the origin to x,y and the x-axis.
     */
    newUp.setX( this->up.getX() + radius * cos(this->rollAmount*radians) );
    newUp.setY( this->up.getY() + radius * sin(this->rollAmount*radians) );
    newUp.setZ( 0 );
    
    newUp.normalize();
    setUp(newUp);
}

void Camera::pitch(GLfloat amount)
{
    if (this->fixed) {
        return;
    }
    
    Vector newUp;
    Vector newCenter;
    
    GLfloat radius = 1;
    
    this->pitchAmount += amount;
    if (this->pitchAmount > 359 || this->pitchAmount < -359) 
    {
        this->pitchAmount = 0;
    }
    
    newUp.setX( this->up.getX() );
    newUp.setY( /*this->up.getY()* +*/ radius * cos(this->pitchAmount*radians) );
    newUp.setZ( /*this->up.getZ() - */ radius * sin(this->pitchAmount*radians) );
    
    newUp.normalize();
    
    newCenter.setX( this->center.getX() );
    newCenter.setY( this->center.getY() - getDistance() * cos(this->pitchAmount*radians) );
    newCenter.setZ( this->center.getZ() - getDistance() * sin(this->pitchAmount*radians) );
    
    setUp(newUp);
    setCenter(newCenter);
    
    cout << newUp << endl;
    
    cout << newCenter << endl;
    
    cout << pitchAmount << endl;
}

void Camera::yaw(GLfloat amount)
{
    if (this->fixed) {
        return;
    }
    
    Vector newCenter;
    
    GLfloat radius = getDistance();
    
    this->yawAmount += amount;
    if (this->yawAmount > 359) 
    {
        this->yawAmount = 0;
    }
    
    newCenter.setX( this->position.getX() + radius * cos(this->yawAmount*radians) );
    newCenter.setY( this->center.getY() );
    newCenter.setZ( this->position.getZ() + radius * sin(this->yawAmount*radians) );
    
    setCenter(newCenter);
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
    
    setPosition(newPosition);
}


/**********************************/
/* Camera Orbits around Z Axis    */
/**********************************/
void Camera::rotateZ(GLfloat amount)
{
    if (this->fixed) {
        return;
    }
    
    Vector newPosition;    
    
    /* Calculate the radius of the orbit */
    GLfloat x1 = this->position.getY();
    GLfloat y1 = this->position.getZ();
    
    GLfloat x2 = this->center.getY();
    GLfloat y2 = this->center.getZ();
    
    GLfloat radius = sqrt( (x2-x1)*(x2-x1) + (y2-y1)*(y2-y1) );
    
    /* if the rotation surpasses 359 degrees, reset to 0 */
    this->zRotation += amount;
    if (this->zRotation > 359) {
        this->zRotation = 0;
    }
    
    /* calculate the coordinates using circle equation: 
     x = a + r cos t
     y = b + r sin t
     
     where: x,y are the new position; a,b is the center of the circle; t is the
     angle formed from the origin to x,y and the x-axis.
     */
    newPosition.setX( this->position.getX() );
    newPosition.setY( this->center.getY()+ radius * cos(this->zRotation*radians) );
    newPosition.setZ( this->center.getZ()+ radius * sin(this->zRotation*radians) );
    
    setPosition(newPosition);
}
