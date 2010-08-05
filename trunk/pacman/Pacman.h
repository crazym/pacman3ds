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
    
    void draw(int outfit = 0);
    void initPosition(GLfloat x, GLfloat y, GLfloat z);
    
    GLfloat x, y, z;
    GLuint listID;
    GLuint textureID[3];

private:
    void top_pacman(double r, int lats, int longs, int texture = 0);
    void bottom_pacman(double r, int lats, int longs, int texture = 0);
    void hemisphere(double r, int lats, int longs);
    void palate(double r);
    void pupil(int model = 0);
    void retina();
};

#endif /* PACMAN_H_ */
