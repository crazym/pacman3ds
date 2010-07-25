/*
 *  maze.cpp
 * 
 *
 *  Created by andrew on 10-07-16.
 *  Copyright 2010 Concordia University. All rights reserved.
 *
 *	References:
 *				OpenGL SuperBible, Fourth Edition, Wright, Lipchak, Haemel, Addison-Wesley 2007
 */


//#include "Maze.h"
#ifdef __APPLE__
#include <GLUT/glut.h>
#else 
#include <GL/glut.h>
#endif

#include "Floor.h"
#include "Pellet.h"
#include "Walls.h"

// This source code was written by Andrew Wolczak. 


// A predefined map. In later assignments this will be added to a file and read from file input.
// Users will be able to create their own maps. 
//
// This map is half of the original Pacman level. It will be transformed to the full size for the final
// project.

const GLfloat tileZ = 100.0; 

void WallA()
{
	glPushMatrix();
	 	glTranslatef(0.0f, 0.0f, 40.0f);
		DrawWall1();
		//glTranslatef(0.0f,-5.0f,0.0f);
		//drawTile();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0f,-5.0f,tileZ);
	drawTile();
	glPopMatrix();
}

void WallB()
{
	glPushMatrix();

		glTranslatef(40.0f, 0.0f, 100.0f);
		glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
		DrawWall1();
		//glTranslatef(0.0f,-5.0f,0.0f);
		//drawTile();

	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0f,-5.0f,tileZ);
	drawTile();
	glPopMatrix();
}

void WallC()
{
	glPushMatrix();
		DrawWall2();
		//glTranslatef(0.0f,-5.0f,0.0f);
		//drawTile();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0f,-5.0f,tileZ);
	drawTile();
	glPopMatrix();
}

void WallD()
{
	glPushMatrix();
		DrawWall3();
		//glTranslatef(0.0f,-5.0f,0.0f);
		//drawTile();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0f,-5.0f,tileZ);
	drawTile();
	glPopMatrix();
}

void WallE()
{
	glPushMatrix();

		glTranslatef(0.0f, 0.0f, 100.0f);
		glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
		DrawWall3();
		//glTranslatef(0.0f,-5.0f,0.0f);
		//drawTile();

	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0f,-5.0f,tileZ);
	drawTile();
	glPopMatrix();
}

void WallF()
{
	glPushMatrix();
		glTranslatef(100.0f, 0.0f,100.0f);
		glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
		DrawWall3();
		//glTranslatef(0.0f,-5.0f,0.0f);
		//drawTile();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0f,-5.0f,tileZ);
	drawTile();
	glPopMatrix();
}

void WallG()
{
	glPushMatrix();
	 	glTranslatef(100.0f, 0.0f, 0.0f);
		glRotatef(270.0f, 0.0f, 1.0f, 0.0f);
		DrawWall3();
		//glTranslatef(0.0f,-5.0f,0.0f);
		//drawTile();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0f,-5.0f,tileZ);
	drawTile();
	glPopMatrix();
}

void WallH()
{
	glPushMatrix();
		DrawWall4();
		//glTranslatef(0.0f,-5.0f,0.0f);
		//drawTile();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0f,-5.0f,tileZ);
	drawTile();
	glPopMatrix();
}

void WallI()
{
	glPushMatrix();
	 	glTranslatef(100.0f, 0.0f, 0.0f);
		glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
		DrawWall4();
		//glTranslatef(0.0f,-5.0f,0.0f);
		//drawTile();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0f,-5.0f,tileZ);
	drawTile();
	glPopMatrix();
}

void WallJ()
{
	glPushMatrix();
	 	glTranslatef(100.0f, 0.0f, 100.0f);
		glRotatef(-180.0f, 0.0f, 1.0f, 0.0f);
		DrawWall4();
		//glTranslatef(0.0f,-5.0f,0.0f);
		//drawTile();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0f,-5.0f,tileZ);
	drawTile();
	glPopMatrix();
}

