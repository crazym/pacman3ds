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

class Ghost {
public:    
    explicit Ghost();
    Ghost(GLfloat red, GLfloat green, GLfloat blue);
    ~Ghost();
    void draw();
    
    void move();
    void chooseMove();
    void setDirection(char direction);
    void collide(GLint n, GLint s, GLint e, GLint w);
    
    void initializeModel();
    void initPosition(GLfloat x, GLfloat y, GLfloat z);
    
    GLuint listID;
    GLuint textureID;
    GLfloat color[4];
    GLfloat x;
    GLfloat y;
    GLfloat z;
    GLfloat xVelocity;
    GLfloat zVelocity;
    
    GLuint myId;

    
private:
    GLUquadricObj *cylinder;
    static GLuint current_id;
};

#endif