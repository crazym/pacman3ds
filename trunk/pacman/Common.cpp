/*
 *  Common.cpp
 *  Pacman3D
 *
 *  Created by bronson on 10-07-27.
 *  Copyright 2010 Concordia University. All rights reserved.
 *
 */

#include "Common.h"

#ifdef __APPLE__
#include <cstdlib>
#include <GLUT/glut.h>
#else 
#include <stdlib.h>
#include <GL/glut.h>
#endif

#include <cmath>

void number()
{
	float radius  = 0.1;
	float vectorX = 0.0;
	float vectorY = 0.0;
    glLineWidth(2.0);
	glBegin(GL_LINE_STRIP);			
	
	for(float angle = 0.0; angle<=(2.0*3.14159); angle+=0.01)
	{		
		vectorX = (radius*(float)sin((double)angle));
		vectorY = (radius*(float)cos((double)angle));
		glVertex2d(vectorX,vectorY);	
	}
	glEnd();
    glLineWidth(1.0);
}
