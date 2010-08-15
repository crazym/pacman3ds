/*
 *  main.cpp
 * 
 *
 *  Created by carlos, bronson, sid, andrew, allan on 10-07-16.
 *  Copyright 2010 Concordia University. All rights reserved.
 *	Carlos Pinto (Team Leader)
 *	ID: 9343911
 *
 *	Bronson Zgeb
 *	ID: 9402268
 *
 *	Andrew Wolczak
 *	ID: 9095543
 *
 *	Allan Tran
 *	ID: 9099824
 *
 *	Siddhartha Kattoju
 *	ID: 9209905
 */

/*
 *  References:
 *      OpenGl Superbible, fourth edition, Richard S. Wright, Jr et al, Addison-Wesley
 *      http://www.opengl.org/documentation/red_book/
 *      http://users.encs.concordia.ca/~c371_1/skeleton.cpp
 *      http://ozark.hendrix.edu/~burch/cs/490/sched/feb8/
 *      http://www.codersger.de/mags/cscene/CS6/CS6-06.html
 *      http://users.encs.concordia.ca/~c371_1/skeleton.cpp
 *      http://www.nullterminator.net/gltexture.html
 */


/*
 *  Texture Sources: 
 *              Various: OpenGl Superbible, fourth edition, Richard S. Wright, Jr et al, Addison-Wesley
 *              Pumpkin: http://www.filterforge.com/filters/7893.html
 *              Floor Tile: Autodesk 3DsMax
 *              Paper: http://www.cgtextures.com/
 */

// This program uses sampleprogram.cpp as a template
// This Program Draws a scene in a Pacman game.

// Function Keys support:
//   1. F1 : toggle between ortho/perspective mode of viewing.
//   2. F2 : toggle between continuous rotation about y-axis and stop rotation
//   3. Up and Down Arrow keys for rotating view about  x-axis
//	 4. Left and Right Arrow keys for rotating about z-axis
//   5. [ and ] for roll
//	 6.	F10: reset view in case your view parameters get out of control.
//	 7. W : Forward
//   8. S : Backward
//   9. A : Strafe Left
//   10. D : Strafe Right
//   11. + : Zoom In Camera
//   12. - : Zoom Out Camera
//   13. F5: Light 1 on/off
//   14. F6: Light 2 on/off
//   15. F7: Light 3 on/off
//   16. F8: Light 4 on/off
//   17. F9: All Lights on/off
//   18. F11: Ambient Light on/off
//   19. 1: Pacman Cam
//   20. 2, 3, 4, 5: Ghost1, 2, 3, 4 Cam
//   21. 6, 7, 8, 9: Light1, 2, 3, 4 Cam
//   22. 0: Initial Cam
//   23. p: pause


// Link with: opengl32.lib, glu32.lib, glut32.lib.
// glut includes links to the other two libraries.
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
#include <ctime>
#endif

#include <cmath>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>

#include "Ghost.h"
#include "Pacman.h"
#include "Material.h"
#include "Timer.h"
#include "Map.h"
#include "Tile.h"
#include "Lamp.h"
#include "Camera.h"
#include "Vector.h"
#include "Common.h"

using namespace std;

void init();
void initMenu();
void setupLighting();
void cleanup();

void ProcessMenu(GLint value);
void resetViewParameters();
void functionKeys (int key, int x, int y);
void graphicKeys (unsigned char key, int x, int y);

/**************************
 Game Objects
 **************************/
static Pacman *pacman;
static Ghost *ghost1;
static Ghost *ghost2;
static Ghost *ghost3;
static Ghost *ghost4;
static Map *map1;
static Lamp *lamp1;
static Lamp *lamp2;
static Lamp *lamp3;
static Lamp *lamp4;
static Camera *camera;
static Timer *timer1;

static char map[483] = {										 
    //23 Rows
    //21 Cols
    'W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W',	 // Current map
    'W','X','Z','Z','Z','Z','Z','Z','Z','Z','W','Z','Z','Z','Z','Z','Z','Z','Z','X','W',
    'W','Z','W','W','W','Z','W','W','W','Z','W','Z','W','W','W','Z','W','W','W','Z','W',
    'W','Z','W','W','W','Z','W','W','W','Z','W','Z','W','W','W','Z','W','W','W','Z','W',
    'W','Z','Z','Z','Z','Z','Z','Z','Z','Z','W','Z','Z','Z','Z','Z','Z','Z','Z','Z','W',
    'W','Z','W','W','W','Z','W','Z','W','W','W','W','W','Z','W','Z','W','W','W','Z','W',
    'W','Z','Z','Z','Z','Z','W','Z','Z','Z','W','Z','Z','Z','W','Z','Z','Z','Z','Z','W',
    'W','W','W','W','W','Z','W','W','W','Z','W','Z','W','W','W','Z','W','W','W','W','W',
    'Y','Y','Y','Y','W','Z','W','Z','Z','Z','Z','Z','Z','Z','W','Z','W','Y','Y','Y','Y',
    'W','W','W','W','W','Z','W','Z','W','W','Y','W','W','Z','W','Z','W','W','W','W','W',
    'Y','Y','Y','Y','Y','X','Z','Z','W','Y','Y','Y','W','Z','Z','X','Y','Y','Y','Y','Y',
    'W','W','W','W','W','Z','W','Z','W','Y','Y','Y','W','Z','W','Z','W','W','W','W','W',
    'Y','Y','Y','Y','W','Z','W','Z','W','W','W','W','W','Z','W','Z','W','Y','Y','Y','Y',
    'Y','Y','Y','Y','W','Z','W','Z','Z','Z','Z','Z','Z','Z','W','Z','W','Y','Y','Y','Y',
    'W','W','W','W','W','Z','W','Z','W','W','W','W','W','Z','W','Z','W','W','W','W','W',
    'W','Z','Z','Z','Z','Z','Z','Z','Z','Z','W','Z','Z','Z','Z','Z','Z','Z','Z','Z','W',
    'W','Z','W','W','W','Z','W','W','W','Z','W','Z','W','W','W','Z','W','W','W','Z','W',
    'W','Z','Z','Z','W','Z','Z','Z','Z','Z','Z','Z','Z','Z','Z','Z','W','Z','Z','Z','W',
    'W','W','W','Z','W','Z','W','Z','W','W','W','W','W','Z','W','Z','W','Z','W','W','W',
    'W','Z','Z','Z','Z','Z','W','Z','Z','Z','W','Z','Z','Z','W','Z','Z','Z','Z','Z','W',
    'W','Z','W','W','W','W','W','W','W','Z','W','Z','W','W','W','W','W','W','W','Z','W',
    'W','X','Z','Z','Z','Z','Z','Z','Z','Z','Z','Z','Z','Z','Z','Z','Z','Z','Z','X','W',
    'W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W','W'
    
};

