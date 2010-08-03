/*
 *  Ghost.cpp
 * 
 *
 *  Created by bronson on 10-07-16.
 *  Copyright 2010 Concordia University. All rights reserved.
 *  References:
 *      http://www.opengl.org/documentation/red_book/
 */

#include "Ghost.h"

#include "Common.h"

using namespace std;

extern GLfloat ghost_body[];
extern GLfloat ghost_pupil[];
extern GLfloat ghost_white[];

Ghost::Ghost()
{
    color[0] = 1.0;
    color[1] = 0.0;
    color[2] = 0.0;
    color[3] = 0.65;
    
#ifdef DEBUG
    cout << "Allocating Ghost" << endl;
#endif
    initializeModel();
}

Ghost::Ghost(GLfloat red, GLfloat green, GLfloat blue)
{
    color[0] = red;
    color[1] = green;
    color[2] = blue;
    color[3] = 0.65;
    
#ifdef DEBUG
    cout << "Allocating Ghost" << endl;
#endif
    initializeModel();
}

Ghost::~Ghost()
{
#ifdef DEBUG
    cout << "Deallocating Ghost" << endl;
#endif
    glDeleteLists(this->listID, 1);
    gluDeleteQuadric(cylinder);
}

void Ghost::initializeModel()
{    
    glGenTextures(1, &this->textureID);

    this->listID = glGenLists(1);
    glNewList(listID, GL_COMPILE);
    cylinder = gluNewQuadric();
       
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, ghost_body);
    glColor4fv(color);
    glTranslatef(-0.4, -0.4, 0.0);
    
    //Draw the base
    glPushMatrix();
        //Draw first cone
        glPushMatrix();
            glRotatef(90, 1.0, 0.0, 0.0);
            glutSolidCone(0.3, 0.5, 10, 10);
        glPopMatrix();
    
        //Draw second cone
        glPushMatrix();
            glTranslatef(0.5, 0.0, 0.5);
            glRotatef(90, 1.0, 0.0, 0.0);
            glutSolidCone(0.3, 0.5, 10, 10);
        glPopMatrix();
    
        //Draw third cone
        glPushMatrix();
            glTranslatef(0.5, 0.0, -0.5);
            glRotatef(90, 1.0, 0.0, 0.0);
            glutSolidCone(0.3, 0.5, 10, 10);
        glPopMatrix();
    
        //Draw fourth cone
        glPushMatrix();
            glTranslatef(1.0, 0.0, 0.0);
            glRotatef(90, 1.0, 0.0, 0.0);
            glutSolidCone(0.3, 0.5, 10, 10);
        glPopMatrix();
    
    glPopMatrix();
    
    //Draw the cylindrical body
    glPushMatrix();
        glTranslatef(0.5, 0.78, 0.0);
        glRotatef(90, 1.0, 0.0, 0.0);
        gluCylinder(cylinder, 0.8, 0.8, 0.8, 20, 20);
    glPopMatrix();
    
    //Draw the top spherical head
    glPushMatrix();
        glTranslatef(0.5, 0.8, 0.0);
        glutSolidSphere(0.8, 20, 20);
    glPopMatrix();
    
    //Draw the eyes
    glPushMatrix();
        glTranslatef(0.0, 0.8, 0.75);
    
        //Draw a white
        glPushMatrix();
            glTranslatef(0.25, 0.0, 0.0);
            glRotatef(-20, 0.0, 1.0, 0.0);
            glScalef(1.0, 1.0, 0.3);
            glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, ghost_white);
            glColor4fv(ghost_white);
            glutSolidSphere(0.2, 20, 20);
    
            //Draw its pupil
            glPushMatrix();
                glTranslatef(0.1, 0.0, 0.17);
                glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, ghost_pupil);
                glColor4fv(ghost_pupil);
                glutSolidSphere(0.1, 20, 20);

            glPopMatrix();
        glPopMatrix();
    
    
        //Draw a white
        glPushMatrix();
            glTranslatef(0.75, 0.0, 0.0);
            glRotatef(20, 0.0, 1.0, 0.0);
            glScalef(1.0, 1.0, 0.3);
            glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, ghost_white);
            glColor4fv(ghost_white);
            glutSolidSphere(0.2, 20, 20);
    
            //Draw its pupil
            glPushMatrix();
                glTranslatef(0.06, 0.0, 0.17);
                glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, ghost_pupil);
                glColor4fv(ghost_pupil);
                glutSolidSphere(0.1, 20, 20);

            glPopMatrix();
        glPopMatrix();
    glPopMatrix();
    
    glEndList();
    
}

void Ghost::initPosition(GLfloat x, GLfloat y, GLfloat z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

void Ghost::draw()
{
    //cout << "Ghost drawing" << endl;
    glPushMatrix();
    glTranslatef(this->x, this->y, this->z);
    glScalef(0.6, 0.6, 0.6);
    glCallList(this->listID);
    glPopMatrix();
}
