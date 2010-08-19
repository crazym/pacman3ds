/*
 *  Material.cpp
 *  Pacman3D
 *
 *  Created by bronson on 10-08-05.
 *  Copyright 2010 Concordia University. All rights reserved.
 *
 */
#ifdef __APPLE__ /* OS X */
#include "Material.h"
#elif defined(__linux__) /* LINUX */
#include "../include/Material.h"
#else /* WINDOWS */
#include "../include/Material.h"
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

GLfloat pacman_body_ambient[] = { 1.0, 1.0, 0.0, 1.0 };
GLfloat pacman_body_diffuse[] = { 1.0, 1.0, 0.0, 1.0 };
GLfloat pacman_palate[]       = { 1.0, 0.0, 0.0, 1.0 };
GLfloat pacman_retina[]       = { 0.0, 0.0, 0.0, 1.0 };
GLfloat pacman_pupil[]        = { 1.0, 1.0, 1.0, 1.0 };

GLfloat pacman_palate_jacko[] = { 0.0, 0.0, 0.0, 1.0 };
GLfloat pacman_pupil_jacko[]  = { 0.0, 0.0, 0.0, 1.0 };

GLfloat pacman_paper_ambient_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };

GLfloat ghost_body[]  = { 0.85, 0.85, 0.85, 0.85 };
GLfloat ghost_white[] = { 0.0, 0.0, 0.0, 1.0 };
GLfloat ghost_pupil[] = { 0.0, 0.0, 1.0, 1.0 };

GLfloat group_number[] = { 0.0, 0.0, 0.0, 1.0 };

GLfloat lamp_emission_on[]     = { 0.4, 0.4, 0.0, 0.0};
GLfloat lamp_emission_off[]    = { 0.0, 0.0, 0.0, 0.0};
GLfloat lamp_specular_on[]     = { 1.0, 1.0, 0.0, 1.0 };
GLfloat lamp_ambient_diffuse[] = { 1.0, 1.0, 0.0, 1.0 };
GLfloat pole_ambient_diffuse[] = { 0.6, 0.6, 0.6, 1.0 };

//GLfloat shadow_mat[] = {0.0,0.0,0.0,0.4};
GLfloat shadow_mat[] = {0.0,0.0,0.0,0.4};


// Light values and coordinates
GLfloat lightModelIntensity[] = { 0.1f, 0.1f, 0.1f, 1.0f };

/* Ambient Light Values */

GLfloat lightAmbient[]  = { 0.7f, 0.7f, 0.7f, 1.0f };
GLfloat lightDiffuse[]  = { 0.7f, 0.7f, 0.7f, 1.0f };
GLfloat lightSpecular[] = { 0.7f, 0.7f, 0.7f, 1.0f };
GLfloat lightPosition[] = { 0.0f, 1.0f, 0.0f, 0.0f }; /* Point down Y-Axis */

/* Spotlight Values */
GLfloat spotlightAmbient[]  = { 0.9f, 0.9f, 0.4f, 1.0f };
GLfloat spotlightDiffuse[]  = { 0.9f, 0.9f, 0.4f, 1.0f };
GLfloat spotlightSpecular[] = { 0.9f, 0.9f, 0.4f, 1.0f };

GLfloat spotlightPosition1[] = { 0.5f, 4.0f, 0.5f, 1.0f };
GLfloat spotlightPosition2[] = { 19.5f, 4.0f, 0.5f, 1.0f };
GLfloat spotlightPosition3[] = { 0.5f, 4.0f, 21.5f, 1.0f };
GLfloat spotlightPosition4[] = { 19.5f, 4.0f, 21.5f, 1.0f };

GLfloat streetlightPosition1[] = { 0.5f, 1.0f, 0.5f, 1.0f };
GLfloat streetlightPosition2[] = { 26.5f, 1.0f, 0.5f, 1.0f };
GLfloat streetlightPosition3[] = { 0.5f, 1.0f, 26.5f, 1.0f };
GLfloat streetlightPosition4[] = { 26.5f, 1.0f, 26.5f, 1.0f };
/*GLfloat spotlightDirection1[] = { 1.0f, 0.0f, 1.0f};
GLfloat spotlightDirection2[] = { -1.0f, 0.0f, 1.0f};
GLfloat spotlightDirection3[] = { 1.0f, 0.0f, -1.0f};
GLfloat spotlightDirection4[] = { -1.0f, 0.0f, -1.0f};*/
/*GLfloat spotlightPosition1[] = { 0.0f, 4.0f, 0.0f, 1.0f };
GLfloat spotlightPosition2[] = { 20.0f, 4.0f, 0.0f, 1.0f };
GLfloat spotlightPosition3[] = { 0.0f, 4.0f, 22.0f, 1.0f };
GLfloat spotlightPosition4[] = { 20.0f, 4.0f, 22.0f, 1.0f };*/

/* The projection of the spotlight onto the x-z plane is 4.
* In order to obtain a 45 degree projection between the x-plane and the
* z-plane the value must be 2sqrt(2) = ~2.82.  The value was calculated using
* the pythagorean theorem.*/
GLfloat spotlightDirection1[] = { 2.82f, -4, 2.82f, 1.0f };
GLfloat spotlightDirection2[] = { -2.82f, -4, 2.82f, 1.0f };
GLfloat spotlightDirection3[] = { 2.82f, -4, -2.82f, 1.0f };
GLfloat spotlightDirection4[] = { -2.82f, -4, -2.82f, 1.0f };
/*
GLfloat spotlightDirection1[] = { 2.82f, 0.0f, 2.82f, 1.0f };
GLfloat spotlightDirection2[] = { -2.82f, 0.0f, 2.82f, 1.0f };
GLfloat spotlightDirection3[] = { 2.82f, 0.0f, -2.82f, 1.0f };
GLfloat spotlightDirection4[] = { -2.82f, 0.0f, -2.82f, 1.0f };
*/
/* Frenzy Light Ambient*/

GLfloat flightAmbient[]  = { 1.0f, 0.3f, 0.2f, 1.0f };
GLfloat flightDiffuse[]  = { 1.0f, 0.5f, 0.2f, 1.0f };
GLfloat flightSpecular[] = { 1.0f, 0.5f, 0.2f, 1.0f };

/* Frenzy Spotlight Values */

GLfloat fspotlightAmbient[]  = { 1.0f, 0.2f, 0.0f, 1.0f };
GLfloat fspotlightDiffuse[]  = { 1.0f, 0.2f, 0.0f, 1.0f };
GLfloat fspotlightSpecular[] = { 1.0f, 0.2f, 0.0f, 1.0f };


