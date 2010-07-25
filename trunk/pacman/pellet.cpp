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

void drawPellet(){

// Draw a pellet.
    
       glPushMatrix();
       	glColor3f(0.96, 0.933, 0.545);
    	glutSolidSphere(1, 20, 20);
       glPopMatrix();

}
