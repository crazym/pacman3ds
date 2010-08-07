/*
 *  Pacman.cpp
 * 
 *
 *  Created by carlos on 10-07-16.
 *  Copyright 2010 Concordia University. All rights reserved.
 *  References:
 *   http://users.encs.concordia.ca/~c371_1/skeleton.cpp
 *   http://ozark.hendrix.edu/~burch/cs/490/sched/feb8/
 *   http://www.codersger.de/mags/cscene/CS6/CS6-06.html
 *   http://users.encs.concordia.ca/~c371_1/skeleton.cpp
 */


#include "Pacman.h"
#include "Common.h"
#include "textures.h"

#include <cmath>
#include <iostream>

using namespace std;

extern GLfloat pacman_body_ambient[];
extern GLfloat pacman_body_diffuse[];
extern GLfloat pacman_palate[];
extern GLfloat pacman_retina[];
extern GLfloat pacman_pupil[];
extern GLfloat group_number[];

extern GLfloat pacman_palate_jacko[];
extern GLfloat pacman_pupil_jacko[];

extern GLfloat pacman_paper_ambient_diffuse[];

Pacman::Pacman()
{
#ifdef DEBUG
    cout << "Allocating Pacman" << endl;
#endif        
    this->textureID[0] = LoadTextureRAW("pacman_skin.raw", 1, 256, 256);
    this->textureID[1] = LoadTextureRAW("pumpkin.raw", 1, 256, 256);
    this->textureID[2] = LoadTextureRAW("paper.raw", 1, 256, 256);

    
    this->listID = glGenLists(3);
    
    /*****************/
    /* Normal Pacman */
    /*****************/
    glNewList(listID, GL_COMPILE);

   	//Top and bottom parts of Pacman--
    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_AMBIENT, pacman_body_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, pacman_body_diffuse);
    glColor4fv(pacman_body_diffuse);
    glTranslated(0.0, 0.0, 0.0);
    glRotatef(90, 0.0, 1, 0.0);
    top_pacman(2, 40, 40);
    bottom_pacman(2, 40, 40);
    glPopMatrix();
        
	glDisable(GL_TEXTURE_2D);
    
    //--------------------------------
	//Palate--------------------------
    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, pacman_palate);
    glColor4fv(pacman_palate);	
    glRotatef(58, 1, 0, 0.0);
    glTranslated(0.0, 0.0, 0.0);
    palate(4.0);
    glPopMatrix();
	//--------------------------------
	//Bottom of mouth-----------------
    glPushMatrix();
    glRotatef(116, 1, 0, 0.0);
    glTranslated(0.0, 0.0, 0.0);
    palate(4.0);
    glPopMatrix();
	//--------------------------------
	//Pupils--------------------------
    //Right Pupil-----------------
    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, pacman_pupil);
    glColor4fv(pacman_pupil);	
    glTranslated(1.3, 2.4, 2);
    glRotatef(70, 1, 0, 0);
    glRotatef(80, 0, 1, 0);
    glTranslated(0.0, 0.0, 0.0);
    pupil();
    glPopMatrix();
    //----------------------------
    
    //Left Pupil------------------
    glPushMatrix();
    glTranslated(-1.3, 2.4, 2);
    glRotatef(70, 1, 0, 0);
    glRotatef(80, 0, 1, 0);
    glTranslated(0.0, 0.0, 0.0);
    pupil();
    glPopMatrix();
    //----------------------------
	//--------------------------------
	//Retina--------------------------
    //Right Retina----------------
    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, pacman_retina);
    glColor4fv(pacman_retina);
    glTranslated(1.2, 2.7, 2.8);
    glRotatef(70, 1, 0, 0);
    glRotatef(80, 0, 1, 0);
    glTranslated(0.0, 0.0, 0.0);
    retina();
    glPopMatrix();
    //----------------------------
    
    //Left Retina-----------------
    glPushMatrix();
    glTranslated(-1.2, 2.7, 2.8);
    glRotatef(70, 1, 0, 0);
    glRotatef(80, 0, 1, 0);
    glTranslated(0.0, 0.0, 0.0);
    retina();
    glPopMatrix();
    //----------------------------
	//--------------------------------
	//Group Number--------------------

    //Top part of number 8--------
    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, group_number);
    glColor4fv(group_number);
    glTranslated(0, 3.9, 0);
    glRotatef(90, 1, 0, 0);
    glScalef(10.0, 10.0, 10.0);
    number();
    glPopMatrix();
    //----------------------------
    //Bottom part of number 8-----
    glPushMatrix();
    glTranslated(0, 3.4, -1.9);
    glRotatef(-120, 1, 0, 0);
    glScalef(10.0, 10.0, 10.0);
    number();
    glPopMatrix();
    //----------------------------
    

    glEndList();
    /************************/
    /* End of Normal Pacman */
    /************************/
    
    
    
    
    
    /*************************/
    /* Jack-o-lantern Pacman */
    /*************************/
    glNewList(listID+1, GL_COMPILE);
   	
    //Top and bottom parts of Pacman--
    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_AMBIENT, pacman_body_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, pacman_body_diffuse);
    glColor4fv(pacman_body_diffuse);
    glTranslated(0.0, 0.0, 0.0);
    glRotatef(90, 0.0, 1, 0.0);
    top_pacman(2, 40, 40, 1);
    bottom_pacman(2, 40, 40, 1);
    glPopMatrix();
    
	glDisable(GL_TEXTURE_2D);
    
    //--------------------------------
	//Palate--------------------------
    glPushMatrix();
    
    glColor4fv(pacman_palate_jacko);
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, pacman_palate_jacko);
    
    glRotatef(58, 1, 0, 0.0);
    glTranslated(0.0, 0.0, 0.0);
    palate(4.0);
    glPopMatrix();
	//--------------------------------
	//Bottom of mouth-----------------
    glPushMatrix();
    glRotatef(116, 1, 0, 0.0);
    glTranslated(0.0, 0.0, 0.0);
    palate(4.0);
    glPopMatrix();
	//--------------------------------
	
    //Pupils--------------------------
    //Right Pupil-----------------
    glPushMatrix();
    glColor4fv(pacman_palate_jacko);
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, pacman_pupil_jacko);
    glColor4f(0,0,0,1);
    glTranslated(1.3, 2.4, 1.4);
    glRotatef(-35, 1, 0, 0);
    glRotatef(0, 0, 1, 0);
    glScalef(0.3,0.3,0.3);
    glTranslated(0.0, 0.0, 0.0);
    pupil(1);
    glPopMatrix();
    //----------------------------
    
    //Left Pupil------------------
    glPushMatrix();
    glTranslated(-1.3, 2.4, 1.4);
    glRotatef(-35, 1, 0, 0);
    //glRotatef(80, 0, 1, 0);
    glScalef(0.3,0.3,0.3);
    glTranslated(0.0, 0.0, 0.0);
    pupil(1);
    glPopMatrix();
    //----------------------------
	//--------------------------------
	
    //Retina--------------------------
    //Right Retina----------------
    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, pacman_retina);
    glColor4fv(pacman_retina);
    glTranslated(1.2, 2.7, 2.8);
    glRotatef(70, 1, 0, 0);
    glRotatef(80, 0, 1, 0);
    glTranslated(0.0, 0.0, 0.0);
    glPopMatrix();
    //----------------------------
    
    //Left Retina-----------------
    glPushMatrix();
    glTranslated(-1.2, 2.7, 2.8);
    glRotatef(70, 1, 0, 0);
    glRotatef(80, 0, 1, 0);
    glTranslated(0.0, 0.0, 0.0);
    glPopMatrix();
    //----------------------------
	//--------------------------------
	
    //Group Number--------------------
    //Top part of number 8--------
    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, group_number);
    glColor4fv(group_number);
    glTranslated(0, 3.9, 0);
    glRotatef(90, 1, 0, 0);
    glScalef(10.0, 10.0, 10.0);
    number();
    glPopMatrix();
    //----------------------------
    //Bottom part of number 8-----
    glPushMatrix();
    glTranslated(0, 3.4, -1.9);
    glRotatef(-120, 1, 0, 0);
    glScalef(10.0, 10.0, 10.0);
    number();
    glPopMatrix();
    //----------------------------	
    glEndList();
    /********************************/
    /* End of Jack-o-lantern pacman */
    /********************************/
    
    
    
    
    /*****************/
    /* Paper Pacman */
    /*****************/
    glNewList(listID+2, GL_COMPILE);
    
   	//Top and bottom parts of Pacman--
    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, pacman_paper_ambient_diffuse);
    glColor4fv(pacman_paper_ambient_diffuse);
    glTranslated(0.0, 0.0, 0.0);
    glRotatef(90, 0.0, 1, 0.0);
    top_pacman(2, 40, 40, 2);
    bottom_pacman(2, 40, 40, 2);
    glPopMatrix();
    
	glDisable(GL_TEXTURE_2D);
    
    //--------------------------------
	//Palate--------------------------
    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, pacman_palate);
    glColor4fv(pacman_palate);	
    glRotatef(58, 1, 0, 0.0);
    glTranslated(0.0, 0.0, 0.0);
    palate(4.0);
    glPopMatrix();
	//--------------------------------
	//Bottom of mouth-----------------
    glPushMatrix();
    glRotatef(116, 1, 0, 0.0);
    glTranslated(0.0, 0.0, 0.0);
    palate(4.0);
    glPopMatrix();
	//--------------------------------
	//Pupils--------------------------
    //Right Pupil-----------------
    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, pacman_pupil);
    glColor4fv(pacman_pupil);	
    glTranslated(1.3, 2.4, 2);
    glRotatef(70, 1, 0, 0);
    glRotatef(80, 0, 1, 0);
    glTranslated(0.0, 0.0, 0.0);
    pupil();
    glPopMatrix();
    //----------------------------
    
    //Left Pupil------------------
    glPushMatrix();
    glTranslated(-1.3, 2.4, 2);
    glRotatef(70, 1, 0, 0);
    glRotatef(80, 0, 1, 0);
    glTranslated(0.0, 0.0, 0.0);
    pupil();
    glPopMatrix();
    //----------------------------
	//--------------------------------
	//Retina--------------------------
    //Right Retina----------------
    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, pacman_retina);
    glColor4fv(pacman_retina);
    glTranslated(1.2, 2.7, 2.8);
    glRotatef(70, 1, 0, 0);
    glRotatef(80, 0, 1, 0);
    glTranslated(0.0, 0.0, 0.0);
    retina();
    glPopMatrix();
    //----------------------------
    
    //Left Retina-----------------
    glPushMatrix();
    glTranslated(-1.2, 2.7, 2.8);
    glRotatef(70, 1, 0, 0);
    glRotatef(80, 0, 1, 0);
    glTranslated(0.0, 0.0, 0.0);
    retina();
    glPopMatrix();
    //----------------------------
	//--------------------------------
	//Group Number--------------------
    //Top part of number 8--------
    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, group_number);
    glColor4fv(group_number);
    glTranslated(0, 3.9, 0);
    glRotatef(90, 1, 0, 0);
    glScalef(10.0, 10.0, 10.0);
    number();
    glPopMatrix();
    //----------------------------
    //Bottom part of number 8-----
    glPushMatrix();
    glTranslated(0, 3.4, -1.9);
    glRotatef(-120, 1, 0, 0);
    glScalef(10.0, 10.0, 10.0);
    number();
    glPopMatrix();
    //----------------------------
    
    glEndList();
    /************************/
    /* End of Paper Pacman */
    /************************/
}

