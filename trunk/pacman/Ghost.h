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
    Ghost(GLfloat red, GLfloat green, GLfloat blue, bool isWireframe);
    ~Ghost();
    void draw();
    
    void initializeModel(bool isWireframe);
    
    GLuint listID;
    GLfloat red;
    GLfloat green;
    GLfloat blue;
    
private:
    GLUquadricObj *cylinder;
};

#endif