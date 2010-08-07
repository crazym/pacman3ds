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
#include <cstdlib>
#include <GL/glut.h>
#else /* WINDOWS */
#include <stdlib.h>
#include <GL/glut.h>
#endif

#include <cmath>

void number0();
void number1();
void number2();
void number3();
void number4();
void number5();
void number6();
void number7();
void number8();
void number9();

void number(char num = 8)
{
	switch(num){


	case 1 :
		number1();
		break;

	case 2 :
		number2();
		break;

	case 3 :
		number3();
		break;

	case 8 :
		number8();
		break;

	case 4 :
		number4();
		break;

	case 5 :
		number5();
		break;

	case 6 :
		number6();
		break;

	case 7 :
		number7();
		break;

	case 9 :
		number9();
		break;

	}

}


void number1(){

	glBegin(GL_LINE_STRIP);

		glVertex2f(0.5,0);
		glVertex2f(0.5,1);
		glVertex2f(0.25,0.75);

	glEnd();
}

void number2(){

	glBegin(GL_LINE_STRIP);

			glVertex2f(1,0);
			glVertex2f(0,0);
			glVertex2f(0,0.5);
			glVertex2f(1,0.5);
			glVertex2f(1,1);
			glVertex2f(0,1);

	glEnd();

}

void number3(){

	glBegin(GL_LINE_STRIP);

			glVertex2f(0,0);
			glVertex2f(1,0);
			glVertex2f(1,0.5);
			glVertex2f(0,0.5);
			glVertex2f(1,0.5);
			glVertex2f(1,1);
			glVertex2f(0,1);

	glEnd();
}


void number4(){

	glBegin(GL_LINE_STRIP);

			glVertex2f(0.75,0);
			glVertex2f(0.75,1);
			glVertex2f(0,0.25);
			glVertex2f(1,0.25);

	glEnd();
}

void number5(){

	glBegin(GL_LINE_STRIP);

				glVertex2f(0,0);
				glVertex2f(1,0);
				glVertex2f(1,0.5);
				glVertex2f(0,0.5);
				glVertex2f(0,1);
				glVertex2f(1,1);

		glEnd();

}

void number6(){

	glBegin(GL_LINE_STRIP);

				glVertex2f(1,1);
				glVertex2f(0,1);
				glVertex2f(0,0);
				glVertex2f(1,0);
				glVertex2f(1,0.5);
				glVertex2f(0,0.5);

		glEnd();
}

void number7(){

	glBegin(GL_LINE_STRIP);

				glVertex2f(0,0);
				glVertex2f(1,1);
				glVertex2f(0,1);


		glEnd();

}

void number8(){

	glBegin(GL_LINE_STRIP);

				glVertex2f(0,0);
				glVertex2f(1,0);
				glVertex2f(1,0.5);
				glVertex2f(0,0.5);
				glVertex2f(0,1);
				glVertex2f(1,1);
				glVertex2f(1,0.5);
				glVertex2f(0,0.5);
				glVertex2f(0,0);

		glEnd();


}

void number8c(){

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

void number9(){

	glBegin(GL_LINE_STRIP);

				glVertex2f(0,0);
				glVertex2f(1,0);
				glVertex2f(1,1);
				glVertex2f(0,1);
				glVertex2f(0,0.5);
				glVertex2f(1,0.5);

		glEnd();
}

void number0(){

	glBegin(GL_LINE_STRIP);

				glVertex2f(0,0);
				glVertex2f(1,0);
				glVertex2f(1,1);
				glVertex2f(0,1);
				glVertex2f(0,0);

		glEnd();
}

void number(){

	number8c();

}

