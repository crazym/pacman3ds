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

using namespace std;

Ghost::Ghost():
    red(1.0), green(0.0), blue(0.0)
{
    cout << "Allocating Ghost" << endl;
    initializeModel(true);
}

Ghost::Ghost(GLfloat red, GLfloat green, GLfloat blue, bool isWireframe):
    red(red), green(green), blue(blue)
{
    cout << "Allocating Ghost" << endl;
    initializeModel(isWireframe);
}

Ghost::~Ghost()
{
    cout << "Deallocating Ghost" << endl;
    glDeleteLists(this->listID, 1);
    gluDeleteQuadric(cylinder);
}

void Ghost::initializeModel(bool isWireframe)
{    
    this->listID = glGenLists(1);
    glNewList(listID, GL_COMPILE);
    cylinder = gluNewQuadric();
   
    if (isWireframe) {
        gluQuadricDrawStyle(cylinder, GLU_LINE);
    }
    
    glColor4f(this->red, this->green, this->blue, 0.65);
    glTranslatef(-0.4, -0.4, 0.0);
    
    //Draw the base
    glPushMatrix();
        //Draw first cone
        glPushMatrix();
            glRotatef(90, 1.0, 0.0, 0.0);
            if (isWireframe) {
                glutWireCone(0.3, 0.5, 10, 10);
            } else {
                glutSolidCone(0.3, 0.5, 10, 10);
            }
        glPopMatrix();
    
        //Draw second cone
        glPushMatrix();
            glTranslatef(0.5, 0.0, 0.5);
            glRotatef(90, 1.0, 0.0, 0.0);
            if (isWireframe) {
                glutWireCone(0.3, 0.5, 10, 10);
            } else {
                glutSolidCone(0.3, 0.5, 10, 10);
            }
        glPopMatrix();
    
        //Draw third cone
        glPushMatrix();
            glTranslatef(0.5, 0.0, -0.5);
            glRotatef(90, 1.0, 0.0, 0.0);
        if (isWireframe) {
            glutWireCone(0.3, 0.5, 10, 10);
        } else {
            glutSolidCone(0.3, 0.5, 10, 10);
        }
        glPopMatrix();
    
        //Draw fourth cone
        glPushMatrix();
            glTranslatef(1.0, 0.0, 0.0);
            glRotatef(90, 1.0, 0.0, 0.0);
            if (isWireframe) {
                glutWireCone(0.3, 0.5, 10, 10);
            } else {
                glutSolidCone(0.3, 0.5, 10, 10);
            }
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
        if (isWireframe) {
            glutWireSphere(0.8, 20, 20);
        } else {
            glutSolidSphere(0.8, 20, 20);
        }
    glPopMatrix();
    
    //Draw the eyes
    glPushMatrix();
        glTranslatef(0.0, 0.8, 0.75);
    
        //Draw a white
        glPushMatrix();
            glTranslatef(0.25, 0.0, 0.0);
            glRotatef(-20, 0.0, 1.0, 0.0);
            glScalef(1.0, 1.0, 0.3);
            glColor3f(1.0, 1.0, 1.0);
            if (isWireframe) {
                glutWireSphere(0.2, 20, 20);
            } else {
                glutSolidSphere(0.2, 20, 20);
            }
    
            //Draw its pupil
            glPushMatrix();
                glTranslatef(0.1, 0.0, 0.17);
                glColor3f(0.0, 0.0, 1.0);
                if (isWireframe) {
                    glutWireSphere(0.1, 20, 20);
                } else {
                    glutSolidSphere(0.1, 20, 20);
                }

            glPopMatrix();
        glPopMatrix();
    
    
        //Draw a white
        glPushMatrix();
            glTranslatef(0.75, 0.0, 0.0);
            glRotatef(20, 0.0, 1.0, 0.0);
            glScalef(1.0, 1.0, 0.3);
            glColor3f(1.0, 1.0, 1.0);
            if (isWireframe) {
                glutWireSphere(0.2, 20, 20);
            } else {
                glutSolidSphere(0.2, 20, 20);
            }
    
            //Draw its pupil
            glPushMatrix();
                glTranslatef(0.06, 0.0, 0.17);
                glColor3f(0.0, 0.0, 1.0);
                if (isWireframe) {
                    glutWireSphere(0.1, 20, 20);
                } else {
                    glutSolidSphere(0.1, 20, 20);
                }

            glPopMatrix();
        glPopMatrix();
    glPopMatrix();
    
    glEndList();
    
}

void Ghost::draw()
{
    //cout << "Ghost drawing" << endl;
    glCallList(this->listID);
}
