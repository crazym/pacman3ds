/*
 *  Tile.cpp
 *  Pacman3D
 *
 *  Created by bronson on 10-07-27.
 *  Copyright 2010 Concordia University. All rights reserved.
 *
 */

#include "Tile.h"
#include "Common.h"

#include <iostream>
#include <cmath>

extern GLfloat high_shininess[];
extern GLfloat no_shininess[];
extern GLfloat mat_specular[];
extern GLfloat no_specular[];

Tile::Tile(char type, GLint x, GLint z)
{
    this->type = type;
    this->x = x;
    this->z = z;
    
    switch (type) {
        case 'W':
            /* Init Wall */
            this->pellet = false;
           
            this->tile_color[0] = 0.0f;
            this->tile_color[1] = 0.0f;
            this->tile_color[2] = 1.0f;
            this->tile_color[3] = 1.0f;
            break;
       
        case 'Y':
            /* Init Blank */
            this->pellet = false;
            
            this->tile_color[0] = 0.7f;
            this->tile_color[1] = 0.7f;
            this->tile_color[2] = 0.7f;
            this->tile_color[3] = 1.0f;
            break;
        
        case 'Z':
            /* Init Tile with Pellet */
            this->pellet = true;
            this->pellet_color[0] = (rand()%255)/255.0f;
            this->pellet_color[1] = (rand()%255)/255.0f;
            this->pellet_color[2] = (rand()%255)/255.0f;
            this->pellet_color[3] = 1.0f;
            
            this->tile_color[0] = 0.7f;
            this->tile_color[1] = 0.7f;
            this->tile_color[2] = 0.7f;
            this->tile_color[3] = 1.0f;
            break;
       
        default:
            break;
    }
    

}

void Tile::draw()
{
    /* Setup position */
    glTranslatef(this->x, 0.0, this->z);
    
    /* Draw */
    glPushMatrix();
    switch (this->type) {
        case 'W':
            /* Draw a Wall */
            glColor4fv(tile_color);
            glutSolidCube(1.0);
            break;
            
        case 'Y':
            /* Draw a Tile */
            glPushMatrix();
                glColor4fv(tile_color);
                glTranslatef(0.0, -0.4, 0.0);
                glScalef(1.0, 0.2, 1.0);
                glutSolidCube(1.0);
            glPopMatrix();
            
            /* Draw the Number 8 */
            glPushMatrix();
                glColor4f(0.0, 0.0, 0.0, 1.0);
                glTranslatef(0.0, -0.2, 0.0);
                glRotatef(90, 1.0, 0.0, 0.0);
                number();
            glPopMatrix();
            
            glPushMatrix();
                glTranslatef(0.0, -0.2, 0.2);
                glRotatef(90, 1.0, 0.0, 0.0);
                number();
            glPopMatrix();
            break;

        case 'Z':
            /* Draw a Tile */
            glPushMatrix();
                glColor4fv(tile_color);
                glTranslatef(0.0, -0.4, 0.0);
                glScalef(1.0, 0.2, 1.0);
                glutSolidCube(1.0);
            glPopMatrix();
            
            /* Draw the Number 8 */
            glPushMatrix();
                glColor4f(0.0, 0.0, 0.0, 1.0);
                glTranslatef(0.0, -0.2, 0.0);
                glRotatef(90, 1.0, 0.0, 0.0);
                number();
            glPopMatrix();
            glPushMatrix();
                glTranslatef(0.0, -0.2, 0.2);
                glRotatef(90, 1.0, 0.0, 0.0);
                number();
            glPopMatrix();
            break;
            
        default:
            break;
    }
    glPopMatrix();
    
    /* Draw Pellet */
    if (this->pellet) {
        glTranslatef(0.0, 0.1, 0.0);
        glColor4fv(pellet_color);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, high_shininess);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
        glutSolidSphere(0.2, 20, 20);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, no_shininess);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, no_specular);
    }
}