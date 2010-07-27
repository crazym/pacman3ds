/*
 *  Pellet.cpp
 * 
 *
 *  Created by sid on 10-07-16.
 *  Copyright 2010 Concordia University. All rights reserved.
 *
 */

#ifdef __APPLE__
#include <cstdlib>
#include <GLUT/glut.h>
#else 
#include <stdlib.h>
#include <GL/glut.h>
#endif

extern GLfloat high_shininess[];
extern GLfloat no_shininess[];

void drawPellet(){
    
    //GLfloat pelletColor[] = {(rand()%255)/255.0f, (rand()%255)/255.0f, (rand()%255)/255.0f};
    
    // Draw a pellet.
    glPushMatrix();
        glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
        glColor3f(0.96, 0.933, 0.545);
        //glColor3fv(pelletColor);
        glutSolidSphere(1, 20, 20);
    glPopMatrix();
    glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);
}
