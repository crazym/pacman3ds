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
#include "Cube.h"
#include "textures.h"

#include <iostream>
#include <cmath>

extern GLfloat high_shininess[];
extern GLfloat no_shininess[];

extern GLfloat mat_specular[];
extern GLfloat no_specular[];

extern GLfloat group_number[];

Tile::Tile(GLchar type, GLint x, GLint z)
{    
    this->type = type;
    this->x = x;
    this->z = z;
    
    this->wallTextureID   = LoadTextureRAW("teal_brick.raw", 1, 256, 256);
    this->pelletTextureID = LoadTextureRAW("stone.raw", 1, 256, 256);
    this->floorTextureID  = LoadTextureRAW("floor.raw", 1, 256, 256);    
    
    switch (type) {
        case 'W':
            /* Init Wall */
            this->pellet = false;
            this->powerPellet = false;
           
            this->tile_color[0] = 0.0f;
            this->tile_color[1] = 0.0f;
            this->tile_color[2] = 1.0f;
            this->tile_color[3] = 1.0f;
            break;
       
        case 'Y':
            /* Init Blank */
            this->pellet = false;
            this->powerPellet = false;

            this->tile_color[0] = 0.7f;
            this->tile_color[1] = 0.7f;
            this->tile_color[2] = 0.7f;
            this->tile_color[3] = 1.0f;
            break;
        
        case 'Z':
            /* Init Tile with Pellet */
            this->pellet = true;
            this->powerPellet = false;

            this->pellet_color[0] = (rand()%255)/255.0f;
            this->pellet_color[1] = (rand()%255)/255.0f;
            this->pellet_color[2] = (rand()%255)/255.0f;
            this->pellet_color[3] = 1.0f;
            
            this->tile_color[0] = 0.7f;
            this->tile_color[1] = 0.7f;
            this->tile_color[2] = 0.7f;
            this->tile_color[3] = 1.0f;
            break;
        
        case 'X':
            /* Init Tile With Power Pellet */
            this->pellet = false;
            this->powerPellet = true;
            
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

void Tile::draw(GLint texturePellets, GLint texturePPellets)
{
    /* Setup position */
    glTranslatef(this->x, 0.0, this->z);
    
    /* Draw */
    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, tile_color);
    
    switch (this->type) {
        case 'W':
            /* Draw a Wall */
            glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);
            glMaterialfv(GL_FRONT, GL_SPECULAR, no_specular);
            glColor4fv(tile_color);
            solidCube(1.0, this->wallTextureID);
            break;
            
        case 'Y':
            /* Draw a Tile */
            glPushMatrix();
                glColor4fv(tile_color);
                glTranslatef(0.0, -0.4, 0.0);
                glScalef(1.0, 0.2, 1.0);
                solidCube(1.0, this->floorTextureID);
            glPopMatrix();
            
            /* Draw the Number 8 */
            /*
            glPushMatrix();
                glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, group_number);
                glColor4fv(group_number);
                glTranslatef(0.0, -0.2, 0.0);
                glRotatef(90, 1.0, 0.0, 0.0);
                number();
            glPopMatrix();
            
            glPushMatrix();
                glTranslatef(0.0, -0.2, 0.2);
                glRotatef(90, 1.0, 0.0, 0.0);
                number();
            glPopMatrix();
            */
            
            break;

        case 'Z':
            /* Draw a Tile */
            glPushMatrix();
                glColor4fv(tile_color);
                glTranslatef(0.0, -0.4, 0.0);
                glScalef(1.0, 0.2, 1.0);
                solidCube(1.0, this->floorTextureID);
            glPopMatrix();
            
            /* Draw the Number 8 */
            /*
            glPushMatrix();
                glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, group_number);
                glColor4fv(group_number);
                glTranslatef(0.0, -0.2, 0.0);
                glRotatef(90, 1.0, 0.0, 0.0);
                number();
            glPopMatrix();
            glPushMatrix();
                glTranslatef(0.0, -0.2, 0.2);
                glRotatef(90, 1.0, 0.0, 0.0);
                number();
            glPopMatrix();
            */
            break;
            
        case 'X':
            /* Draw a Tile */
            glPushMatrix();
                glColor4fv(tile_color);
                glTranslatef(0.0, -0.4, 0.0);
                glScalef(1.0, 0.2, 1.0);
                solidCube(1.0, this->floorTextureID);
            glPopMatrix();
            
            break;

            
        default:
            break;
            
    }
    glPopMatrix();
    
    /* Draw Pellet */
    if (this->pellet) {
        
        if (texturePellets) {
            glEnable(GL_TEXTURE_GEN_S);
            glEnable(GL_TEXTURE_GEN_T);
            
            glBindTexture(GL_TEXTURE_2D, this->pelletTextureID);
        }
        
        glTranslatef(0.0, 0.1, 0.0);
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, pellet_color);
        glColor4fv(pellet_color);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, high_shininess);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
        glutSolidSphere(0.2, 20, 20);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, no_shininess);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, no_specular);
        
        if (texturePellets) {
            glDisable(GL_TEXTURE_GEN_S);
            glDisable(GL_TEXTURE_GEN_T);
        }
    }
    
    /* Draw Power Pellet */
    if (this->powerPellet) {
        
        if (texturePPellets) {
            glEnable(GL_TEXTURE_GEN_S);
            glEnable(GL_TEXTURE_GEN_T);
            
            glBindTexture(GL_TEXTURE_2D, this->pelletTextureID);            
        }
        
        glTranslatef(0.0, 0.1, 0.0);
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, pellet_color);
        glColor4fv(pellet_color);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, high_shininess);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
        glutSolidSphere(0.4, 20, 20);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, no_shininess);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, no_specular);
        
        if (texturePPellets) {
            glDisable(GL_TEXTURE_GEN_S);
            glDisable(GL_TEXTURE_GEN_T);
        }
        
    }
}