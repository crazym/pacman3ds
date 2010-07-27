/*
 *  walls.cpp
 * 
 *
 *  Created by andrew on 10-07-16.
 *  Copyright 2010 Concordia University. All rights reserved.
 * 	References:
 *				OpenGL SuperBible, Fourth Edition, Wright, Lipchak, Haemel, Addison-Wesley 2007
 */

#ifdef __APPLE__
#include <cstdlib>
#include <GLUT/glut.h>
#else 
#include <stdlib.h>
#include <GL/glut.h>
#endif

////////////////////////////////////////////////////////////////////////////////////////////////
// A unit cube.
void DrawSimpleWall()
{
    
	glPushMatrix();
    
        // Set material color, Blue
        glColor3f(0.0f, 0.0f, 1.0f);
        
        // Front Face ///////////////////////////////////
        glBegin(GL_POLYGON);
        
        // Front Face
        glNormal3f(0.0f, 0.0f, 1.0f);	
        
        glVertex3f(0.0f,0.0f,100.0f);
        glVertex3f(100.0f,0.0f,100.0f);
        glVertex3f(100.0f,100.0f,100.0f);
        glVertex3f(0.0f,100.0f,100.0f);
        glVertex3f(0.0f,0.0f,100.0f);
        
        // Right Side Face
        glNormal3f(1.0f,0.0f, 0.0f);	
        
        glVertex3f(100.0f,0.0f,100.0f);
        glVertex3f(100.0f,0.0f,0.0f);
        glVertex3f(100.0f,100.0f,0.0f);
        glVertex3f(100.0f,100.0f,100.0f);
        glVertex3f(100.0f,0.0f,100.0f);
        
        // Back Face
        glNormal3f(0.0f, 0.0f, -1.0f);	
        
        glVertex3f(100.0f,0.0f,0.0f);
        glVertex3f(0.0f,0.0f,0.0f);
        glVertex3f(0.0f,100.0f,0.0f);
        glVertex3f(100.0f,100.0f,0.0f);
        glVertex3f(100.0f,0.0f,0.0f);
        
        // Left Side Face
        glNormal3f(-1.0f, 0.0f, 0.0f);	
        
        glVertex3f(0.0f,0.0f,0.0f);
        glVertex3f(0.0f,0.0f,100.0f);
        glVertex3f(0.0f,100.0f,100.0f);
        glVertex3f(0.0f,100.0f,0.0f);
        glVertex3f(0.0f,0.0f,0.0f);
        
        // Bottom Face
        glNormal3f(0.0f, -1.0f, 0.0f);	
        
        glVertex3f(0.0f,0.0f,0.0f);
        glVertex3f(100.0f,0.0f,0.0f);
        glVertex3f(100.0f,0.0f,100.0f);
        glVertex3f(0.0f,0.0f,100.0f);
        glVertex3f(0.0f,0.0f,0.0f);
        
        // Top Face
        glNormal3f(0.0f, 1.0f, 0.0f);	
        
        glVertex3f(0.0f,100.0f,100.0f);
        glVertex3f(100.0f,100.0f,100.0f);
        glVertex3f(100.0f,100.0f,0.0f);
        glVertex3f(0.0f,100.0f,0.0f);
        glVertex3f(0.0f,100.0f,100.0f);
        
        glEnd();
	
    glPopMatrix();
    
}