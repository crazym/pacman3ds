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

extern GLfloat no_mat[];
extern GLfloat mat_ambient[];
extern GLfloat mat_ambient_color[];
extern GLfloat mat_diffuse[];
extern GLfloat mat_specular[];
extern GLfloat no_specular[];
extern GLfloat no_shininess[];
extern GLfloat low_shininess[];
extern GLfloat high_shininess[];
extern GLfloat mat_emission[];

extern GLfloat pacman_body_ambient[];
extern GLfloat pacman_body_diffuse[];
extern GLfloat pacman_palate[];
extern GLfloat pacman_retina[];
extern GLfloat pacman_pupil[];

extern GLfloat pacman_palate_jacko[];
extern GLfloat pacman_pupil_jacko[];


extern GLfloat ghost_body[];
extern GLfloat ghost_white[];
extern GLfloat ghost_pupil[];

extern GLfloat group_number[];

extern GLfloat lamp_emission_on[];
extern GLfloat lamp_emission_off[];
extern GLfloat lamp_specular_on[];
extern GLfloat lamp_ambient_diffuse[];
extern GLfloat pole_ambient_diffuse[];

#endif