// Initial size of graphics window on your screen.
const GLint WIDTH  = 800; // in pixels
const GLint HEIGHT = 600; //

// increment for idle function rotation and zoom
const GLdouble rotStep = 5.0;
const GLdouble moveStep = 1.0;
const GLdouble ALL_ROUND = 360;
const GLdouble zoomStep = 5.0;
const GLdouble zoomFactor = 1.03;

// Current size of window (will change when you resize window)
GLint width  = WIDTH;
GLint height = HEIGHT;

// Mouse positions, normalized to [0,1].
GLdouble xMouse = 0.5;
GLdouble yMouse = 0.5;

// Bounds of viewing frustum, maintain uniform scaling.
GLdouble viewWindowLeft =  -40;
GLdouble viewWindowRight  = 40;
GLdouble viewWindowBottom =  -40;
GLdouble viewWindowTop  = 40;
GLdouble nearPlane =  1.5;
GLdouble farPlane  = 120;

// Viewing angle.
GLdouble fovy = 60;

/* misc */
//static GLdouble halfway = - (farPlane + nearPlane) / 2;	   // half way between near and far planes
static GLint ambient_light = 0;
static GLint textures_enabled = 1;
static GLint color_material_enabled = 0;
static GLint pacman_outfit = 0;

static GLint texturePellets = 1;
static GLint texturePPellets = 1;

static vector<Tile *>walls;
static vector<Tile *>pelletTiles;
static vector<Tile *>ppelletTiles;

GLboolean paused = 0;
GLboolean idleEnable = 0;	// flags that set continuous rotation on/off
GLboolean projType = 1;      // flag for proj type; ortho = 0, perspective = 1
GLboolean isWireFrame =0;    // flag for setting wire frame mode

//MADPACMAN
GLboolean frenzy = 0;
GLfloat f_timer=0.0;

//Saving previous state
GLfloat Temp[6][4];



void resetViewParameters()
{
	// resets 3D synthetic camera parameters to default values
    camera->reset();

	viewWindowLeft =  -60;
	viewWindowRight  = 60;
	viewWindowBottom =  -60;
	viewWindowTop  = 60;
    
	nearPlane =  60;
	farPlane  = 120;
    
	fovy = 60;
    
	projType = 1;
	idleEnable = 0;
}


void setView()
{
	// Must set it up in Projection Matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
    
	if(projType) {
        gluPerspective(fovy, (GLfloat) 1.0, nearPlane, farPlane);
    }
	else {
        glOrtho
		(
         viewWindowLeft,
         viewWindowRight,
         viewWindowBottom,
         viewWindowTop,
         nearPlane,
         farPlane
         );
    }
		
}

void zoom(unsigned char direction)
{
   // for zoom in reduces viewWindow size and for zoom out increases it.

	if (direction == '+') {
			viewWindowLeft += zoomStep; viewWindowRight -= zoomStep;
			viewWindowBottom += zoomStep; viewWindowTop -= zoomStep;
			fovy = fovy / zoomFactor;
		}
		else if (direction == '-') {
			viewWindowLeft -= zoomStep; viewWindowRight += zoomStep;
			viewWindowBottom -= zoomStep; viewWindowTop += zoomStep;
			fovy = fovy * zoomFactor;
		}

}

void drawAxes(){

	glPushMatrix();
		glBegin(GL_LINES);
		// X axis
		glColor3f(1, 0, 0);
		glVertex3f(0, 0, 0);
		glVertex3f(10, 0, 0);
		// Y axis
		glColor3f(0, 1, 0);
		glVertex3f(0, 0, 0);
		glVertex3f(0, 10, 0);
		// Z axis
		glColor3f(0, 0, 1);
		glVertex3f(0, 0, 0);
		glVertex3f(0, 0, 10);
		glEnd();
    glPopMatrix();
}

