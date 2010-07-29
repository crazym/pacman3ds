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

#ifdef __APPLE__
#include <cstdlib>
#include <GLUT/glut.h>
#else 
#include <stdlib.h>
#include <GL/glut.h>
#endif


class Lamp {
public:
    Lamp(GLenum light, GLfloat* direction);
    ~Lamp();
    
    void setPosition(GLfloat* position);
    void setAmbDiffSpec(GLfloat* ambient, GLfloat* diffuse, GLfloat* specular);
    void draw();
    void turnOn();
    void turnOff();
    
    bool isOn;
    GLuint listID;
    GLenum light;
    GLfloat x;
    GLfloat y;
    GLfloat z;
    
private:
    GLUquadricObj *cylinder;
};

#endif
