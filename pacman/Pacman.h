/*
 *  Pacman.h
 * 
 *
 *  Created by carlos on 10-07-16.
 *  Copyright 2010 Concordia University. All rights reserved.
 *
 */

#ifndef PACMAN_H_
#define PACMAN_H_

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

void DrawPacman();

class Pacman {
public:
    Pacman();
    ~Pacman();
    
    void draw(GLint outfit = 0);
    
    void initPosition(GLfloat x, GLfloat y, GLfloat z);
    void move();
    void setDirection(char direction);
    void collide(GLint n, GLint s, GLint e, GLint w);
    
    GLfloat x, y, z;
    GLuint textureID[3];
    GLfloat xVelocity;
    GLfloat zVelocity;

private:
    void pacman_1();
    void pacman_2();
    void pacman_3();
    
    void top_pacman(GLdouble r, GLint lats, GLint longs, GLint texture = 0);
    void bottom_pacman(GLdouble r, GLint lats, GLint longs, GLint texture = 0);
    void hemisphere(GLdouble r, GLint lats, GLint longs);
    void palate(GLdouble r);
    void pupil(GLint model = 0);
    void retina();
    
    void drawNumberEight();
    void drawBothRetinas();
    void drawBothPupils(GLint model = 0);
    void drawBothPalates();
};

#endif