// This function is called to display the scene.
void display ()
{
    GLfloat spotlightPosition1[] = { 0.0f, 4.0f, 0.0f, 1.0f };
    GLfloat spotlightPosition2[] = { 20.0f, 4.0f, 0.0f, 1.0f };
    GLfloat spotlightPosition3[] = { 0.0f, 4.0f, 22.0f, 1.0f };
    GLfloat spotlightPosition4[] = { 20.0f, 4.0f, 22.0f, 1.0f };
    
    /* The projection of the spotlight onto the x-z plane is 4.
     * In order to obtain a 45 degree projection between the x-plane and the
     * z-plane the value must be 2sqrt(2) = ~2.82.  The value was calculated using
     * the pythagorean theorem.*/
    
    GLfloat spotlightDirection1[] = { 2.82f, -4.0f, 2.82f, 1.0f };
    GLfloat spotlightDirection2[] = { -2.82f, -4.0f, 2.82f, 1.0f };
    GLfloat spotlightDirection3[] = { 2.82f, -4.0f, -2.82f, 1.0f };
    GLfloat spotlightDirection4[] = { -2.82f, -4.0f, -2.82f, 1.0f };
    
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
    // set modelling mode
	glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    camera->look();
    
    lamp1->setLightPosition(spotlightPosition1, spotlightDirection1);
    lamp2->setLightPosition(spotlightPosition2, spotlightDirection2);
    lamp3->setLightPosition(spotlightPosition3, spotlightDirection3);
    lamp4->setLightPosition(spotlightPosition4, spotlightDirection4);                    
        
	// Draw model axes in centre of room.
    //drawAxes();
    
    if(isWireFrame) {
        glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    } else {
        glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
    }
    
    if (textures_enabled) glEnable(GL_TEXTURE_2D);

    //draw timer
    glPushMatrix();
		glColor3f(1,1,1);
		glTranslatef(6,4,0);
		glScalef(0.01,0.01,0.01);
		timer1->drawTimer();
	glPopMatrix();

    pacman->draw(pacman_outfit);
    map1->draw(texturePellets, texturePPellets);
    
    lamp1->draw();
    lamp2->draw();
    lamp3->draw();
    lamp4->draw();    
    ghost1->draw();
    ghost2->draw();
    ghost3->draw();
    ghost4->draw();

	

    if (textures_enabled) glDisable(GL_TEXTURE_2D);
    
    // now swap buffer
    glutSwapBuffers();   
}

void Frenzy(bool frenzy)
{
	if(frenzy)
	{
		f_timer=0.0;
		ProcessMenu(31);
		pacman->SPEED = 0.07;
		/* Ambient Light Values */

		for (int i=0;i<4;i++)
		{
			lightAmbient[i]=flightAmbient[i];
			lightDiffuse[i]=flightDiffuse[i];
			lightSpecular[i]=flightSpecular[i];

		}
		
		/* Spotlight Values */
		
		for (int s=0;s<4;s++)
		{
			spotlightAmbient[s]=fspotlightAmbient[s];
			spotlightDiffuse[s]=fspotlightDiffuse[s];
			spotlightSpecular[s]=fspotlightSpecular[s];

		}

		setupLighting();
	}
	if(!frenzy)
	{
		f_timer=0.0;
		ProcessMenu(30);
		/* Ambient Light Values */
		for (int i=0;i<4;i++)
		{
			lightAmbient[i]  = Temp[0][i];
			lightDiffuse[i]  = Temp[1][i];
			lightSpecular[i] = Temp[2][i];
		}
		
		/* Spotlight Values */
		for (int s=0;s<4;s++)
		{
			spotlightAmbient[s]  = Temp[3][s];
			spotlightDiffuse[s]  = Temp[4][s];
			spotlightSpecular[s] = Temp[5][s];
		}

		setupLighting();
	}
}

