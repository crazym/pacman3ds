/*
 *  Ghost.cpp
 * 
 *
 *  Created by bronson on 10-07-16.
 *  Copyright 2010 Concordia University. All rights reserved.
 *  References:
 *      http://www.opengl.org/documentation/red_book/
 */

#include "Ghost.h"

#include "Common.h"
#include "textures.h"
#include "Pacman.h"
#include "Material.h"


#ifdef __APPLE__ /* OS X */
#define ghostTexture "ghostbody.raw"
#elif defined(__linux__) /* LINUX */
#define ghostTexture "data/Textures/ghostbody.raw"
#else /* WINDOWS */
#define ghostTexture "data/Textures/ghostbody.raw"
#endif

using namespace std;

extern GLfloat ghost_body[];
extern GLfloat ghost_pupil[];
extern GLfloat ghost_white[];
Pacman pacman();

GLuint Ghost::current_id = 0;

const static GLfloat SPEED = 0.05;

Ghost::Ghost()
{
    color[0] = 1.0;
    color[1] = 0.0;
    color[2] = 0.0;
    color[3] = 0.65;
    
#ifdef DEBUG
    cout << "Allocating Ghost" << endl;
#endif
    initializeModel();
    
    this->xVelocity = 0;
    this->zVelocity = 0;
    
    /* Set the Ghost Id for AI purposes */
    this->myId = current_id;
    ++current_id;
}

Ghost::Ghost(GLfloat red, GLfloat green, GLfloat blue)
{
    color[0] = red;
    color[1] = green;
    color[2] = blue;
    color[3] = 0.65;
    
#ifdef DEBUG
    cout << "Allocating Ghost" << endl;
#endif
    initializeModel();
    
    this->xVelocity = 0;
    this->zVelocity = -1;
    
    /* Set the Ghost Id for AI purposes */
    this->myId = current_id;
    ++current_id;
}

Ghost::~Ghost()
{
#ifdef DEBUG
    cout << "Deallocating Ghost" << endl;
#endif
    glDeleteLists(this->listID, 1);
    gluDeleteQuadric(cylinder);
}

void Ghost::get_pac(GLint x, GLint z)
{
	this->p_loc_x = x;
	this->p_loc_z = z;
	//cout<<"Pacman x: "<<p_loc_x<<endl;
	//cout<<"Pacman z: "<<p_loc_z<<endl;
}

