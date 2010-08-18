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
#include "Material.h"

#include <iostream>
#include <cmath>
#include <cassert>

#ifdef __APPLE__ /* OS X */
#define brickTexture "teal_brick.raw"
#define pelletTexture "stone.raw"
#define floorTexture1 "floor.raw"
#define floorTexture2 "floor_blood.raw"
#elif defined(__linux__) /* LINUX */
#define brickTexture "data/Textures/teal_brick.raw"
#define pelletTexture "data/Textures/stone.raw"
#define floorTexture1 "data/Textures/floor.raw"
#define floorTexture2 "data/Textures/floor_blood.raw"
#else /* WINDOWS */
#define brickTexture "data/Textures/teal_brick.raw"
#define pelletTexture "data/Textures/stone.raw"
#define floorTexture1 "data/Textures/floor.raw"
#define floorTexture2 "data/Textures/floor_blood.raw"
#endif

extern GLfloat high_shininess[];
extern GLfloat no_shininess[];

extern GLfloat mat_specular[];
extern GLfloat no_specular[];

extern GLfloat group_number[];

Tile::Tile(char type, GLint x, GLint z)
{    
    this->type = type;
    this->x = x;
    this->z = z;
    
    Vector eastWall(x+0.5, 0, z);
    Vector southWall(x, 0, z+0.5);
    Vector westWall(x-0.5, 0, z);
    Vector northWall(x, 0, z-0.5);
    
    Vector eastNormal(1, 0, 0);
    Vector southNormal(0, 0, 1);
    Vector northNormal(0, 0, -1);
    Vector westNormal(-1, 0, 0);
    
    
    this->eastPlane = Plane(eastWall, eastNormal);
    this->southPlane = Plane(southWall, southNormal);
    this->westPlane = Plane(westWall, westNormal);
    this->northPlane = Plane(northWall, northNormal);
    
    this->wallTextureID   = LoadTextureRAW(brickTexture, 1, 64, 64);
    this->pelletTextureID = LoadTextureRAW(pelletTexture, 1, 64, 64);
    
    if (rand()%10 > 2) {
        this->floorTextureID  = LoadTextureRAW(floorTexture1, 1, 64, 64);    
    } else {
        this->floorTextureID  = LoadTextureRAW(floorTexture2, 1, 64, 64);    

    }
    
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

            this->pellet_color[0] = Color(rand()%2);
            this->pellet_color[1] = Color(rand()%2);
            this->pellet_color[2] = Color(rand()%2);
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
            
            this->pellet_color[0] = Color(rand()%2);
            this->pellet_color[1] = Color(rand()%2);
			this->pellet_color[2] = Color(rand()%2);
            //this->pellet_color[2] = (rand()%255)/255.0f;
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

GLfloat Tile::Color(int key){
	switch(key){
	case 0:
		return 0.3;
	case 1:
		return 0.8;
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
