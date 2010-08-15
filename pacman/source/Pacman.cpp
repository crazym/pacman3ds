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
#include "Material.h"
#include "Common.h"

#include <cmath>
#include <iostream>

#ifdef __APPLE__ /* OS X */
#define pacmanTexture1 "pacman_skin.raw"
#define pacmanTexture2 "pacman-batman.raw"
#define pacmanTexture3 "paper.raw"
#elif defined(__linux__) /* LINUX */
#define pacmanTexture1 "data/Textures/pacman_skin.raw"
#define pacmanTexture2 "data/Textures/pacman-batman.raw"
#define pacmanTexture3 "data/Textures/paper.raw"
#else /* WINDOWS */
#define pacmanTexture1 "data/Textures/pacman_skin.raw"
#define pacmanTexture2 "data/Textures/pumpkin.raw"
#define pacmanTexture3 "data/Textures/paper.raw"
#endif

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

static int pac_atop=0;
static int open=0;

const GLfloat SPEED = 0.05;
const GLfloat FRENZY_SPEED = 0.1;

Pacman::Pacman()
{
#ifdef DEBUG
    cout << "Allocating Pacman" << endl;
#endif        
    this->xVelocity = 0;
    this->zVelocity = 0;
    this->outfit = 0;
    
    this->textureID[0] = LoadTextureRAW(pacmanTexture1, 1, 64, 64);
    this->textureID[1] = LoadTextureRAW(pacmanTexture2, 1, 64, 64);
    this->textureID[2] = LoadTextureRAW(pacmanTexture3, 1, 64, 64);

    this->frenzy = 0;
    this->speed = SPEED;
}

Pacman::~Pacman()
{
#ifdef DEBUG
    cout << "Deallocating Pacman" << endl;
#endif
}

void Pacman::initPosition(GLfloat x, GLfloat y, GLfloat z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

void Pacman::draw()
{
    GLint texturesAreEnabled = 0;
    if (glIsEnabled(GL_TEXTURE_2D)) {
        texturesAreEnabled = 1;
    }
        
    glPushMatrix();
    glTranslatef(this->x, this->y, this->z);
    //glScalef(0.125, 0.125, 0.125);
    glScalef(0.1, 0.1, 0.1);

    /* Rotate the Pacman according to his direction */
    if (xVelocity > 0) {
        glRotatef(90, 0, 1, 0);
    } else if (xVelocity < 0) {
        glRotatef(-90, 0, 1, 0);
    } else if (zVelocity < 0) {
        glRotatef(180, 0, 1, 0);
    }

    if (this->outfit == 0) 
    {
        pacman_1();
    }
    else if (this->outfit == 1)
    {
        pacman_2();
    }
    else if (this->outfit == 2)
    {
        pacman_3();
    }
    
    //glCallList(this->listID+outfit);
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
		//for(j = 0; j <= longs-6; j++) 
		for(j = 0; j <= longs+1; j++)
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
		//for(j = 1; j <= longs-5; j++) 
		for(j = 1; j <= longs-0; j++) 
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

void Pacman::setDirection(char direction)
{
    switch (direction) {
        case 'n':
            this->zVelocity = -this->speed;
            this->xVelocity = 0;
            break;
        
        case 'e':
            this->xVelocity = this->speed;
            this->zVelocity = 0;
            break;
        
        case 's':
            this->zVelocity = this->speed;
            this->xVelocity = 0;
            break;
        
        case 'w':
            this->xVelocity = -this->speed;
            this->zVelocity = 0;
            break;

        default:
            break;
    }
    
}

void Pacman::move()
{
    this->x += this->xVelocity;
    this->z += this->zVelocity;
}

void Pacman::collide(GLint n, GLint s, GLint e, GLint w)
{
    /*********************/
    /* Detect End of Map */
    /*********************/
    if (this->x <= 0.5) 
    {
        this->x = 20;
        this->setDirection('w');
    }
    
    if (this->x >= 20.5) 
    {
        this->x = 1;
        this->setDirection('e');
    }
    
    /*********************/
    /* Detect Collisions */
    /*********************/
    if (n && this->zVelocity < 0) 
    {
        this->zVelocity = 0;
    }
    
    if (s && this->zVelocity > 0)
    {
        this->zVelocity = 0;
    }
    
    if (e && this->xVelocity > 0)
    {
        this->xVelocity = 0;
    }
    
    if (w && this->xVelocity < 0) 
    {
        this->xVelocity = 0;
    }
}


void Pacman::pacman_1()
{
	if((pac_atop==30)||(open))
	{
		pac_atop--;
		if(pac_atop==0)
			open=!open;
	}
    
	if((pac_atop==0)||(!open))
	{
		pac_atop++;
		if(pac_atop==30)
			open=!open;
	}
    
#ifdef DEBUG
	cout<<"top "<<pac_atop<<endl;
#endif
    
   	//Top and bottom parts of Pacman--
    glPushMatrix();
        glMaterialfv(GL_FRONT, GL_AMBIENT, pacman_body_ambient);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, pacman_body_diffuse);
		glColor4fv(pacman_body_diffuse);
		
		/*
		glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, high_shininess);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
		*/
        
        glTranslated(0.0, 0.0, 0.0);
        glRotatef(90, 0.0, 1, 0.0);
        
        glPushMatrix();
            glRotatef(90, 0.0, 1, 0.0);
            //increasing raises
            glRotatef(30-pac_atop, 1, 0, 0.0);
            //glTranslated(0.0, 2.0, 0.0);
            top_pacman(2, 40, 40);
        glPopMatrix();
    
        glPushMatrix();
            glRotatef(90, 0.0, 1, 0.0);
            //decreasing lowers
            glRotatef(-30+pac_atop, 1, 0, 0.0);
            bottom_pacman(2, 40, 40);
        glPopMatrix();
		/*
		glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, no_shininess);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, no_specular);
		*/
    glPopMatrix();
    
	glDisable(GL_TEXTURE_2D);
    

	//Palate--------------------------
    //Setup
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, pacman_palate);
    glColor4fv(pacman_palate);	
    //Draw
    drawBothPalates();
	
	//Animation---------------------------------------------------
	glPushMatrix();
	glRotatef(pac_atop,1,0,0);
	
    //Pupils--------------------------
    drawBothPupils();

	//Retina--------------------------
    drawBothRetinas();

	//Group Number--------------------
    drawNumberEight();

    glPopMatrix();
	//end of animation-----------------------------------------------
}

