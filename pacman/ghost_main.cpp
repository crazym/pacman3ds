//
//  main.m
//  cube
//
//  Created by bronson on 10-07-01.
//  Copyright Concordia University 2010. All rights reserved.
//

#include <iostream>
#include <string>
#include <cmath>

#include <GL/glut.h>

//#include "/home/sid/Desktop/computer-graphics/code/models/Ghost.h"
#include "Ghost.h"

using namespace std;

#define KEY_W 119
#define KEY_S 115
#define KEY_A 97
#define KEY_D 100

static Ghost *ghost;
static GLfloat yRotation = 0.0;
static GLfloat xRotation = 0.0;


void init(void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_FLAT);    
    glEnable(GL_DEPTH_TEST);
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	//draw axis lines
	glBegin(GL_LINES);
	      // X axis
	      glColor3f(1, 0, 0);
	      glVertex3f(0, 0, 0);
	      glVertex3f(10, 0, 0);
	      // Y axis
	      glColor3f(0, 1, 0);
	      glVertex3f(0, 0, 0);
	      glVertex3f(0, 10, 0);
	      // Z axis
	      glColor3f(0, 0, 1);
	      glVertex3f(0, 0, 0);
	      glVertex3f(0, 0, 10);
	   glEnd();


    glColor3f(1.0, 1.0, 1.0);
    glPushMatrix();
        glRotatef(yRotation, 0.0, 1.0, 0.0);
        glRotatef(xRotation, 1.0, 0.0, 0.0);
        ghost->draw();
    glPopMatrix();
    
    // Draw a pellet.
       glPushMatrix();
            glRotatef(yRotation, 0.0, 1.0, 0.0);
            glRotatef(xRotation, 1.0, 0.0, 0.0);
            glTranslatef(1.0, 0.5, 2.0);
    	glColor3f(0, 0.5, 1);
    	glutWireSphere(0.2, 20, 20);
        glPopMatrix();

    glutSwapBuffers();
}

void reshape(int w, int h)
{
    glViewport(0.0, 0.0, (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, 1.33, 1.5, 20.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

void key(unsigned char inkey, int px, int py)
{
    int gLastKey = inkey;
    switch (gLastKey) {
        case KEY_A:
            yRotation -= 1;
            break;
        case KEY_D:
            yRotation += 1;
            break;
        case KEY_W:
            xRotation += 1;
            break;
        case KEY_S:
            xRotation -= 1;
            break;
        default:
            cout << "Key: " << gLastKey << endl;
            break;
    }
    glutPostRedisplay();
    
}

int main1(int argc, char *argv[])
{

    glutInit(&argc, (char **)argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);
    init();

    ghost = new Ghost(1.0, 0.0, 0.0, true);

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(key);
    glutMainLoop();
    
    delete ghost;
    
    return 0;
}