// This function is called when there is nothing else to do.
void idle ()
{
    /* Do nothing when paused */
    if (paused) {
        return;
    }
    
    /* Setup For Collision */
    Vector pacmanPosition(pacman->x, pacman->y, pacman->z);
    Vector ghostPosition(ghost1->x, ghost1->y, ghost1->z);
    
    GLint n, s, e, w;
    
    /***********************************
     *  Collision With Walls           *
     ***********************************/
    vector<Tile *>::const_iterator t_it;
    for (t_it = walls.begin(); t_it != walls.end(); ++t_it) 
    {   
        /**************************/   
        /* PACMAN WALL COLLISIONS */
        /**************************/
        
        /* Reset any collisions */
        n = s = e = w = 0;
        testWallCollision(pacmanPosition, *(*t_it), n, s, e, w);
        pacman->collide(n, s, e, w);
        
        
        /**************************/
        /* GHOST1 WALL COLLISIONS */
        /**************************/
        ghostPosition = Vector(ghost1->x, ghost1->y, ghost1->z);
        
        /* Reset any collisions */
        n = s = e = w = 0;
        testWallCollision(ghostPosition, *(*t_it), n, s, e, w);
        ghost1->collide(n, s, e, w);
        
        
        /**************************/
        /* GHOST2 WALL COLLISIONS */
        /**************************/
        ghostPosition = Vector(ghost2->x, ghost2->y, ghost2->z);
        
        /* Reset any collisions */
        n = s = e = w = 0;
        testWallCollision(ghostPosition, *(*t_it), n, s, e, w);
        ghost2->collide(n, s, e, w);      
        
        
        /**************************/
        /* GHOST3 WALL COLLISIONS */
        /**************************/
        ghostPosition = Vector(ghost3->x, ghost3->y, ghost3->z);
        
        /* Reset any collisions */
        n = s = e = w = 0;
        testWallCollision(ghostPosition, *(*t_it), n, s, e, w);      
        ghost3->collide(n, s, e, w);
        
        
        /**************************/
        /* GHOST4 WALL COLLISIONS */
        /**************************/
        ghostPosition = Vector(ghost4->x, ghost4->y, ghost4->z);
        
        /* Reset any collisions */
        n = s = e = w = 0;
        testWallCollision(ghostPosition, *(*t_it), n, s, e, w);
        ghost4->collide(n, s, e, w);
    }
    
    
    /*******************************/
    /*    END WALL COLLISIONS      */
    /*******************************/
#ifdef DEBUG
    cout << "END WALL COLLISION" << endl;
#endif
    
    vector<Tile *>::iterator p_it;
    /********************************
     *  Collision With Pellets      *
     ********************************/
    for(p_it = pelletTiles.begin(); p_it != pelletTiles.end(); ++p_it)
    {
        Vector tilePosition((*p_it)->x, 0, (*p_it)->z);
        GLdouble distance = testDistance(tilePosition, pacmanPosition);
        
        /* Eat the pellet */
        if (distance < 0.7) {
            (*p_it)->pellet = false;
            pelletTiles.erase(p_it);
        }
        
        /* Avoid an error when you eat the last pellet */
        if (p_it == pelletTiles.end()) 
        {
            break;
        }
    }

	vector<Tile *>::iterator pp_it;
    /********************************
     *  Collision With PPellets      *
     ********************************/
    for(pp_it = ppelletTiles.begin(); pp_it != ppelletTiles.end(); ++pp_it)
    {
        Vector tilePosition((*pp_it)->x, 0, (*pp_it)->z);
        GLdouble distance = testDistance(tilePosition, pacmanPosition);
        
        /* Eat the ppellet */
        if (distance < 0.7) {
            (*pp_it)->powerPellet = false;
            ppelletTiles.erase(pp_it);

			//JACKO
			frenzy = 1;
			Frenzy(frenzy);
			//Frenzy(frenzy);
        }
        
        /* Avoid an error when you eat the last pellet */
        if (pp_it == ppelletTiles.end()) 
        {
            break;
        }
    }
    
    
    /**********************/
    /*  MOVE CHARACTERS   */
    /**********************/
    pacman->move();
    ghost1->move();
    ghost2->move();
    ghost3->move();
    ghost4->move();
    
	//Determine Pacman's position
	ghost1->get_pac(pacman->x,pacman->z);
	ghost1->get_bli(ghost1->x,ghost1->z);
	
	//PACMAN'S FRENZY TIMER
	
	if (frenzy)
	{
		f_timer+=0.1;
		int s_l=rand()%5;
		switch (s_l)
		{
			case 0:
				functionKeys (GLUT_KEY_F5,0,0);
				break;
			case 1:
				functionKeys (GLUT_KEY_F6,0,0);
				break;
			case 2:
				functionKeys (GLUT_KEY_F7,0,0);
				break;
			case 3:
				functionKeys (GLUT_KEY_F8,0,0);
				break;
			case 4:
				functionKeys (GLUT_KEY_F9,0,0);
				break;

		}

		//DISABLE ALL SPOTLIGHTS
		functionKeys (GLUT_KEY_F9,0,0);
		functionKeys (GLUT_KEY_F9,0,0);

	}
	if (f_timer>30.0)
	{
		frenzy = 0;
		Frenzy(frenzy);
	}
	cout<<"TIME: "<<f_timer<<endl;
	//
	//

    if (idleEnable)
    {	
        /* Slow Rotation */
        camera->rotateY(rotStep/20);
    }
    glutPostRedisplay();
    
}

//capture mouse movement
void mouseMovement (int mx, int my)
{
   // Normalize mouse coordinates.
   xMouse = double(mx) / double(width);
   yMouse = 1 - double(my) / double(height);

   // Redisplay image.
   glutPostRedisplay();
}

// Respond to window resizing, preserving proportions.
// Parameters give new window size in pixels.
void reshapeMainWindow (int newWidth, int newHeight)
{
	width = newWidth;
	height = newHeight;
	glViewport(0, 0, width, height);
    setView();
	glMatrixMode (GL_MODELVIEW);
}

// Display Help.
void help()
{
   cout << "F1 : toggle between ortho/perspective mode of viewing" << endl
		<< "F2 : toggle between continuous rotation about y-axis and stop rotation" << endl
		<< "Up and Down Arrow keys for rotating view about  x-axis" << endl
		<< "Left and Right Arrow keys for rotating about z-axis" << endl
        << "[ and ] for roll" << endl
		<< "F10: reset view in case your view parameters get out of control" << endl
		<< "W : Forward" << endl
		<< "S : Backward" << endl
		<< "A : Strafe Left" << endl
		<< "D : Strafe Right" << endl
		<< "+ : Zoom in Camera" << endl
		<< "- : Zoom out Camera" << endl 
        << "Right Mouse Button: Menu" << endl
        << "F5: Light 1 on/off" << endl
        << "F6: Light 2 on/off" << endl
        << "F7: Light 3 on/off" << endl
        << "F8: Light 4 on/off" << endl
        << "F9: All Lights on/off" << endl
        << "F11: Ambient Light on/off" << endl
        << "1: Pacman cam" << endl
        << "2, 3, 4, 5: Ghost1, 2, 3, 4 Cam" << endl
        << "6, 7, 8, 9: Light1, 2, 3, 4 Cam" << endl
        << "0: Initial Cam" << endl
        << "p: pause" << endl
        << endl;
}

