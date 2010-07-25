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
// Draw the Wall Version 1. Straight Wall.
void DrawWall1()
{

	glPushMatrix();
	 	glTranslatef(0.0f, 0.0f,20.0f);


	 // Set material color, Blue
	 glColor3f(0.0f, 0.0f, 1.0f);

   // Front Face ///////////////////////////////////
	glBegin(GL_POLYGON);

		// Front Face
        glNormal3f(0.0f, 0.0f, 1.0f);

        glVertex3f(0.0f,0.0f,0.0f);
		glVertex3f(100.0f,0.0f,0.0f);
		glVertex3f(100.0f,100.0f,0.0f);
		glVertex3f(0.0f,100.0f,0.0f);
		glVertex3f(0.0f,0.0f,0.0f);

		// Right Side Face
        glNormal3f(1.0f,0.0f, 0.0f);

		glVertex3f(100.0f,0.0f,0.0f);
		glVertex3f(100.0f,0.0f,-20.0f);
		glVertex3f(100.0f,100.0f,-20.0f);
		glVertex3f(100.0f,100.0f,0.0f);
		glVertex3f(100.0f,0.0f,0.0f);

		// Back Face
        glNormal3f(0.0f, 0.0f, -1.0f);

		glVertex3f(100.0f,0.0f,-20.0f);
		glVertex3f(0.0f,0.0f,-20.0f);
		glVertex3f(0.0f,100.0f,-20.0f);
		glVertex3f(100.0f,100.0f,-20.0f);
		glVertex3f(100.0f,0.0f,-20.0f);

		// Left Side Face
        glNormal3f(-1.0f, 0.0f, 0.0f);

		glVertex3f(0.0f,0.0f,0.0f);
		glVertex3f(0.0f,100.0f,0.0f);
		glVertex3f(0.0f,100.0f,-20.0f);
		glVertex3f(0.0f,0.0f,-20.0f);
		glVertex3f(0.0f,0.0f,0.0f);

		// Bottom Face
        glNormal3f(0.0f, -1.0f, 0.0f);

		glVertex3f(0.0f,0.0f,0.0f);
		glVertex3f(0.0f,0.0f,-20.0f);
		glVertex3f(100.0f,0.0f,-20.0f);
		glVertex3f(100.0f,0.0f,0.0f);
		glVertex3f(0.0f,0.0f,0.0f);

		// Top Face
        glNormal3f(0.0f, 1.0f, 0.0f);

		glVertex3f(0.0f,100.0f,0.0f);
		glVertex3f(100.0f,100.0f,0.0f);
		glVertex3f(100.0f,100.0f,-20.0f);
		glVertex3f(0.0f,100.0f,-20.0f);
		glVertex3f(0.0f,100.0f,0.0f);

    glEnd();

	 glPopMatrix();

}


////////////////////////////////////////////////////////////////////////////////////////////////
// Draw the Wall Version 2. Cross Wall.
void DrawWall2()
{
	glPushMatrix();
	 	glTranslatef(0.0f, 0.0f, 40.0f);

		DrawWall1();

		glTranslatef(40.0f, 0.0f, 60.0f);
		glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
	    DrawWall1();
	glPopMatrix();
}

////////////////////////////////////////////////////////////////////////////////////////////////
// Draw the Wall Version 3. T Wall.
void DrawWall3()
{

		DrawWall1();

	glPushMatrix();
		glTranslatef(40.0f, 0.0f, 100.0f);
		glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
	    DrawWall1();
	glPopMatrix();


}

////////////////////////////////////////////////////////////////////////////////////////////////
// Draw the Wall Version 4. Corner Wall.
void DrawWall4()
{
	 DrawWall1();

	 glPushMatrix();
		glTranslatef(0.0f, 0.0f, 100.0f);
		glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
	    DrawWall1();
	glPopMatrix();


}

