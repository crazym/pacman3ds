/*
 *  Lamp.cpp
 *  Pacman3D
 *
 *  Created by bronson on 10-07-28.
 *  Copyright 2010 Concordia University. All rights reserved.
 *
 */
#ifdef __APPLE__ /* OS X */
#include "Lamp.h"
#include "textures.h"
#elif defined(__linux__) /* LINUX */
#include "../include/Lamp.h"
#include "../include/textures.h"
#else /* WINDOWS */
#include "../include/Lamp.h"
#include "../include/textures.h"
#endif

#include <iostream>

#ifdef __APPLE__ /* OS X */
#define lampTexture "metal.raw"
#elif defined(__linux__) /* LINUX */
#define lampTexture "data/Textures/metal.raw"
#else /* WINDOWS */
#define lampTexture "data/Textures/metal.raw"
#endif

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
    this->isOn = false;
    
    this->textureID = LoadTextureRAW(lampTexture, 1, 64, 64);
    
    this->listID = glGenLists(2);
    this->cylinder = gluNewQuadric();
    
    gluQuadricTexture(this->cylinder, GL_TRUE);
    gluQuadricNormals(this->cylinder, GLU_SMOOTH);
    
    glLightf(this->light, GL_SPOT_CUTOFF, 25.0);
    
    /* List for Pole */
    glNewList(this->listID, GL_COMPILE);

    
    glBindTexture(GL_TEXTURE_2D, this->textureID);
    
    glPushMatrix();
        glColor4fv(pole_color);
        glTranslatef(0.0, 3.0, 0.0);
        glRotatef(90, 1.0, 0.0, 0.0);
        /* The height of the lamp post is 4 */
        gluCylinder(cylinder, 0.2, 0.2, 4.0, 20, 20);
    glPopMatrix();
    
    glEndList();
    
    /* List for Bulb */
    glNewList(this->listID+1, GL_COMPILE);
    glPushMatrix();
        glColor4fv(lamp_color);
        glTranslatef(0.0, 2.8, 0.0);
        glutSolidSphere(0.3, 20, 20);
    glPopMatrix();
    glEndList();
}

Lamp::~Lamp()
{
    glDeleteLists(this->listID, 2);
    gluDeleteQuadric(cylinder);
}

void Lamp::setLightPosition(GLfloat* position, GLfloat* direction)
{
    GLfloat x = position[0];
    GLfloat y = position[1];
    GLfloat z = position[2];
    
    this->lightPosition[0] = x;
    this->lightPosition[1] = y;
    this->lightPosition[2] = z;
    this->lightPosition[3] = 1.0f;
    
    glLightfv(this->light, GL_POSITION, position);
    glLightfv(this->light, GL_SPOT_DIRECTION, direction);
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
    GLint texturesAreEnabled = 0;
    if (glIsEnabled(GL_TEXTURE_2D)) {
        texturesAreEnabled = 1;
    }    
    
    glPushMatrix();
        glPushMatrix();
            glTranslatef(this->x, this->y, this->z);
            //glScalef(0.3, 0.3, 0.3);
            
            glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, pole_ambient_diffuse);
            /* Draw Pole */
            glCallList(this->listID);
    
            glDisable(GL_TEXTURE_2D);
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
    if (texturesAreEnabled) {
        glEnable(GL_TEXTURE_2D);
    }
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