void Ghost::get_bli(GLint x,GLint z)
{
	this->b_loc_x = x;
	this->b_loc_z = z;
	//cout<<"Blinky x: "<<b_loc_x<<endl;
	//cout<<"Blinky z: "<<b_loc_z<<endl;
}
void Ghost::initializeModel()
{    
    this->textureID = LoadTextureRAW(ghostTexture, 1, 64, 64);
    
    this->listID = glGenLists(1);
    glNewList(listID, GL_COMPILE);
    this->cylinder = gluNewQuadric();
    
    gluQuadricNormals(this->cylinder, GLU_SMOOTH);
    gluQuadricTexture(this->cylinder, GL_TRUE);
    
    glBindTexture(GL_TEXTURE_2D, this->textureID);
       
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, ghost_body);
    glColor4fv(color);
    glTranslatef(-0.4, -0.4, 0.0);
    
    //Draw the base
    glPushMatrix();
        //Draw first cone
        glPushMatrix();
            glRotatef(90, 1.0, 0.0, 0.0);
            glutSolidCone(0.3, 0.5, 10, 10);
        glPopMatrix();
    
        //Draw second cone
        glPushMatrix();
            glTranslatef(0.5, 0.0, 0.5);
            glRotatef(90, 1.0, 0.0, 0.0);
            glutSolidCone(0.3, 0.5, 10, 10);
        glPopMatrix();
    
        //Draw third cone
        glPushMatrix();
            glTranslatef(0.5, 0.0, -0.5);
            glRotatef(90, 1.0, 0.0, 0.0);
            glutSolidCone(0.3, 0.5, 10, 10);
        glPopMatrix();
    
        //Draw fourth cone
        glPushMatrix();
            glTranslatef(1.0, 0.0, 0.0);
            glRotatef(90, 1.0, 0.0, 0.0);
            glutSolidCone(0.3, 0.5, 10, 10);
        glPopMatrix();
    
    glPopMatrix();
    
    //Draw the cylindrical body
    glPushMatrix();
        glTranslatef(0.5, 0.78, 0.0);
        glRotatef(90, 1.0, 0.0, 0.0);
        gluCylinder(cylinder, 0.8, 0.8, 0.8, 20, 20);
    glPopMatrix();
    
    
    glEnable(GL_TEXTURE_GEN_S);
    glEnable(GL_TEXTURE_GEN_T);    
        
    //Draw the top spherical head
    glPushMatrix();
        glTranslatef(0.5, 0.8, 0.0);
        glutSolidSphere(0.8, 20, 20);
    glPopMatrix();
    
    glDisable(GL_TEXTURE_GEN_S);
    glDisable(GL_TEXTURE_GEN_T);
    
    //Draw the eyes
    glPushMatrix();
        glTranslatef(0.0, 0.8, 0.75);
    
        //Draw a white
        glPushMatrix();
            glTranslatef(0.25, 0.0, 0.0);
            glRotatef(-20, 0.0, 1.0, 0.0);
            glScalef(1.0, 1.0, 0.3);
            glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, ghost_white);
            glColor4fv(ghost_white);
            glutSolidSphere(0.2, 20, 20);
    
            /*
            //Draw its pupil
            glPushMatrix();
                glTranslatef(0.1, 0.0, 0.17);
                glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, ghost_pupil);
                glColor4fv(ghost_pupil);
                glutSolidSphere(0.1, 20, 20);

            glPopMatrix();
            */
        glPopMatrix();
    
    
        //Draw a white
        glPushMatrix();
            glTranslatef(0.75, 0.0, 0.0);
            glRotatef(20, 0.0, 1.0, 0.0);
            glScalef(1.0, 1.0, 0.3);
            glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, ghost_white);
            glColor4fv(ghost_white);
            glutSolidSphere(0.2, 20, 20);
    
            /*
            //Draw its pupil
            glPushMatrix();
                glTranslatef(0.06, 0.0, 0.17);
                glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, ghost_pupil);
                glColor4fv(ghost_pupil);
                glutSolidSphere(0.1, 20, 20);

            glPopMatrix();
            */
        glPopMatrix();
    glPopMatrix();

	//Draw a shadow

	//Setup
    glPushMatrix();
		glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, shadow_mat);
		glColor4fv(shadow_mat);

		glTranslatef(0.5,0.0,0.0);
		glRotatef(90,1,0,0);
		glScalef(1.0,1.0,1.0);
		shadow();
	glPopMatrix();

        
    glEndList();
    
}

