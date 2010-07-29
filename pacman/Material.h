/*
 *  Material.h
 *  Pacman3D
 *
 *  Created by bronson on 10-07-27.
 *  Copyright 2010 Concordia University. All rights reserved.
 *  References:
 *      http://www.opengl.org/documentation/red_book/
 */
#ifndef _MATERIAL_H_
#define _MATERIAL_H_

#ifdef __APPLE__
#include <cstdlib>
#include <GLUT/glut.h>
#else 
#include <stdlib.h>
#include <GL/glut.h>
#endif

GLfloat no_mat[]            = { 0.0, 0.0, 0.0, 1.0 };
GLfloat mat_ambient[]       = { 0.5, 0.5, 0.5, 1.0 };
GLfloat mat_ambient_color[] = { 0.8, 0.8, 0.2, 1.0 };
GLfloat mat_diffuse[]       = { 0.1, 0.5, 0.8, 1.0 };
GLfloat mat_specular[]      = { 1.0, 1.0, 1.0, 1.0 };
GLfloat no_specular[]       = { 0.0, 0.0, 0.0, 1.0 };
GLfloat no_shininess[]      = { 0.0 };
GLfloat low_shininess[]     = { 5.0 };
GLfloat high_shininess[]    = { 100.0 };
GLfloat mat_emission[]      = { 0.3, 0.2, 0.2, 0.0 };

GLfloat pacman_body_ambient[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat pacman_body_diffuse[] = { 1.0, 1.0, 0.0, 1.0 };
GLfloat pacman_palate[]       = { 1.0, 0.0, 0.0, 1.0 };
GLfloat pacman_retina[]       = { 0.0, 0.0, 0.0, 1.0 };
GLfloat pacman_pupil[]        = { 1.0, 1.0, 1.0, 1.0 };

GLfloat ghost_body[]  = { 0.75, 0.75, 0.75, 0.65 };
GLfloat ghost_white[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat ghost_pupil[] = { 0.0, 0.0, 1.0, 1.0 };

GLfloat group_number[] = { 0.0, 0.0, 0.0, 1.0 };

GLfloat lamp_emission_on[]     = { 0.4, 0.4, 0.0, 0.0};
GLfloat lamp_emission_off[]    = { 0.0, 0.0, 0.0, 0.0};
GLfloat lamp_specular_on[]     = { 1.0, 1.0, 0.0, 1.0 };
GLfloat lamp_ambient_diffuse[] = { 1.0, 1.0, 0.0, 1.0 };
GLfloat pole_ambient_diffuse[] = { 0.6, 0.6, 0.6, 1.0 };

#endif