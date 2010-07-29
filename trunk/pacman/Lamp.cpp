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

Lamp::Lamp(GLenum light, GLfloat* direction)
{
    this->light = light;
    this->listID = glGenLists(1);
    
    glLightf(this->light, GL_SPOT_CUTOFF, 45.0);
    glLightfv(this->light, GL_SPOT_DIRECTION, direction);
    
    glNewList(listID, GL_COMPILE);
        glutSolidSphere(1.0, 20, 20);
    glEndList();
}

Lamp::~Lamp()
{
    glDeleteLists(this->listID, 1);
}

void Lamp::setPosition(GLfloat* position)
{
    this->x = position[0];
    this->y = position[1];
    this->z = position[2];    
    
    glLightfv(this->light, GL_POSITION, position);
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
        GLfloat position[] = {this->x, this->y, this->z, 1.0};
        glLightfv(this->light, GL_POSITION, position);

        glPushMatrix();
            glTranslatef(this->x, this->y, this->z);
            glScalef(0.3, 0.3, 0.3);
            glCallList(this->listID);
        glPopMatrix();
    glPopMatrix();
}