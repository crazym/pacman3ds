

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

void WallW();
void WallY();
void WallZ();

// Switch case statement to read the map array and identify which wall type it is.
void DrawMapWall(char c);

// The function that generates the maze by using the function above.
void DrawMaze(char* map);


#endif
