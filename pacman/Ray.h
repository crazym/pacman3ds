/*
 *  Ray.h
 *  Pacman3D
 *
 *  Created by bronson on 10-08-11.
 *  Copyright 2010 Concordia University. All rights reserved.
 *
 *  Reference: http://nehe.gamedev.net/data/lessons/lesson.asp?lesson=30
 */
#ifndef _RAY_H_
#define _RAY_H_

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

class Ray {

public:
    Ray();
    
    Vector position;
    Vector direction;
    
    Vector getPoint(GLfloat t);
    
};

#endif