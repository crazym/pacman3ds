/*
 *  Lamp.h
 *  Pacman3D
 *
 *  Created by bronson on 10-07-28.
 *  Copyright 2010 Concordia University. All rights reserved.
 *
 */

#ifndef LAMP_H_
#define LAMP_H_

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


class Lamp {
public:
    Lamp(GLenum light, GLfloat* direction);
    ~Lamp();
    
    void setLightPosition(GLfloat* position, GLfloat* direction); // position of the light
    void setModelPosition(GLfloat* position);
    void setAmbDiffSpec(GLfloat* ambient, GLfloat* diffuse, GLfloat* specular);
    void draw();
    void turnOn();
    void turnOff();
    
    GLboolean isOn;
    GLuint listID;
    GLuint textureID;
    GLenum light;
    
    GLfloat lightPosition[4];
    
    GLfloat x;
    GLfloat y;
    GLfloat z;
    
private:
    GLUquadricObj *cylinder;
};

#endif