// Respond to graphic character keys.
// Parameters give key code and mouse coordinates.
void graphicKeys (unsigned char key, int x, int y)
{
	switch (key)
	{
		case 'h':
            help();
            break;
            
        case 27:
            exit(0);
            break;
            
        case 'p':
            paused = 1 - paused;
            break;
            
        case 'w':
            camera->moveForward(moveStep);
            break;
        case 's':
            camera->moveBackward(moveStep);
            break;
        case 'a':
            camera->moveLeft(moveStep);
            break;
        case 'd':
            camera->moveRight(moveStep);
            break;
		case '=':
        case '+':
			camera->zoomIn(zoomStep);
            break;
		case '-':
			camera->zoomOut(zoomStep);
            break;
        case ']':
            camera->roll(rotStep);
            break;
        case '[':
            camera->roll(-rotStep);
            break;
            
        case '1':
            ProcessMenu(5);
            break;
        case '2':
            ProcessMenu(6);
            break;
        case '3':
            ProcessMenu(7);
            break;
        case '4':
            ProcessMenu(8);
            break;
        case '5':
            ProcessMenu(9);
            break;
        case '6':
            ProcessMenu(10);
            break;
        case '7':
            ProcessMenu(11);
            break;
        case '8':
            ProcessMenu(12);
            break;
        case '9':
            ProcessMenu(13);
            break;
        case '0':
            ProcessMenu(16);
            break;

        case 't' :
            if(timer1->timerIsOn)
            timer1->stopTimer();
            else timer1->startTimer();
            break;

        default:
            cout << key << endl;
	}
    glutPostRedisplay();
}

