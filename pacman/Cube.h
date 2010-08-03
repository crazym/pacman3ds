/*
 *  Cube.h
 *  Pacman3D
 *
 *  Created by bronson on 10-08-03.
 *  Copyright 2010 Concordia University. All rights reserved.
 *
 */

#ifndef _CUBE_H_
#define _CUBE_H_

#ifdef __APPLE__
#include <cstdlib>
#include <GLUT/glut.h>
#else 
#include <stdlib.h>
#include <GL/glut.h>
#endif

void solidCube(GLdouble size, GLuint textureID = 0);
#endif