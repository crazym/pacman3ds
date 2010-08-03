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
    
    void setLightPosition(GLfloat* position, GLfloat* direction); // position of the light
    void setModelPosition(GLfloat* position);
    void setAmbDiffSpec(GLfloat* ambient, GLfloat* diffuse, GLfloat* specular);
    void draw();
    void turnOn();
    void turnOff();
    
    bool isOn;
    //bool firstTime; //used as a hack to fix an annoying bug
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
