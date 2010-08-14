/*
 *  Camera.h
 *  Pacman3D
 *
 *  Created by bronson on 10-08-10.
 *  Copyright 2010 Concordia University. All rights reserved.
 *
 *  Reference: http://nehe.gamedev.net/data/articles/article.asp?article=08
 *
 */
#ifndef _CAMERA_H_
#define _CAMERA_H_

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

#include "Vector.h"

class Camera
{
public:
    Camera();
    
    void reset();
    void look();
   
    void setPosition(const Vector &position);
    void setPosition(GLfloat x, GLfloat y, GLfloat z);
    
    void setUp(const Vector &up);
    void setUp(GLfloat x, GLfloat y, GLfloat z);
    
    void setCenter(const Vector &center);
    void setCenter(GLfloat x, GLfloat y, GLfloat z);
    
    void rotateY(GLfloat amount);
    void rotateZ(GLfloat amount);
    void roll(GLfloat amount);
    
    void moveForward(GLfloat amount);
    void moveBackward(GLfloat amount);
    void moveLeft(GLfloat amount);
    void moveRight(GLfloat amount);
    
    void zoomIn(GLfloat amount);
    void zoomOut(GLfloat amount);
    
    Vector getTarget();
    Vector getRight();
    GLfloat getDistance();
    
    /* points */
    Vector position;
    Vector center;
    
    /* Vectors */
    Vector up;
    
    GLfloat yRotation;
    GLfloat xRotation;
    GLfloat zRotation;
};

#endif