Pacman::~Pacman()
{
#ifdef DEBUG
    cout << "Deallocating Pacman" << endl;
#endif
    glDeleteLists(this->listID, 2);
}

void Pacman::initPosition(GLfloat x, GLfloat y, GLfloat z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

void Pacman::draw(GLint outfit)
{
    GLint texturesAreEnabled = 0;
    if (glIsEnabled(GL_TEXTURE_2D)) {
        texturesAreEnabled = 1;
    }
    
    glPushMatrix();
    glTranslatef(this->x, this->y, this->z);
    glScalef(0.125, 0.125, 0.125);
    glCallList(this->listID+outfit);
    glPopMatrix();
    
    if (texturesAreEnabled) {
        glEnable(GL_TEXTURE_2D);
    }
}


void Pacman::hemisphere(GLdouble r, GLint lats, GLint longs) 
{
	GLint i, j;
	for(i = 1; i <= lats; i++) 
	{
		GLdouble lat0 = 3.14159265 * (-0.5 + (GLdouble) (i - 1) / lats);
		GLdouble z0  = r*sin(lat0);
		GLdouble zr0 =  r*cos(lat0);
    
		GLdouble lat1 = 3.14159265 * (-0.5 + (GLdouble) i / lats);
		GLdouble z1 = r*sin(lat1);
		GLdouble zr1 = r*cos(lat1);
    
		//changing the longs +1 to -5 opens pacmans mouth
		glBegin(GL_QUAD_STRIP);
		for(j = 0; j <= longs; j++) 
		{
			GLdouble lng = 2*3.14159265 * (GLdouble) (j - 1) / longs/2;
			GLdouble x = r*cos(lng);
			GLdouble y = r*sin(lng);
    
			glNormal3f(x * zr0, y * zr0, r*z0);
			glVertex3f(x * zr0, y * zr0, r*z0);
			glNormal3f(x * zr1, y * zr1, r*z1);
			glVertex3f(x * zr1, y * zr1, r*z1);
		}
		glEnd();
	}
}


void Pacman::top_pacman(GLdouble r, GLint lats, GLint longs, GLint texture) 
{
	GLint i, j;

    glEnable(GL_TEXTURE_GEN_S);
    glEnable(GL_TEXTURE_GEN_T);
    
    glBindTexture(GL_TEXTURE_2D, this->textureID[texture]);
        
	for(i = 1; i <= lats; i++) 
	{
		GLdouble lat0 = 3.14159265 * (-0.5 + (GLdouble) (i - 1) / lats);
		GLdouble z0  = r*sin(lat0);
		GLdouble zr0 =  r*cos(lat0);
    
		GLdouble lat1 = 3.14159265 * (-0.5 + (GLdouble) i / lats);
		GLdouble z1 = r*sin(lat1);
		GLdouble zr1 = r*cos(lat1);
    
		//changing the longs +1 to -5 opens pacmans mouth
		glBegin(GL_QUAD_STRIP);
		for(j = 0; j <= longs-6; j++) 
		{
			GLdouble lng = 2*3.14159265 * (GLdouble) (j - 1) / longs/2;
			GLdouble x = r*cos(lng);
			GLdouble y = r*sin(lng);
    
			glNormal3f(x * zr0, y * zr0, r*z0);
			glVertex3f(x * zr0, y * zr0, r*z0);
			glNormal3f(x * zr1, y * zr1, r*z1);
			glVertex3f(x * zr1, y * zr1, r*z1);
		}
		glEnd();
	}
    
    glDisable(GL_TEXTURE_GEN_S);
    glDisable(GL_TEXTURE_GEN_T);
}

void Pacman::palate(GLdouble r)
{
	GLfloat radius = r;
	GLfloat vectorX = 0.0;
	GLfloat vectorY = 0.0;
	glBegin(GL_POLYGON);			
	for(GLfloat angle = 3.14159/2; angle>=(-3.14159/2); angle-=0.01)
	{		
		vectorX = (radius*(GLfloat)sin((GLdouble)angle));
		vectorY = (radius*(GLfloat)cos((GLdouble)angle));
		glVertex2d(vectorX,vectorY);	
	}
	glEnd();
}

void Pacman::bottom_pacman(GLdouble r, GLint lats, GLint longs, GLint texture) 
{
	GLint i, j;

    glEnable(GL_TEXTURE_GEN_S);
    glEnable(GL_TEXTURE_GEN_T);
    
    glBindTexture(GL_TEXTURE_2D, this->textureID[texture]);
    
	for(i = 1; i <= lats; i++) 
	{
		GLdouble lat0 = 3.14159265 * (-0.5 + (GLdouble) (i - 1) / lats);
		GLdouble z0  = r*sin(lat0);
		GLdouble zr0 =  r*cos(lat0);
    
		GLdouble lat1 = 3.14159265 * (-0.5 + (GLdouble) i / lats);
		GLdouble z1 = r*sin(lat1);
		GLdouble zr1 = r*cos(lat1);
    
		glBegin(GL_QUAD_STRIP);
		for(j = 1; j <= longs-5; j++) 
		{
			GLdouble lng = -2*3.14159265 * (GLdouble) (j - 1) / longs/2;
			GLdouble x = r*cos(lng);
			GLdouble y = r*sin(lng);
    
			glNormal3f(x * zr0, y * zr0, r*z0);
			glVertex3f(x * zr0, y * zr0, r*z0);
			glNormal3f(x * zr1, y * zr1, r*z1);
			glVertex3f(x * zr1, y * zr1, r*z1);
		}
		glEnd();
	}
    
    glDisable(GL_TEXTURE_GEN_S);
    glDisable(GL_TEXTURE_GEN_T);
}

void Pacman::pupil(GLint model)
{
	glPushMatrix();
    if (model == 0) 
    {
        hemisphere(1, 8, 8);
    } 
    
    else if (model == 1) 
    {
        GLint height=5;
        GLint depth=5;
        GLint width=5;

        glBegin(GL_TRIANGLES);
        
		//Front Face
		glVertex3f(-width/2,0.0,depth);
		glVertex3f(width/2,0.0,depth);
		glVertex3f(0,height,depth);
        
		//Back Face
		glVertex3f(-width/2,0.0,0);
		glVertex3f(width/2,0.0,0);
		glVertex3f(0,height,0);
		glEnd();
        
		glBegin(GL_QUAD_STRIP);
		//Right Side
		glVertex3f(0,height,0);
		glVertex3f(0,height,depth);
		glVertex3f(width/2,0.0,0);
		glVertex3f(width/2,0.0,depth);
        
		//Left Side
		glVertex3f(0,height,0);
		glVertex3f(0,height,depth);
		glVertex3f(-width/2,0.0,0);
		glVertex3f(-width/2,0.0,depth);
        
		//Bottom Face
		glVertex3f(-width/2,0.0,0);
		glVertex3f(-width/2,0.0,depth);
		//glVertex3f(0,5.0,10);
		//glVertex3f(0,5.0,15);
		glVertex3f(width/2,0.0,0);
		glVertex3f(width/2,0.0,depth);

		glEnd();

    }
	glPopMatrix();
}

void Pacman::retina()
{
	glPushMatrix();
	hemisphere(0.6, 8, 8);
	glPopMatrix();
}
