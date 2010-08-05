/*
 *  Common.cpp
 *  Pacman3D
 *
 *  Created by bronson on 10-07-27.
 *  Copyright 2010 Concordia University. All rights reserved.
 *
 */

#include "Common.h"

#ifdef __APPLE__ /* OS X */
#include <cstdlib>
#include <GLUT/glut.h>
#elif defined(__linux__) /* LINUX */
#include <stdlib.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#else /* WINDOWS */
#include <stdlib.h>
#include <windows.h>
#include <GL/glut.h>
#endif

#include <cmath>

void number()
{
	GLfloat radius  = 0.1;
	GLfloat vectorX = 0.0;
	GLfloat vectorY = 0.0;
    glLineWidth(2.0);
	glBegin(GL_LINE_STRIP);			
	
	for(GLfloat angle = 0.0; angle<=(2.0*3.14159); angle+=0.01)
	{		
		vectorX = (radius*(GLfloat)sin((GLdouble)angle));
		vectorY = (radius*(GLfloat)cos((GLdouble)angle));
		glVertex2d(vectorX,vectorY);	
	}
	glEnd();
    glLineWidth(1.0);
}