void Pacman::pacman_2()
{
    
	if((pac_atop==30)||(open))
	{
		pac_atop--;
		if(pac_atop==0)
			open=!open;
	}
    
	if((pac_atop==0)||(!open))
	{
		pac_atop++;
		if(pac_atop==30)
			open=!open;
	}
	//Top and bottom parts of Pacman--
    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_AMBIENT, pacman_paper_ambient_diffuse);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, pacman_paper_ambient_diffuse);
    glColor4fv(pacman_paper_ambient_diffuse);
    glTranslated(0.0, 0.0, 0.0);
    glRotatef(90, 0.0, 1, 0.0);
    glPushMatrix();
	glRotatef(90, 0.0, 1, 0.0);
	//increasing raises
	glRotatef(30-pac_atop, 1, 0, 0.0);
	top_pacman(2, 40, 40, 1);
	glPopMatrix();
	glPushMatrix();
	glRotatef(90, 0.0, 1, 0.0);
	//decreasing lowers
	glRotatef(-30+pac_atop, 1, 0, 0.0);
    bottom_pacman(2, 40, 40, 1);
	glPopMatrix();
    glPopMatrix();
    
	glDisable(GL_TEXTURE_2D);
    

	//Palate--------------------------
    //Setup
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, pacman_palate_jacko);
    glColor4fv(pacman_palate_jacko);
    //Draw
    drawBothPalates();
    
	//Animation---------------------------------------------------
	glPushMatrix();
	glRotatef(pac_atop,1,0,0);
    
    //Pupils--------------------------
    drawBothPupils(1);
	
    //Retina--------------------------
    //Jack-o-lantern has no retina
	
    //Group Number--------------------
    drawNumberEight();
	
    glPopMatrix();
	//end of animation-----------------------------------------------
}

void Pacman::pacman_3()
{
	if((pac_atop==30)||(open))
	{
		pac_atop--;
		if(pac_atop==0)
			open=!open;
	}
    
	if((pac_atop==0)||(!open))
	{
		pac_atop++;
		if(pac_atop==30)
			open=!open;
	}
    
    //Top and bottom parts of Pacman--
    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, pacman_paper_ambient_diffuse);
    glColor4fv(pacman_paper_ambient_diffuse);
    glTranslated(0.0, 0.0, 0.0);
    glRotatef(90, 0.0, 1, 0.0);
	glPushMatrix();
	glRotatef(90, 0.0, 1, 0.0);
	//increasing raises
	glRotatef(30-pac_atop, 1, 0, 0.0);
	top_pacman(2, 40, 40, 2);
	glPopMatrix();
    glPushMatrix();
	glRotatef(90, 0.0, 1, 0.0);
	//decreasing lowers
	glRotatef(-30+pac_atop, 1, 0, 0.0);
	bottom_pacman(2, 40, 40, 2);
    glPopMatrix();
	glPopMatrix();
    
	glDisable(GL_TEXTURE_2D);
    
	//Palate-------------------------    
    //Setup
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, pacman_palate);
    glColor4fv(pacman_palate);	
    //Draw
    drawBothPalates();	
	
	//Animation---------------------------------------------------
	glPushMatrix();
	glRotatef(pac_atop,1,0,0);
	
    //Pupils--------------------------
    drawBothPupils();
    
	//Retinas--------------------------
    drawBothRetinas();

	//Group Number--------------------
    drawNumberEight();

    glPopMatrix();
	//end of animation-----------------------------------------------

}

