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

#ifdef __APPLE__
#include <cstdlib>
#include <GLUT/glut.h>
#else 
#include <stdlib.h>
#include <GL/glut.h>
#endif

class Tile{
public:
    Tile(char type, GLint x, GLint z);
    
    void draw();
    
    char type;
    bool pellet;
    
    GLint x;
    GLint z;
    
    GLfloat pellet_color[4];
    GLfloat tile_color[4];
};

#endif