//updates the scene according to menu selection
void ProcessMenu(GLint value)
{
	switch(value)
	{
		case 1:
			isWireFrame = false;
			break;
            
		case 2:
			isWireFrame = true;
			break;
            
        case 3:
            glShadeModel(GL_SMOOTH);
            break;
            
        case 4:
            glShadeModel(GL_FLAT);
            break;
            
            /* Pacman-cam */
        case 5:
            camera->reset();
            camera->setPosition(pacman->x, 
                                pacman->y+1.0, 
                                pacman->z);
            
            camera->setCenter(pacman->x, 
                              pacman->y, 
                              pacman->z+5.0);
            /*
            eye_x = pacman->x;
            eye_y = pacman->y+1.0;
            eye_z = pacman->z;
            
            center_x = pacman->x;
            center_y = pacman->y;
            center_z = pacman->z+5.0;
            
            fw_rw = 0;
            up_dn = 0;
            lt_rt = 0;
            
            yaw = 0;
            pitch  = 0;
            roll = 0;   
            */
            break;
            
            /* Ghost1-Cam */    
        case 6:
            camera->reset();
            camera->setPosition(ghost1->x, 
                                ghost1->y+1.0, 
                                ghost1->z);
            
            camera->setCenter(ghost1->x, 
                              ghost1->y, 
                              ghost1->z+5.0); 
            
            break;
            
            /* Ghost2-Cam */
        case 7:
            camera->reset();
            camera->setPosition(ghost2->x, 
                                ghost2->y+1.0, 
                                ghost2->z);
            
            camera->setCenter(ghost2->x, 
                              ghost2->y, 
                              ghost2->z+5.0);   
            
            break;
            
            /* Ghost3-Cam */    
        case 8:
            camera->reset();
            camera->setPosition(ghost3->x, 
                                ghost3->y+1.0, 
                                ghost3->z);
            
            camera->setCenter(ghost3->x, 
                              ghost3->y, 
                              ghost3->z+5.0); 
            
            break;
            
            /* Ghost4-Cam */
        case 9:
            camera->reset();
            camera->setPosition(ghost4->x, 
                                ghost4->y+1.0, 
                                ghost4->z);
            
            camera->setCenter(ghost4->x, 
                              ghost4->y, 
                              ghost4->z+5.0); 
            
            break;
            
            /* Light1-Cam */
        case 10:
            camera->reset();
            camera->setPosition(lamp1->x, 
                                lamp1->y+5.0, 
                                lamp1->z);
            
            camera->setCenter(lamp1->x +5, 
                              lamp1->y -4, 
                              lamp1->z +5);
            
            /******
             *NOTE: Changed viewing direction for better vision
             ******/
            /*
            camera->setCenter(lamp1->x +2.82, 
                              lamp1->y -4, 
                              lamp1->z +2.82);
            */
            break;
            
            /* Light2-Cam */
        case 11:
            camera->reset();
            camera->setPosition(lamp2->x, 
                                lamp2->y+5.0, 
                                lamp2->z);
            
            camera->setCenter(lamp2->x -5, 
                              lamp2->y -4, 
                              lamp2->z +5);
            /*
            camera->setCenter(lamp2->x -2.82, 
                              lamp2->y -4, 
                              lamp2->z +2.82);  
            */
            break;
            
            /* Light3-Cam */
		case 12:
            camera->reset();
            camera->setPosition(lamp3->x, 
                                lamp3->y+5.0, 
                                lamp3->z);
            
            camera->setCenter(lamp3->x +5, 
                              lamp3->y -4, 
                              lamp3->z -5);
            
            /*
            camera->setCenter(lamp3->x +2.82, 
                              lamp3->y -4, 
                              lamp3->z -2.82);
            */
            
            break;
            
            /* Light4-Cam */
		case 13:
            camera->reset();
            camera->setPosition(lamp4->x, 
                                lamp4->y+5.0, 
                                lamp4->z);
            
            camera->setCenter(lamp4->x -5, 
                              lamp4->y -4, 
                              lamp4->z -5);
            /*
            camera->setCenter(lamp4->x -2.82, 
                              lamp4->y -4, 
                              lamp4->z -2.82); 
            */
            break;
            
            /* Enable Ambient Light */
        case 14:
            glEnable(GL_LIGHT0);
            break;
            
            /* Disable Ambient Light */
        case 15:
            glDisable(GL_LIGHT0);
            break;
            
            /* Initial-Cam */
        case 16:
            camera->reset();
            break;
            
            /* Enable/Disable Color Material */
        case 17:
            color_material_enabled = 1 - color_material_enabled;
            if (color_material_enabled) {
                glEnable(GL_COLOR_MATERIAL);
            } else {
                glDisable(GL_COLOR_MATERIAL);
            }
            break;
            
            /* Enable Light 1 */
        case 19:
            lamp1->turnOn();
            break;
            
            /* Disable Light 1 */
        case 20:
            lamp1->turnOff();
            break;
            
            /* Enable Light 2 */
        case 21:
            lamp2->turnOn();
            break;
            
            /* Disable Light 2 */
        case 22:
            lamp2->turnOff();
            break;
            
            /* Enable Light 3 */
        case 23:
            lamp3->turnOn();
            break;
            
            /* Disable Light 3 */
        case 24:
            lamp3->turnOff();
            break;
            
            /* Enable Light 4 */
        case 25:
            lamp4->turnOn();
            break;
            
            /* Disable Light 4 */
        case 26:
            lamp4->turnOff();
            break;
            
            /* Enable Lamps */
        case 27:
            lamp1->turnOn();
            lamp2->turnOn();
            lamp3->turnOn();
            lamp4->turnOn();
            break;
            
            /* Disable Lamps */
        case 28:
            lamp1->turnOff();
            lamp2->turnOff();
            lamp3->turnOff();
            lamp4->turnOff();
            break;
            
            /* Enable/Disable Textures */
        case 29:
            textures_enabled = 1 - textures_enabled;
            break;
        
            /* Pacman Outfit 1 */
        case 30:
            pacman_outfit = 0;
            break;
            
            /* Pacman Outfit 2 */
        case 31:
            pacman_outfit = 1;
            break;
            
            /* Pacman Outfit 3 */
        case 32:
            pacman_outfit = 2;
            break;

            /* Enable/Disable Pellet Texture */
        case 33:
            texturePellets = 1 - texturePellets;
            break;

            /* Enable/Disable Power Pellet Texture */
        case 34:
            texturePPellets = 1 - texturePPellets;
            break;

            /* Enable/Disable All Pellet Texture */
        case 35:
            if (texturePellets || texturePPellets) {
                texturePellets = 0;
                texturePPellets = 0;
            } else {
                texturePellets = 1;
                texturePPellets = 1;
            }
            break;
            

        default:
            break;
	}
    
	glutPostRedisplay();
}

// Respond to function keys.
// Parameters give key code and mouse coordinates.
void functionKeys (int key, int x, int y)
{
   switch (key)
   {
       case GLUT_KEY_F10:
           resetViewParameters();
           break;
           
       case GLUT_KEY_F1:
           projType = 1 - projType;
           break;
           
       case GLUT_KEY_F2:
           idleEnable = 1 - idleEnable;
           break;
           
       case GLUT_KEY_F3:
           zoom('+');
           break;
           
       case GLUT_KEY_F4:
           zoom('-');
           break;
           
       case GLUT_KEY_F5:
           if (lamp1->isOn) {
               lamp1->turnOff();
           } else {
               lamp1->turnOn();
           }
           break;
           
       case GLUT_KEY_F6:
           if (lamp2->isOn) {
               lamp2->turnOff();
           } else {
               lamp2->turnOn();
           }
           
           break;
           
       case GLUT_KEY_F7:
           if (lamp3->isOn) {
               lamp3->turnOff();
           } else {
               lamp3->turnOn();
           }
           
           break;
           
       case GLUT_KEY_F8:
           if (lamp4->isOn) {
               lamp4->turnOff();
           } else {
               lamp4->turnOn();
           }
           
           break;
           
       case GLUT_KEY_F9:
           if (lamp1->isOn || lamp2->isOn || lamp3->isOn || lamp4->isOn) {
               lamp1->turnOff();
               lamp2->turnOff();
               lamp3->turnOff();
               lamp4->turnOff();
           } else {
               lamp1->turnOn();
               lamp2->turnOn();
               lamp3->turnOn();
               lamp4->turnOn();
           }

           break;
           
       case GLUT_KEY_F11:
           ProcessMenu(15-ambient_light);
           ambient_light = 1 - ambient_light;
           break;
           
/*
       case GLUT_KEY_UP:
           camera->rotateZ(-rotStep);
           break;
           
       case GLUT_KEY_DOWN:
           camera->rotateZ(rotStep);
           break; 

		case GLUT_KEY_RIGHT:
           camera->rotateY(rotStep);
           break;
           
        case GLUT_KEY_LEFT:
           camera->rotateY(-rotStep);
           break;  
 */
       case GLUT_KEY_UP:
           pacman->setDirection('n');
           break;
           
       case GLUT_KEY_DOWN:
           pacman->setDirection('s');
           break; 
           
       case GLUT_KEY_RIGHT:
           pacman->setDirection('e');          
           break;
           
       case GLUT_KEY_LEFT:
           pacman->setDirection('w');          
           break;  
   }

    glutPostRedisplay();
}




