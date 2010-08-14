/*
 *  Tile.h
 *  Pacman3D
 *
 *  Created by bronson on 10-07-27.
 *  Copyright 2010 Concordia University. All rights reserved.
 *
 */
#ifndef _TILE_H_
#define _TILE_H_

#ifdef __APPLE__ /* OS X */
#include <cstdlib>
#include <GLUT/glut.h>
#elif defined(__linux__) /* LINUX */
#include <cstdlib>
#include <GL/glut.h>
#else /* WINDOWS */
#include <stdlib.h>
#include <windows.h>
#include <GL/glut.h>
#endif

#include "Pellet.h"

class Tile{
public:
    Tile(char type, int x, int z);
    Pellet* pellet1;
    
    void draw(int texturePellets, int texturePPellets);
    
    char type;
    GLboolean pellet;
    GLboolean powerPellet;
    
    GLuint floorTextureID;
    GLuint wallTextureID;
    
    GLint x;
    GLint z;
    
    GLfloat tile_color[4];
};

#endif