void Pacman::drawBothPalates()
{
    glPushMatrix();
    //Top of mouth--------------------
	//glRotatef(58, 1, 0, 0.0);
	//decreasing raises
	glRotatef(60+pac_atop, 1, 0, 0.0);
    glTranslated(0.0, 0.0, 0.0);
    palate(4.0);
    glPopMatrix();
	//--------------------------------
	//Bottom of mouth-----------------
    glPushMatrix();
    //glRotatef(116, 1, 0, 0.0);
    //increasing lowers
	glRotatef(124-pac_atop, 1, 0, 0.0);
	glTranslated(0.0, 0.0, 0.0);
    palate(4.0);
    glPopMatrix();
}

void Pacman::drawBothPupils(GLint model)
{
    //Setup
    if (model == 1) 
    {
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, pacman_pupil_jacko);
        glColor4f(0,0,0,1);
    } 
    else 
    {
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, pacman_pupil);
        glColor4fv(pacman_pupil);
    }
    
    /* Jack-o-lantern Model */
    if (model == 1) 
    {
        //Right Pupil-----------------
        glPushMatrix();
            glTranslated(1.3, 2.4, 1.4);
            glRotatef(-35, 1, 0, 0);
            glRotatef(0, 0, 1, 0);
            glScalef(0.3,0.3,0.3);
            glTranslated(0.0, 0.0, 0.0);
            pupil(model);
        glPopMatrix();
        //----------------------------
        
        //Left Pupil------------------
        glPushMatrix();
            glTranslated(-1.3, 2.4, 1.4);
            glRotatef(-35, 1, 0, 0);
            glScalef(0.3,0.3,0.3);
            glTranslated(0.0, 0.0, 0.0);
            pupil(model);
        glPopMatrix();
    }
    else 
    {
        //Right Pupil-----------------
        glPushMatrix();
            glTranslated(1.3, 2.4, 2);
            glRotatef(70, 1, 0, 0);
            glRotatef(80, 0, 1, 0);
            glTranslated(0.0, 0.0, 0.0);
            pupil(model);
        glPopMatrix();
        //----------------------------
        
        //Left Pupil------------------
        glPushMatrix();
            glTranslated(-1.3, 2.4, 2);
            glRotatef(70, 1, 0, 0);
            glRotatef(80, 0, 1, 0);
            glTranslated(0.0, 0.0, 0.0);
            pupil(model);
        glPopMatrix();
        //----------------------------
    }

}

void Pacman::drawBothRetinas()
{
    //Setup
    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, pacman_retina);
    glColor4fv(pacman_retina);
    
    //Right Retina----------------
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
}

void Pacman::drawNumberEight()
{
    //Setup
    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, group_number);
    glColor4fv(group_number);
    
    //Top part of number 8--------
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
}

GLint Pacman::getRoundedX()
{
    if (this->x - floor(this->x) < 0.5) 
    {
        return floor(this->x);
    }
    
    /* else */
    return ceil(this->x);
}

GLint Pacman::getRoundedZ()
{
    if (this->z - floor(this->z) < 0.5) 
    {
        return floor(this->z);
    }
    
    /* else */
    return ceil(this->z);
}

void Pacman::atePowerPellet()
{
    this->outfit = 1;
    this->frenzy = 1;
    this->speed = FRENZY_SPEED;
}

void Pacman::finishPowerPellet()
{
    this->outfit = 0;
    this->frenzy = 0;
    this->speed = SPEED;
}

void Pacman::drawShadow()
{
	//Setup
    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, shadow_mat);
    glColor4fv(shadow_mat);

	glTranslatef(0.0,-4.0,0.0);
	glRotatef(90,1,0,0);
	glScalef(3.0,3.0,3.0);
	shadow();
	glPopMatrix();
}

