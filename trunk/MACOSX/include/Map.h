/*
 *  Map.h
 *  Pacman3D
 *
 *  Created by bronson on 10-07-27.
 *  Copyright 2010 Concordia University. All rights reserved.
 *
 */
#ifndef _MAP_H_
#define _MAP_H_

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

#include <vector>

using namespace std;

class Tile;

class Map {
public:
	Map();
    Map(char* map, GLint rows, GLint columns);
    ~Map();
    
    void initializeMap(char* map, GLint rows, GLint columns);
    void draw(GLint texturePellets, GLint texturePPellets);
    
    vector<Tile*> tiles;
    GLint size;
    GLint rows;
    GLint columns;
    
    char *mapArray;
    
};
#endif