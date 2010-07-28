/*
 *  Ghost.h
 * 
 *
 *  Created by bronson on 10-07-16.
 *  Copyright 2010 Concordia University. All rights reserved.
 *
 */
#ifndef _GHOST_H_
#define _GHOST_H_

#include <iostream>

#ifdef __APPLE__
#include <cstdlib>
#include <GLUT/glut.h>
#else 
#include <stdlib.h>
#include <GL/glut.h>
#endif

class Ghost {
public:    
    explicit Ghost();
    Ghost(GLfloat red, GLfloat green, GLfloat blue);
    ~Ghost();
    void draw();
    
    void initializeModel();
    void initPosition(GLfloat x, GLfloat y, GLfloat z);
    
    GLuint listID;
    GLfloat red;
    GLfloat green;
    GLfloat blue;
    GLfloat x;
    GLfloat y;
    GLfloat z;
    
private:
    GLUquadricObj *cylinder;
};

#endif