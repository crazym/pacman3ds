/*
 *  Lamp.cpp
 *  Pacman3D
 *
 *  Created by bronson on 10-07-28.
 *  Copyright 2010 Concordia University. All rights reserved.
 *
 */

#include "Lamp.h"
#include <iostream>

extern GLfloat lamp_emission_on[];
extern GLfloat lamp_emission_off[];
extern GLfloat lamp_specular_on[];
extern GLfloat lamp_ambient_diffuse[];
extern GLfloat pole_ambient_diffuse[];
extern GLfloat no_specular[];

Lamp::Lamp(GLenum light, GLfloat* direction)
{
    GLfloat lamp_color[] = { 1.0, 1.0, 0.0, 1.0 };
    GLfloat pole_color[] = { 0.6, 0.6, 0.6, 1.0 };
    
    this->light = light;
    this->listID = glGenLists(2);
    this->isOn = false;
    //this->firstTime = true;
    this->cylinder = gluNewQuadric();
    
    glLightf(this->light, GL_SPOT_CUTOFF, 45.0);
    glLightfv(this->light, GL_SPOT_DIRECTION, direction);
    
    /* List for Pole */
    glNewList(this->listID, GL_COMPILE);
    glPushMatrix();
        glColor4fv(pole_color);
        glRotatef(90, 1.0, 0.0, 0.0);
        gluCylinder(cylinder, 0.2, 0.2, 1.0, 20, 20);
    glPopMatrix();
    glEndList();
    
    /* List for Bulb */
    glNewList(this->listID+1, GL_COMPILE);
    glPushMatrix();
        glColor4fv(lamp_color);
        glTranslatef(0.0, 0.2, 0.0);
        glutSolidSphere(0.3, 20, 20);
    glPopMatrix();
    glEndList();
}

Lamp::~Lamp()
{
    glDeleteLists(this->listID, 2);
    gluDeleteQuadric(cylinder);
}

void Lamp::setLightPosition(GLfloat* position)
{
    GLfloat x = position[0];
    GLfloat y = position[1];
    GLfloat z = position[2];
    
    this->lightPosition[0] = x;
    this->lightPosition[1] = y;
    this->lightPosition[2] = z;
    this->lightPosition[3] = 1.0f;
    
    glLightfv(this->light, GL_POSITION, position);
}

void Lamp::setModelPosition(GLfloat* position)
{
    this->x = position[0];
    this->y = position[1];
    this->z = position[2];
}

void Lamp::setAmbDiffSpec(GLfloat* ambient, GLfloat* diffuse, GLfloat* specular)
{
    glLightfv(this->light, GL_AMBIENT, ambient);
    glLightfv(this->light, GL_DIFFUSE, diffuse);
    glLightfv(this->light, GL_SPECULAR, specular);
}

void Lamp::draw()
{
    glPushMatrix();
        glPushMatrix();
            glTranslatef(this->x, this->y, this->z);
            //glScalef(0.3, 0.3, 0.3);
            
            glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, pole_ambient_diffuse);
            /* Draw Pole */
            glCallList(this->listID);

    
            /* Setup and Draw Bulb */
            if (isOn) {
                glMaterialfv(GL_FRONT, GL_EMISSION, lamp_emission_on);
                glMaterialfv(GL_FRONT, GL_SPECULAR, lamp_specular_on);
            } else {
                glMaterialfv(GL_FRONT, GL_EMISSION, lamp_emission_off);
                glMaterialfv(GL_FRONT, GL_SPECULAR, no_specular);
            }
            glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, lamp_ambient_diffuse);
            glCallList(this->listID+1);
            
            glMaterialfv(GL_FRONT, GL_EMISSION, lamp_emission_off);
            glMaterialfv(GL_FRONT, GL_SPECULAR, no_specular);
        glPopMatrix();

    glPopMatrix();
}

void Lamp::turnOn()
{
    glEnable(this->light);
    this->isOn = true;
}

void Lamp::turnOff()
{
    glDisable(this->light);
    this->isOn = false;
}