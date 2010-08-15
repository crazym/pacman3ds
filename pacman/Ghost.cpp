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
    
    this->setDirection('n');
    
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
    
    this->setDirection('n');
    
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
            
            /* Centers the Ghost */
            if (this->x - floor(this->x) < 0.90) 
            {
                this->x = floor(this->x);
            } 
            else 
            {
                this->x = ceil(this->x);
            }
            
            this->direction = 'n';

            break;
            
        case 'e':
            this->xVelocity = SPEED;
            this->zVelocity = 0;
            
            
            /* Centers The Ghost */
            if (this->z - floor(this->z) < 0.90) 
            {
                this->z = floor(this->z);
            } 
            else 
            {
                this->z = ceil(this->z);
            }
            
            this->direction = 'e';

            break;
            
        case 's':
            this->zVelocity = SPEED;
            this->xVelocity = 0;

            /* Centers The Ghost */
            if (this->x - floor(this->x) < 0.90) 
            {
                this->x = floor(this->x);
            } 
            else 
            {
                this->x = ceil(this->x);
            }

            this->direction = 's';
            
            break;
            
        case 'w':
            this->xVelocity = -SPEED;
            this->zVelocity = 0;

            /* Centers The Ghost */
            if (this->z - floor(this->z) < 0.90) 
            {
                this->z = floor(this->z);
            } 
            else 
            {
                this->z = ceil(this->z);
            }
            
            this->direction = 'w';

            break;
            
        default:
            break;
    }
}

GLboolean Ghost::collide(GLint n, GLint s, GLint e, GLint w)
{
    /*********************/
    /* Detect End of Map */
    /*********************/
    if (this->x <= 0.5) 
    {
        this->x = 20;
        this->setDirection('w');
    }
    
    if (this->x >= 21.5) 
    {
        this->x = 0;
        this->setDirection('e');
    }
    
    /*********************/
    /* Detect Collisions */
    /*********************/
    if (n && this->direction == 'n') 
    {
        this->zVelocity = 0;
        this->z += SPEED;

        return true;
    } 
    
    if (s && this->direction == 's')
    {
        this->zVelocity = 0;
        this->z -= SPEED;

        return true;
    }
    
    if (e && this->direction == 'e')
    {
        this->xVelocity = 0;
        this->x -= SPEED;

        return true;
    }
    
    if (w && this->direction == 'w') 
    {
        this->xVelocity = 0;
        this->x += SPEED;
        
        return true;
    }
    
    return false;
    /********************/
    /* Did Not Collide  */
    /********************/
}