int main (int argc, char **argv)
{
    // GLUT initialization. Enable double buffer mode
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(width, height);
	glutCreateWindow("Pacman3D beta");
    
    initMenu();
    
	// Register call backs for standard tasks such as:
	// display, windowresize, keypress, functionkey press, mouse movement.
	glutDisplayFunc(display);
	glutReshapeFunc(reshapeMainWindow);
	glutKeyboardFunc(graphicKeys);
    glutSpecialFunc(functionKeys);
    glutMotionFunc(mouseMovement);
	glutIdleFunc(idle);
    
    // Display help.
	help();
    
    init();
    
    // Enter GLUT loop.
	glutMainLoop();
    
}


void initMenu()
{
    GLint nModeMenu; // menu identifier used when calling glutsetmenu
	nModeMenu = glutCreateMenu(ProcessMenu);
	glutAddMenuEntry("Solid",1);
	glutAddMenuEntry("Wire",2);
    glutAddMenuEntry("-------------", 0);
    glutAddMenuEntry("Smooth Shading", 3);
    glutAddMenuEntry("Flat Shading", 4);
    glutAddMenuEntry("-------------", 0);
    glutAddMenuEntry("Initial Cam", 16);
    glutAddMenuEntry("Pacman-Cam", 5);
    glutAddMenuEntry("Ghost1-Cam", 6);
    glutAddMenuEntry("Ghost2-Cam", 7);
    glutAddMenuEntry("Ghost3-Cam", 8);
    glutAddMenuEntry("Ghost4-Cam", 9);
    glutAddMenuEntry("Light1-Cam", 10);
    glutAddMenuEntry("Light2-Cam", 11);
    glutAddMenuEntry("Light3-Cam", 12);
    glutAddMenuEntry("Light4-Cam", 13);
    glutAddMenuEntry("-------------", 0);
    glutAddMenuEntry("Enable Ambient Light", 14);
    glutAddMenuEntry("Disable Ambient Light",15);
    glutAddMenuEntry("-------------", 0);
    glutAddMenuEntry("Enable/Disable Color Material", 17);
    glutAddMenuEntry("-------------", 0);
    glutAddMenuEntry("Enable Lamp 1", 19);
    glutAddMenuEntry("Disable Lamp 1", 20);
    glutAddMenuEntry("Enable Lamp 2", 21);
    glutAddMenuEntry("Disable Lamp 2", 22);
    glutAddMenuEntry("Enable Lamp 3", 23);
    glutAddMenuEntry("Disable Lamp 3", 24);
    glutAddMenuEntry("Enable Lamp 4", 25);
    glutAddMenuEntry("Disable Lamp 4", 26);
    glutAddMenuEntry("Enable All Lamps", 27);
    glutAddMenuEntry("Disable All Lamps", 28);
    glutAddMenuEntry("-------------", 0);
    glutAddMenuEntry("Enable/Disable Textures", 29);
    glutAddMenuEntry("-------------", 0);
    glutAddMenuEntry("Pacman Outfit 1", 30);
    glutAddMenuEntry("Pacman Outfit 2", 31);
    glutAddMenuEntry("Pacman Outfit 3", 32);
    glutAddMenuEntry("-------------", 0);
    glutAddMenuEntry("Enable/Disable Pellet Texture", 33);
    glutAddMenuEntry("Enable/Disable Power Pellet Texture", 34);
    glutAddMenuEntry("Enable/Disable All Pellet Texture", 35);
    
    
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}


