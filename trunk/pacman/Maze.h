

#ifndef  __MAZE_H 
#define __MAZE_H
/*
 *  Maze.h
 * 
 *
 *  Created by andrew on 10-07-16.
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

// These functions create the 4 different walls types required for the modelling assignment #1. 
// Wall1 = Simple straight wall.
// Wall2 = Cross wall.
// Wall3 = T Wall
// Wall4 = Corner walls.

// It was found that when creating the maze that not all walls were necessary and only rotated and translated versions of 
// certain wall types could make all the maze walls.

void DrawWall1();
void DrawWall2();
void DrawWall3();
void DrawWall4();


// These are all the possibilities to have walls. They are just rotates and translated versions of the above wall functions
// so they can fit nicely in the unit layer.

void WallA();
void WallB();
void WallC();
void WallD();
void WallE();
void WallF();
void WallG();
void WallH();
void WallI();
void WallJ();
void WallK();
void WallL();
void WallM();
void WallN();
void WallO();
void WallZ();

// Switch case statement to read the map array and identify which wall type it is.
void DrawMapWall(char c);

// The function that generates the maze by using the function above.
void DrawMaze(char* map);


#endif