void Ghost::chooseMove(GLint n, GLint s, GLint e, GLint w, GLboolean collided, GLint pacmanPositionX, GLint pacmanPositionZ)
{
    /* If n, s, e, w are 1 that means there is a wall in the respective direction */
    
    /* Implement AI Logic */
    if (this->myId == 0) 
    {
        //Logic for Ghost One
        //Turns toward the intersection closest to pacman
		//compare pacman and blinky's coordinates

        /*********************************/
        /* Logic When Collided With Wall */
        /*********************************/
        if (collided) 
        {
            switch (this->direction) {
                case 'n': 
                case 's':
                    if (this->x > pacmanPositionX && !w)
                    {
                        setDirection('w');
                    }
                    else if (this->x < pacmanPositionX && !e)
                    {
                        setDirection('e');
                    }
                    else if (this->z > pacmanPositionZ && !n)
                    {
                        setDirection('n');
                    }
                    else if (!s)
                    {
                        setDirection('s');
                    }
                    break;
                    
                case 'e': 
                case 'w':
                    if (this->z > pacmanPositionZ && !n) 
                    {
                        setDirection('n');
                    }
                    else if (this->z < pacmanPositionZ && !s)
                    {
                        setDirection('s');
                    }
                    else if (this->x > pacmanPositionX && !w)
                    {
                        setDirection('w');
                    }
                    else if (!e)
                    {
                        setDirection('e');
                    }
                    break;
                    
                default:
                    break;
            }
        }
        /********************************************/
        /* Logic when reaching the center of a tile */
        /********************************************/
        else if(rand() % 100 == 1)
        {
            if (this->z > pacmanPositionZ) 
            {
                setDirection('n');
            }
            else if (this->z < pacmanPositionZ)
            {
                setDirection('s');
            }
        }
        else if(rand() % 100 == 1)
        {
            if (this->x > pacmanPositionX) 
            {
                setDirection('w');
            }
            else if (this->x < pacmanPositionX)
            {
                setDirection('e');
            }
            
        }
                
    }
    else if (this->myId == 1)
    {
        //Logic for Ghost Two
        
        /**************************/
        /* RANDOM DIRECTION LOGIC */
        /**************************/
        
        /*********************************/
        /* Logic When Collided With Wall */
        /*********************************/
        if (collided) 
        {
            GLint direction = rand() % 4;
            switch (direction) {
                case 0:
                    setDirection('n');
                    break;
                case 1:
                    setDirection('s');
                    break;
                case 2:
                    setDirection('e');
                    break;
                case 3:
                    setDirection('w');
                    break;
                    
                default:
                    break;
                    
            }
        }
        /********************************************/
        /* Logic when reaching the center of a tile */
        /********************************************/
        else if (rand() % 500 == 1)
        {
            /* Sometimes he feels like turning at an opening */
            switch (this->direction) {
                    
                case 's':
                case 'n':
                    if (!w) 
                    {
                        setDirection('w');
                    }
                    else if (!e)
                    {
                        setDirection('e');
                    }
                    break;
                   
                case 'w':
                case 'e':
                    if (!n) 
                    {
                        setDirection('n');
                    }
                    else if (!s)
                    {
                        setDirection('s');
                    }
                    
                    
                default:
                    break;
            }
        }

    }
    else if (this->myId == 2)
    {
        //Logic for Ghost Three
        
        /***************************/
        /* COUNTER-CLOCKWISE LOGIC */
        /***************************/
        
        /*********************************/
        /* Logic When Collided With Wall */
        /*********************************/
        if (collided) 
        {
            switch (this->direction) {
                /* Moving North */
                case 'n':
                    /* West is a wall */
                    if (w) 
                    {
                        setDirection('e');
                    }
                    else 
                    {
                        setDirection('w');
                    }
                    break;
                /* Moving East */
                case 'e':
                    /* North is a wall */
                    if (n) 
                    {
                        setDirection('s');
                    }
                    else 
                    {
                        setDirection('n');
                    }
                    break;
                /* Moving South */
                case 's':
                    /* East is a wall */
                    if (e) 
                    {
                        setDirection('w');
                    }
                    else 
                    {
                        setDirection('e');
                    }
                    break;
                /* Moving West */
                case 'w':
                    /* South is a wall */
                    if (s) 
                    {
                        setDirection('n');
                    }
                    else 
                    {
                        setDirection('s');
                    }
                    break;


                default:
                    break;
            }
        }
        /********************************************/
        /* Logic when reaching the center of a tile */
        /********************************************/
        else if (rand() % 500 == 1)
        {
            /* Sometimes he likes to turn counter-clockwise */
            switch (this->direction) {
                case 'n':
                    if (!w) 
                    {
                        setDirection('w');
                    }
                    break;
                    
                case 'e':
                    if (!n) 
                    {
                        setDirection('n');
                    }
                    break;
                    
                case 's':
                    if (!e) {
                        setDirection('e');
                    }
                    break;
                    
                case 'w':
                    if (!s) {
                        setDirection('s');
                    }
                    break;

                default:
                    break;
            }
        }
    }
    else if (this->myId == 3)
    {
        //Logic for Ghost Four
        
        /*******************/
        /* CLOCKWISE LOGIC */
        /*******************/
        
        /*********************************/
        /* Logic When Collided With Wall */
        /*********************************/
        if (collided) 
        {
            switch (this->direction) {
                /* Moving North */
                case 'n':
                    /* East is a wall */
                    if (e) 
                    {
                        setDirection('w');
                    } 
                    else
                    {
                        setDirection('e');   
                    }
                    break;
                /* Moving East */
                case 'e':
                    /* South is a Wall */
                    if (s) 
                    {
                        setDirection('n');
                    }
                    else 
                    {
                        setDirection('s');
                    }
                    break;
                /* Moving South */
                case 's':
                    /* West is a Wall */
                    if (w) 
                    {
                        setDirection('e');
                    }
                    else 
                    {
                        setDirection('w');
                    }
                    break;
                /* Moving West */
                case 'w':
                    /* North is a Wall */
                    if (n) 
                    {
                        setDirection('s');
                    }
                    else 
                    {
                        setDirection('n');
                    }
                    break;
                default:
                    break;
            }
        }
        /********************************************/
        /* Logic when reaching the center of a tile */
        /********************************************/
        else if (rand() % 500 == 1)
        {
            /* Sometimes he feels like turning clockwise */
            switch (this->direction) {
                case 'n':
                    if (!e) 
                    {
                        setDirection('e');
                    }
                    break;
                    
                case 'e':
                    if (!s) 
                    {
                        setDirection('s');
                    }
                    break;
                    
                case 's':
                    if (!w) 
                    {
                        setDirection('w');
                    }
                    break;
                    
                case 'w':
                    if (!n) 
                    {
                        setDirection('n');
                    }
                    break;

                default:
                    break;
            }
        }

    }
    

    //cout << "Choosing: " << direction << endl;
}


GLint Ghost::getRoundedX()
{
    if (this->x - floor(this->x) < 0.5) 
    {
        return floor(this->x);
    }
    
    /* else */
    return ceil(this->x);
}

GLint Ghost::getRoundedZ()
{
    if (this->z - floor(this->z) < 0.5) 
    {
        return floor(this->z);
    }
    
    /* else */
    return ceil(this->z);
}
