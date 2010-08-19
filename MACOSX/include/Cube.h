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

void solidCube(GLdouble size, GLuint textureID = 0);
#endif