void init()
{
	for (int i=0;i<6;i++)
	{
		for(int j=0;j<4;j++)
		{
			if(i==0)
				Temp[i][j]=lightAmbient[j];
			if(i==1)
				Temp[i][j]=lightDiffuse[j];
			if(i==2)
				Temp[i][j]=lightSpecular[j];
			if(i==3)
				Temp[i][j]=spotlightAmbient[i];
			if(i==4)
				Temp[i][j]=spotlightDiffuse[i];
			if(i==5)
				Temp[i][j]=spotlightSpecular[i];
		}
	}

    //init scene
    glShadeModel(GL_SMOOTH);
    setupLighting();
    
    /* intitialize timers */
    timer1 = new Timer();

	/* init characters */
    pacman = new Pacman();
    pacman->initPosition(1.0f, 0.2f, 3.0f);
    
    ghost1 = new Ghost(1.0, 0.0, 0.0);
    ghost2 = new Ghost(0.0, 1.0, 0.0);
    ghost3 = new Ghost(1.0, 0.5, 0.7);
    ghost4 = new Ghost(1.0, 0.5, 0.0);
    
    ghost1->initPosition(10.0f,  0.2f, 11.0f);
    ghost2->initPosition(10.0f, 0.2f, 11.0f);
    ghost3->initPosition(10.0f, 0.2f, 11.0f);
    ghost4->initPosition(10.0f, 0.2f, 11.0f);
    
    /* init map */
    srand(time(NULL)); //seed rand for pellet colours
    map1 = new Map(map, 23, 21);
    
    /* Create a vector of walls for collision detection */
    /* Create another vector of tiles with pellets for more detection */
    vector<Tile *>::const_iterator t_it;    
    for (t_it = map1->tiles.begin(); t_it != map1->tiles.end(); ++t_it) 
    {
        
        if ((*t_it)->type == 'W') {
            walls.push_back((*t_it));
        }
        
        if ((*t_it)->type == 'Z') {
            pelletTiles.push_back((*t_it));
        }
		
		//POWER
		if ((*t_it)->type == 'X') {
            ppelletTiles.push_back((*t_it));
        }
    }
    
    /* init camera */
    camera = new Camera();
    
    glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
    glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
    
    
    atexit(cleanup);    
}


void setupLighting()
{
	/*
    // Light values and coordinates
    GLfloat lightModelIntensity[] = { 0.1f, 0.1f, 0.1f, 1.0f };
    */
    /* Ambient Light Values */
    /*
    GLfloat lightAmbient[]  = { 0.7f, 0.7f, 0.7f, 1.0f };
    GLfloat lightDiffuse[]  = { 0.7f, 0.7f, 0.7f, 1.0f };
    GLfloat lightSpecular[] = { 0.7f, 0.7f, 0.7f, 1.0f };
    GLfloat lightPosition[] = { 0.0f, 1.0f, 0.0f, 0.0f }; // Point down Y-Axis 
    */
    /* Spotlight Values */
	/*
    GLfloat spotlightAmbient[]  = { 0.5f, 0.5f, 0.0f, 1.0f };
    GLfloat spotlightDiffuse[]  = { 0.5f, 0.5f, 0.0f, 1.0f };
    GLfloat spotlightSpecular[] = { 0.5f, 0.5f, 0.0f, 1.0f };
    GLfloat spotlightPosition1[] = { 0.5f, 1.0f, 0.5f, 1.0f };
    GLfloat spotlightPosition2[] = { 19.5f, 1.0f, 0.5f, 1.0f };
    GLfloat spotlightPosition3[] = { 0.5f, 1.0f, 21.5f, 1.0f };
    GLfloat spotlightPosition4[] = { 19.5f, 1.0f, 21.5f, 1.0f };
    GLfloat spotlightDirection1[] = { 1.0f, 0.0f, 1.0f};
    GLfloat spotlightDirection2[] = { -1.0f, 0.0f, 1.0f};
    GLfloat spotlightDirection3[] = { 1.0f, 0.0f, -1.0f};
    GLfloat spotlightDirection4[] = { -1.0f, 0.0f, -1.0f};
    */
    
    lamp1 = new Lamp(GL_LIGHT1, spotlightDirection1);
    lamp2 = new Lamp(GL_LIGHT2, spotlightDirection2);
    lamp3 = new Lamp(GL_LIGHT3, spotlightDirection3);
    lamp4 = new Lamp(GL_LIGHT4, spotlightDirection4);
    
    lamp1->setAmbDiffSpec(spotlightAmbient, spotlightDiffuse, spotlightSpecular);
    lamp2->setAmbDiffSpec(spotlightAmbient, spotlightDiffuse, spotlightSpecular);
    lamp3->setAmbDiffSpec(spotlightAmbient, spotlightDiffuse, spotlightSpecular);
    lamp4->setAmbDiffSpec(spotlightAmbient, spotlightDiffuse, spotlightSpecular);
    
    /* setup where the lamps are modeled */
    lamp1->setModelPosition(spotlightPosition1);
    lamp2->setModelPosition(spotlightPosition2);
    lamp3->setModelPosition(spotlightPosition3);
    lamp4->setModelPosition(spotlightPosition4);
    
    glEnable(GL_DEPTH_TEST);	// Hidden surface removal
    glFrontFace(GL_CCW);		// Counter clock-wise polygons face out
    
    // Enable lighting
    glEnable(GL_LIGHTING);
    
    /* Setup and enable light 0 */    
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lightModelIntensity);
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
    glEnable(GL_LIGHT0);
    
    // Set Material properties to follow glColor values
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    
    // Black blue background
    glClearColor(0.0f, 0.0f, 0.4f, 1.0f );
    
    // Enable Transparency
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    //Rescale Normals if needed
    glEnable(GL_NORMALIZE);
}


void cleanup()
{
    /* Clean up */
    delete pacman;
    delete ghost1;
    delete ghost2;
    delete ghost3;
    delete ghost4;
    delete map1;
    delete lamp1;
    delete lamp2;
    delete lamp3;
    delete lamp4;
}