void WallK()
{
	glPushMatrix();
	 	glTranslatef(0.0f, 0.0f, 100.0f);
		glRotatef(-270.0f, 0.0f, 1.0f, 0.0f);
		DrawWall4();
		//glTranslatef(0.0f,-5.0f,0.0f);
		//drawTile();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0f,-5.0f,tileZ);
	drawTile();
	glPopMatrix();
}

void WallL()
{
	glPushMatrix();
	 	glTranslatef(0.0f, 0.0f, 100.0f);
		glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
		DrawWall1();
		//glTranslatef(0.0f,-5.0f,0.0f);
		//drawTile();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0f,-5.0f,tileZ);
	drawTile();
	glPopMatrix();
}
void WallM()
{
	glPushMatrix();
	 	glTranslatef(80.0f, 0.0f, 100.0f);
		glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
		DrawWall1();
		//glTranslatef(0.0f,-5.0f,0.0f);
		//drawTile();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0f,-5.0f,tileZ);
	drawTile();
	glPopMatrix();
}

void WallN()
{
	glPushMatrix();
		DrawWall1();
		//glTranslatef(0.0f,-5.0f,0.0f);
		//drawTile();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0f,-5.0f,tileZ);
	drawTile();
	glPopMatrix();
}

void WallO()
{
	glPushMatrix();
	 	glTranslatef(0.0f, 0.0f, 80.0f);
		DrawWall1();
		//glTranslatef(0.0f,-5.0f,0.0f);
		//drawTile();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0f,-5.0f,tileZ);
	drawTile();
	glPopMatrix();
}
void WallY()
{
	// Empty. No wall.
	// no pellet
    
/*	glPushMatrix();
    glColor3f(0,1,1);
    glTranslatef(50.0f,15.0f,60.0f);
    glScalef(20.0, 20.0, 20.0);
    drawPellet();
	glPopMatrix();*/
    
	glPushMatrix();
    glTranslatef(0.0f,-5.0f,tileZ);
    drawTile();
	glPopMatrix();
}
void WallZ()
{
	// Empty. No wall.
	//draw pellet

	glPushMatrix();
		glColor3f(0,1,1);
		glTranslatef(50.0f,15.0f,60.0f);
		 glScalef(20.0, 20.0, 20.0);
		drawPellet();
	glPopMatrix();

	glPushMatrix();
        glTranslatef(0.0f,-5.0f,tileZ);
        drawTile();
	glPopMatrix();
}



void DrawMapWall(char c)
{
	switch (c)
	{
        case 'A':
            WallA();
            break;
        case 'B':
            WallB();
            break;
        case 'C':
            WallC();
            break;
        case 'D':
            WallD();
            break;
        case 'E':
            WallE();
            break;
        case 'F':
            WallF();
            break;
        case 'G':
            WallG();
            break;
        case 'H':
            WallH();
            break;
        case 'I':
            WallI();
            break;
        case 'J':
            WallJ();
            break;
        case 'K':
            WallK();
            break;
        case 'L':
            WallL();
            break;
        case 'M':
            WallM();
            break;
        case 'N':
            WallN();
            break;
        case 'O':
            WallO();
            break;
        case 'Y':
            WallY();
            break;
        case 'Z':
            WallZ();
            break;
	}
}

// The function draws the entire maze.
void DrawMaze(char* map){
    
	glScalef(0.1f,0.1f,0.1f);
    
    int count = 0;
    //char c;
    
    glPushMatrix();
    for(int i = 0 ; i < 483 ; i++)
    {
        
        //c = map[i];
        DrawMapWall(map[i]);
        glTranslatef(100.0f, 0.0f, 0.0f);
        
        count++;
        if(count >= 21)
        {
            glTranslatef(-2100.0f, 0.0f, 100.0f);
            count=0;
        }
        
    }
    glPopMatrix();
    
}

