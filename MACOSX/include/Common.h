/*
 *  Common.h
 *  Pacman3D
 *
 *  Created by bronson on 10-07-27.
 *  Copyright 2010 Concordia University. All rights reserved.
 *
 *  Reference: http://nehe.gamedev.net/data/lessons/lesson.asp?lesson=30
 */
#ifndef _COMMON_H_
#define _COMMON_H_

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

#include "Plane.h"

class Vector;
class Tile;
class Map;
//#define DEBUG


void number();

Vector crossProduct(const Vector& a, const Vector& b);
GLdouble dotProduct(const Vector& a, const Vector& b);
GLint TestIntersionPlane(const Plane& plane, const Vector& position, const Vector& direction, GLdouble& lamda, const GLdouble leeway);
GLdouble testDistance(const Vector& point1, const Vector& point2);
void testWallCollision(const Vector& position, const Tile& wall, GLint& n, GLint& s, GLint& e, GLint& w, const GLdouble leeway);
GLint getPositionInMapArray(GLint cols, GLint x, GLint z);
void getSurroundingTiles(const Map& theMap, GLint position, GLint& northTile, GLint& southTile, GLint& eastTile, GLint& westTile);
void shadow();
void print_stroke_string(void* font, char* s);
void print_bitmap_string (void* font, char *string);
void drawString(string timeString);
#endif