void Ghost::initPosition(GLfloat x, GLfloat y, GLfloat z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

void Ghost::draw()
{
    //cout << "Ghost drawing" << endl;
    glPushMatrix();
    glTranslatef(this->x, this->y, this->z);
    glScalef(0.6, 0.6, 0.6);
    glCallList(this->listID);
    glPopMatrix();
}

void Ghost::move()
{
    this->x += this->xVelocity;
    this->z += this->zVelocity;
}

void Ghost::setDirection(char direction)
{
    switch (direction) {
        case 'n':
            this->zVelocity = -SPEED;
            this->xVelocity = 0;
            break;
            
        case 'e':
            this->xVelocity = SPEED;
            this->zVelocity = 0;
            break;
            
        case 's':
            this->zVelocity = SPEED;
            this->xVelocity = 0;
            break;
            
        case 'w':
            this->xVelocity = -SPEED;
            this->zVelocity = 0;
            break;
            
        default:
            break;
    }
}

void Ghost::collide(GLint n, GLint s, GLint e, GLint w)
{
    if (n && this->zVelocity < 0) 
    {
        this->zVelocity = 0;
        chooseMove('n');
    }
    
    if (s && this->zVelocity > 0)
    {
        this->zVelocity = 0;
        chooseMove('s');
    }
    
    if (e && this->xVelocity > 0)
    {
        this->xVelocity = 0;
        chooseMove('e');
    }
    
    if (w && this->xVelocity < 0) 
    {
        this->xVelocity = 0;
        chooseMove('w');
    }
	//TELEPORT
    if(this->x<-0.5)
		this->x=19.5;
	if(this->x>20.0)
		this->x=0.0;
	//enf of teleport
}


void Ghost::chooseMove(char side)
{
	int out=0;
	GLint direction = 0;
    /* Implement AI Logic */

	//Blinky
    if (this->myId == 0) 
    {
        //Logic for Ghost One 
		//Getting out of box
		if(out)
		{
			this->zVelocity = -SPEED;
			out=1;
		}
		//Turns toward the intersection closest to pacman
		//get pacman's coordinates
			//done with get_pac
		//get blinky's coordinates 
		//compare
		switch (side) {
		case 'n': case 's':
			if((this->b_loc_x)>(this->p_loc_x))
				this->xVelocity = -SPEED;	
			else if((this->b_loc_x)<(this->p_loc_x))
				this->xVelocity = SPEED;
			else if(this->b_loc_x==this->p_loc_x)
			{
				if((this->b_loc_z)>(this->p_loc_z))
					this->zVelocity = -SPEED;
				else if((this->b_loc_z)<(this->p_loc_z))
					this->zVelocity = SPEED;
			}
			break;
		/*
		case 's':
			if((this->b_loc_x)>(this->p_loc_x))
				this->xVelocity = -SPEED;	
			else if((this->b_loc_x)<(this->p_loc_x))
				this->xVelocity = SPEED;
			break;*/
		
		case 'e': case'w':
			if((this->b_loc_z)>(this->p_loc_z))
				this->zVelocity = -SPEED;
			else if((this->b_loc_z)<(this->p_loc_z))
				this->zVelocity = SPEED;	
			else if(this->b_loc_z==this->p_loc_z)
			{
				if((this->b_loc_x)>(this->p_loc_x))
					this->xVelocity = -SPEED;	
				else if((this->b_loc_x)<(this->p_loc_x))
					this->xVelocity = SPEED;
			}
				break;
		/*
		case 'w':
			if((this->b_loc_z)>(this->p_loc_z))
				this->zVelocity = -SPEED;
			else if((this->b_loc_z)<(this->p_loc_z))
				this->zVelocity = SPEED;
			break;*/


		default:
			break;	
		}
    }

	//Inky
    else if (this->myId == 1)
    {
        //Logic for Ghost Two 
		//Getting out of box
		if(out)
		{
			this->zVelocity = -SPEED;
			out=1;
		}
		direction = rand() % 4;
		switch (direction) {
			case 0:
				this->xVelocity = SPEED;
				break;
			case 1:
				this->xVelocity = -SPEED;
				break;
			case 2:
				this->zVelocity = SPEED;
				break;
			case 3:
				this->zVelocity = -SPEED;
				break;

			default:
				break;
		}
    }

	//Pinky
    else if (this->myId == 2)
    {
        //Logic for Ghost Three 
		//Getting out of box
		if(out)
		{
			this->zVelocity = -SPEED;
			out=1;
		}
		switch (side) {
			case 'n':
				this->xVelocity = -SPEED;
				break;
			case 's':
				this->xVelocity = SPEED;
				break;
			case 'e':
				this->zVelocity = -SPEED;
				break;
			case 'w':
				this->zVelocity = SPEED;
				break;

			default:
				break;
		}
    }

	//Clyde
    else if (this->myId == 3)
    {
        //Logic for Ghost Four 
		//Getting out of box
		if(out)
		{
			this->zVelocity = -SPEED;
			out=1;
		}

		//GLint direction = rand() % 4;
		switch (side) {
			case 'n':
				this->xVelocity = SPEED;
				break;
			case 's':
				this->xVelocity = -SPEED;
				break;
			case 'e':
				this->zVelocity = SPEED;
				break;
			case 'w':
				this->zVelocity = -SPEED;
				break;

			default:
				break;
		}
    }

    /**************************/
    /* RANDOM DIRECTION LOGIC */
    /**************************/
    
	/*direction = rand() % 4;
    switch (direction) {
        case 0:
            this->xVelocity = SPEED;
            break;
        case 1:
            this->xVelocity = -SPEED;
            break;
        case 2:
            this->zVelocity = SPEED;
            break;
        case 3:
            this->zVelocity = -SPEED;
            break;

        default:
            break;
    }*/
    //cout << "Choosing: " << direction << endl;
}
