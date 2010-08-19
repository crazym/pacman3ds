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

/*
 *  Music Resources:
 *      FreeMusicArchive:
 *           Frenzy Music - The Master ov Time, pt. 1: Escape by Magic Hammer is licensed under a Attribution-Noncommercial-
 *                              No Derivative Works 3.0 United States License.
 *
 *
 *           Eating Sound - http://www.freesound.org/samplesViewSingle.php?id=27877 The Freesound Project is a collaborative database
 *                              of Creative Commons licensed sounds.
 */

// This program uses sampleprogram.cpp as a initalLightingValueslate
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

#include <fstream>
#include <cstdlib>
#include <cmath>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>

#include "../include/audio.h"
#include "../include/Ghost.h"
#include "../include/Pacman.h"
#include "../include/Material.h"
#include "../include/Timer.h"
#include "../include/Map.h"
#include "../include/Tile.h"
#include "../include/Lamp.h"
#include "../include/Camera.h"
#include "../include/Vector.h"
#include "../include/Common.h"
#include "../include/Menu.h"


#ifdef __APPLE__ /* OS X */
#define map1Path "Level1.txt"
#define map2Path "Level2.txt"
#elif defined(__linux__) /* LINUX */
#define map1Path "data/Maps/Level1.txt"
#define map2Path "data/Maps/Level2.txt"
#else /* WINDOWS */
#define map1Path "data/Maps/Level1.txt"
#define map2Path "data/Maps/Level2.txt"
#endif

using namespace std;

void initModels();
void initMenu();
void initCameras();
void setupLighting();
void cleanup();
void reset(GLuint loadLevel);
void loadMap(GLuint load);

void ProcessMenu(GLint value);
void functionKeys (int key, int x, int y);
void graphicKeys (unsigned char key, int x, int y);
void enterFullscreen();
void exitFullscreen();
void switchCamera(GLuint camera);

/**************************
 Game Objects
 **************************/
static Pacman *pacman;
static Pacman *pacman2;
static Ghost *ghost1;
static Ghost *ghost2;
static Ghost *ghost3;
static Ghost *ghost4;

static Map *currentMap;
static Map map2;
static Map map1;
static Menu *menu1;

static Lamp *lamp1;
static Lamp *lamp2;
static Lamp *lamp3;
static Lamp *lamp4;

static Timer *timer1;
static Timer *timer2;

static Camera *currentCamera;
static Camera mainCam;
static Camera lamp1Cam(1);
static Camera lamp2Cam(1);
static Camera lamp3Cam(1);
static Camera lamp4Cam(1);
static Camera pacmanCam(1);
static Camera ghost1Cam(1);
static Camera ghost2Cam(1);
static Camera ghost3Cam(1);
static Camera ghost4Cam(1);


static char map[784];
int level = 1; // Can either be level 1, level 2							 
  

// Initial size of graphics window on your screen.
const GLint WIDTH  = 800; // in pixels
const GLint HEIGHT = 600; //

static GLuint fullscreen = 0;

// increment for idle function rotation and zoom
const GLdouble rotStep = 5.0;
const GLdouble moveStep = 1.0;
const GLdouble ALL_ROUND = 360;
const GLdouble zoomStep = 5.0;
const GLdouble zoomFactor = 1.03;

/* For Collision Detection */
/* How close pacman and ghost has to be to collide with a wall when turning */
const GLfloat PACMAN_LEEWAY = 0.7;
const GLfloat GHOST_LEEWAY = 0.8;

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

static GLint texturePellets = 1;
static GLint texturePPellets = 1;

//Defined in timer.cpp
int lives = 3;
GLboolean dead = 0;
int t_flag = 0;
int p_text = 0;
int offset = 0;
//SCORE
long int score = 0;
int play_intro = 0;

static vector<Tile *>walls;
static vector<Tile *>pelletTiles;
static vector<Tile *>powerPelletTiles;

GLboolean inMenu = 0;
GLboolean multiplayer = 0;
GLboolean paused = 1;
GLboolean respawn = 0;
GLboolean idleEnable = 0;	// flags that set continuous rotation on/off
GLboolean projType = 1;      // flag for proj type; ortho = 0, perspective = 1
GLboolean isWireFrame =0;    // flag for setting wire frame mode
GLboolean ambient_lighting_enabled = 1;
GLboolean textures_enabled = 1;
GLboolean color_material_enabled = 1;
GLboolean menuEnabled = 1;
GLboolean timerDisplay = 1;
GLboolean lifeDisplay = 1;
GLboolean gameover = 0;
GLboolean g_o_display = 1;
GLboolean scoreDisplay = 1;
GLboolean g_dead = 0;


 /*
 * Store initial lighting context after setup so that it may be restored
 * after lighting is modified by powerups and other eventualities.
 */
GLfloat initalLightingValues[6][4];


// Will read 483 or 784 characters
void openMap()
{

	ifstream indata; // indata is like cin
	char letter; // variable for input value

	if(level == 1)
	{
		indata.open(map1Path); // opens the file
	}
	if(level == 2)
	{
		 indata.open(map2Path); // opens the file
	}
 
	if(!indata) { // file couldn't be opened
		cerr << "Error: file could not be opened" << endl;
		return;
	}
	
	int i = 0;

	indata >> letter;
	
	while (!indata.eof() ) { // keep reading until end-of-file
		  
		map[i] = letter;
		i++;
		indata >> letter; // sets EOF flag if no value found
	}
	   
	indata.close();
	
	return;

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

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
    // set modelling mode
	glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    currentCamera->look();
    
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

    if (color_material_enabled)
    	glEnable(GL_COLOR_MATERIAL);
    	else
    	glDisable(GL_COLOR_MATERIAL);
	

	if(menuEnabled){ 
	
		glPushMatrix();	
			glColor3f(1,1,1);
			glScalef(0.01,0.01,0.01);
			menu1->printMenu('0');
		glPopMatrix();
	}

	/*if(!menuEnabled&&inMenu)
	{
		//glPushMatrix();	
			glColor3f(1,1,1);
			//glScalef(0.01,0.01,0.01);
			menu1->printMenu('1');
		//glPopMatrix();
	}*/

	if(!menuEnabled)
	{
		if(lives>-1){
			if(timerDisplay){ 
				
				//draw game timer
				glPushMatrix();
					glColor3f(1,1,1);
					glTranslatef(1,4.5,0);
					glScalef(0.01,0.01,0.01);
					timer1->drawTimer();
				glPopMatrix();

				//draw powerup timer
				glPushMatrix();
					glColor3f(1,1,1);
					glTranslatef(1,3,0);
					glScalef(0.01,0.01,0.01);
					timer2->drawTimer();
				glPopMatrix();
			}
			
			if(lifeDisplay){
				//Display LIFE
				glPushMatrix();
				glColor3f(1,1,1);
				glTranslatef(1,7,0);
				glScalef(0.01,0.01,0.01);
				timer1->drawLife(lives);
				glPopMatrix();
			}
			if(scoreDisplay){
				glPushMatrix();
				glColor3f(1,1,1);
				glTranslatef(1,9,0);
				glScalef(0.01,0.01,0.01);
				timer1->drawScore(score);
				glPopMatrix();
			}
		}
	}

	if(gameover&&g_o_display){
			
		for(int i=0;i<3;i++){
			glPushMatrix();
			glColor3f(1,1,1);
			glTranslatef(1,9-2*i,0);
			//glRotatef(-30,1,0,0);
			glScalef(0.01,0.01,0.01);
			//timer1->drawTimer();
			timer1->drawGameOver(i);
			glPopMatrix();
		}
			
	}


    pacman->draw();
	if(multiplayer)
		pacman2->draw();
    currentMap->draw(texturePellets, texturePPellets);
    
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

void enableFrenzyMode(bool frenzy)
{
	stop_frenzy_audio();
	if(frenzy)
	{
		pacman->atePowerPellet();
	
		play_frenzy_audio();

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

		//ProcessMenu(17);

		setupLighting();
	}
	if(!frenzy)
	{
        pacman->finishPowerPellet();
		if(multiplayer)
		pacman2->finishPowerPellet();



		//set pacman's outfit.
		ProcessMenu(30);

		/* restore Ambient Light Values */
		for (int i=0;i<4;i++)
		{
			lightAmbient[i]  = initalLightingValues[0][i];
			lightDiffuse[i]  = initalLightingValues[1][i];
			lightSpecular[i] = initalLightingValues[2][i];
		}
		
		/* restore Spotlight Values */
		for (int s=0;s<4;s++)
		{
			spotlightAmbient[s]  = initalLightingValues[3][s];
			spotlightDiffuse[s]  = initalLightingValues[4][s];
			spotlightSpecular[s] = initalLightingValues[5][s];
		}
		
		//ProcessMenu(17);

		setupLighting();

		
	}
}

// This function is called when there is nothing else to do.
//collision detection, camera logic and ghost AI is implemented here.
void idle ()
{
    /* Do nothing when paused */
    if (paused) {

		if(play_intro == 0)
		{
			play_intro_audio();
			play_intro = 1;
		}

		timer1->timer_string = "paused";
		timer1->pause();
		timer2->pause();

        return;
    }
	
	if(!paused) {

		stop_intro_audio();
		play_intro = 0;
	}

	else if (respawn){
			timer1->timer_string = "PRESS 't' TO START";
			timer1->pause();
			timer2->pause();
			
			return;
	}
	else{

			if(timer1->timerIsPaused) timer1->resume();
			if(timer2->timerIsPaused) timer2->resume();

		}
    
	if(lives==-1){
		/*
			timer1->timer_string = "PRESS 't' TO START";
			timer1->pause();
			timer2->pause();*/
		/*
		for(int i=0;i<3;i++){
			glPushMatrix();
			glColor3f(1,1,1);
			glTranslatef(1,9-i,0);
			glScalef(0.01,0.01,0.01);
			timer1->drawGameOver(i);
			glPopMatrix();	
		}
		resetViewParameters();*/
		//graphicKeys ('m', 0, 0);
		return;

	}
    /* Setup For Collision */
    Vector pacmanPosition(pacman->x, pacman->y, pacman->z);
    Vector ghostPosition(ghost1->x, ghost1->y, ghost1->z);

    /* Ghost's position in the map array */
    GLuint positionInMapArray;

    /* Used to Determine how far the ghost is from the center of a tile.
     This determines whether he should look for a new opening or not. */
    GLfloat distanceFromCenterX;
    GLfloat distanceFromCenterZ;

    /* A flag used to skip unnecessary calculations and trim clock cycles and code */
    GLuint ghostNeedsToMove = 0;
    
    /* A flag if the ghost collides with a wall.  Used for AI logic. */
    GLuint ghostCollided = 0;

    /* Collisions to the north, south, east, west */
    GLint n, s, e, w;
    

    /***********************/
    /* Pacman Camera Logic */
    /***********************/
    if (pacmanCam.enabled)
    {
        currentCamera->setPosition(pacman->x, pacman->y+1.5, pacman->z);

        if (pacman->xVelocity < 0)
        {
            currentCamera->setCenter(pacman->x-5, pacman->y, pacman->z);
        }
        else if (pacman->xVelocity > 0)
        {
            currentCamera->setCenter(pacman->x+5, pacman->y, pacman->z);
        }
        else if (pacman->zVelocity < 0)
        {
            currentCamera->setCenter(pacman->x, pacman->y, pacman->z-5);
        }
        else if (pacman->zVelocity > 0)
        {
            currentCamera->setCenter(pacman->x, pacman->y, pacman->z+5);
        }
    }

    /***********************/
    /* Ghost1 Camera Logic */
    /***********************/
    if (ghost1Cam.enabled)
    {
        currentCamera->setPosition(ghost1->x, ghost1->y+1.5, ghost1->z);

        if (ghost1->direction == 'n')
        {
            currentCamera->setCenter(ghost1->x, ghost1->y, ghost1->z - 5);
        }
        else if (ghost1->direction == 's')
        {
            currentCamera->setCenter(ghost1->x, ghost1->y, ghost1->z + 5);
        }
        else if (ghost1->direction == 'e')
        {
            currentCamera->setCenter(ghost1->x + 5, ghost1->y, ghost1->z);
        }
        else if (ghost1->direction == 'w')
        {
            currentCamera->setCenter(ghost1->x - 5, ghost1->y, ghost1->z);
        }
    }

    /***********************/
    /* Ghost2 Camera Logic */
    /***********************/
    if (ghost2Cam.enabled)
    {
        currentCamera->setPosition(ghost2->x, ghost2->y+1.5, ghost2->z);

        if (ghost2->direction == 'n')
        {
            currentCamera->setCenter(ghost2->x, ghost2->y, ghost2->z - 5);
        }
        else if (ghost2->direction == 's')
        {
            currentCamera->setCenter(ghost2->x, ghost2->y, ghost2->z + 5);
        }
        else if (ghost2->direction == 'e')
        {
            currentCamera->setCenter(ghost2->x + 5, ghost2->y, ghost2->z);
        }
        else if (ghost2->direction == 'w')
        {
            currentCamera->setCenter(ghost2->x - 5, ghost2->y, ghost2->z);
        }
    }

    /***********************/
    /* Ghost3 Camera Logic */
    /***********************/
    if (ghost3Cam.enabled)
    {
        currentCamera->setPosition(ghost3->x, ghost3->y+1.5, ghost3->z);

        if (ghost3->direction == 'n')
        {
            currentCamera->setCenter(ghost3->x, ghost3->y, ghost3->z - 5);
        }
        else if (ghost3->direction == 's')
        {
            currentCamera->setCenter(ghost3->x, ghost3->y, ghost3->z + 5);
        }
        else if (ghost3->direction == 'e')
        {
            currentCamera->setCenter(ghost3->x + 5, ghost3->y, ghost3->z);
        }
        else if (ghost3->direction == 'w')
        {
            currentCamera->setCenter(ghost3->x - 5, ghost3->y, ghost3->z);
        }
    }

    /***********************/
    /* Ghost4 Camera Logic */
    /***********************/
    if (ghost4Cam.enabled)
    {
        currentCamera->setPosition(ghost4->x, ghost4->y+1.5, ghost4->z);

        if (ghost4->direction == 'n')
        {
            currentCamera->setCenter(ghost4->x, ghost4->y, ghost4->z - 5);
        }
        else if (ghost4->direction == 's')
        {
            currentCamera->setCenter(ghost4->x, ghost4->y, ghost4->z + 5);
        }
        else if (ghost4->direction == 'e')
        {
            currentCamera->setCenter(ghost4->x + 5, ghost4->y, ghost4->z);
        }
        else if (ghost4->direction == 'w')
        {
            currentCamera->setCenter(ghost4->x - 5, ghost4->y, ghost4->z);
        }
    }

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
        testWallCollision(pacmanPosition, *(*t_it), n, s, e, w, PACMAN_LEEWAY);
        pacman->collide(n, s, e, w);
        
        
        /**************************/
        /* GHOST1 WALL COLLISIONS */
        /**************************/
        ghostPosition = Vector(ghost1->x, ghost1->y, ghost1->z);
        ghostNeedsToMove = 0;
        ghostCollided = 0;
        
        /* Reset any collisions */
        n = s = e = w = 0;
        testWallCollision(ghostPosition, *(*t_it), n, s, e, w, GHOST_LEEWAY);
        if (ghost1->collide(n, s, e, w))
        {
            ghostNeedsToMove = 1;
            ghostCollided = 1;
        }

        /****************************************/
        /* GHOST 1 REACHES THE CENTER OF A TILE */
        /****************************************/
        /* Determine how far the ghost is from the center of a tile.  This determines whether he
         should look for a new opening or not. */
        distanceFromCenterX = ghost1->x - floor(ghost1->x);
        distanceFromCenterZ = ghost1->z - floor(ghost1->z);

        /* Skip this if the ghost needs to move anyway */
        if (distanceFromCenterX < 0.05 && distanceFromCenterZ < 0.05 && !ghostNeedsToMove)
        {
            /* Character is at the center of a tile. */
            ghostNeedsToMove = 1;
        }


        /************************/
        /* GHOST 1 MAKES A MOVE */
        /************************/
        if (ghostNeedsToMove) {
            /* Get the ghosts position in the map array */
            positionInMapArray = getPositionInMapArray(currentMap->columns, ghost1->getRoundedX(), ghost1->getRoundedZ());

            /* Get the surrounding tiles and make a move */
            GLint northTile, southTile, eastTile, westTile;
            northTile = southTile = eastTile =  westTile = 0;

            getSurroundingTiles(*currentMap, positionInMapArray, northTile, southTile, eastTile, westTile);

            ghost1->chooseMove(northTile, southTile, eastTile, westTile, ghostCollided, pacman->getRoundedX(), pacman->getRoundedZ());
        }
        
        
        /**************************/
        /* GHOST2 WALL COLLISIONS */
        /**************************/
        ghostPosition = Vector(ghost2->x, ghost2->y, ghost2->z);
        ghostNeedsToMove = 0;
        ghostCollided = 0;
        
        /* Reset any collisions */
        n = s = e = w = 0;
        testWallCollision(ghostPosition, *(*t_it), n, s, e, w, GHOST_LEEWAY);

        /* If the ghost collided */
        if (ghost2->collide(n, s, e, w))
        {
            ghostNeedsToMove = 1;
            ghostCollided = 1;
        }


        /****************************************/
        /* GHOST 2 REACHES THE CENTER OF A TILE */
        /****************************************/
        /* Determine how far the ghost is from the center of a tile.  This determines whether he
         should look for a new opening or not. */
        distanceFromCenterX = ghost2->x - floor(ghost2->x);
        distanceFromCenterZ = ghost2->z - floor(ghost2->z);

        /* Skip this if the ghost needs to move anyway */
        if (distanceFromCenterX < 0.05 && distanceFromCenterZ < 0.05 && !ghostNeedsToMove)
        {
            /* Character is at the center of a tile. */
            ghostNeedsToMove = 1;
        }

        /************************/
        /* GHOST 2 MAKES A MOVE */
        /************************/
        if (ghostNeedsToMove) {
            /* Get the ghosts position in the map array */
            positionInMapArray = getPositionInMapArray(currentMap->columns, ghost2->getRoundedX(), ghost2->getRoundedZ());

            /* Get the surrounding tiles and make a move */
            GLint northTile, southTile, eastTile, westTile;
            northTile = southTile = eastTile =  westTile = 0;

            getSurroundingTiles(*currentMap, positionInMapArray, northTile, southTile, eastTile, westTile);

            ghost2->chooseMove(northTile, southTile, eastTile, westTile, ghostCollided);
        }
        
        
        /**************************/
        /* GHOST3 WALL COLLISIONS */
        /**************************/
        ghostPosition = Vector(ghost3->x, ghost3->y, ghost3->z);
        ghostNeedsToMove = 0;
        ghostCollided = 0;
        
        /* Reset any collisions */
        n = s = e = w = 0;
        testWallCollision(ghostPosition, *(*t_it), n, s, e, w, GHOST_LEEWAY);
        if(ghost3->collide(n, s, e, w))
        {
            ghostNeedsToMove = 1;
            ghostCollided = 1;
        }


        /****************************************/
        /* GHOST 3 REACHES THE CENTER OF A TILE */
        /****************************************/
        /* Determine how far the ghost is from the center of a tile.  This determines whether he
         should look for a new opening or not. */
        distanceFromCenterX = ghost3->x - floor(ghost3->x);
        distanceFromCenterZ = ghost3->z - floor(ghost3->z);

        /* Skip this if the ghost needs to move anyway */
        if (distanceFromCenterX < 0.05 && distanceFromCenterZ < 0.05 && !ghostNeedsToMove)
        {
            /* Character is at the center of a tile. */
            ghostNeedsToMove = 1;
        }

        /************************/
        /* GHOST 3 MAKES A MOVE */
        /************************/
        if (ghostNeedsToMove) {
            /* Get the ghosts position in the map array */
            positionInMapArray = getPositionInMapArray(currentMap->columns, ghost3->getRoundedX(), ghost3->getRoundedZ());

            /* Get the surrounding tiles and make a move */
            GLint northTile, southTile, eastTile, westTile;
            northTile = southTile = eastTile =  westTile = 0;

            getSurroundingTiles(*currentMap, positionInMapArray, northTile, southTile, eastTile, westTile);

            ghost3->chooseMove(northTile, southTile, eastTile, westTile, ghostCollided);
        }
        
        
        /**************************/
        /* GHOST4 WALL COLLISIONS */
        /**************************/
        ghostPosition = Vector(ghost4->x, ghost4->y, ghost4->z);
        ghostNeedsToMove = 0;
        ghostCollided = 0;
        
        /* Reset any collisions */
        n = s = e = w = 0;
        testWallCollision(ghostPosition, *(*t_it), n, s, e, w, GHOST_LEEWAY);
        if(ghost4->collide(n, s, e, w))
        {
            ghostNeedsToMove = 1;
            ghostCollided = 1;
        }


        /****************************************/
        /* GHOST 4 REACHES THE CENTER OF A TILE */
        /****************************************/
        /* Determine how far the ghost is from the center of a tile.  This determines whether he
         should look for a new opening or not. */
        distanceFromCenterX = ghost4->x - floor(ghost4->x);
        distanceFromCenterZ = ghost4->z - floor(ghost4->z);

        /* Skip this if the ghost needs to move anyway */
        if (distanceFromCenterX < 0.05 && distanceFromCenterZ < 0.05 && !ghostNeedsToMove)
        {
            /* Character is at the center of a tile. */
            ghostNeedsToMove = 1;
        }

        /************************/
        /* GHOST 4 MAKES A MOVE */
        /************************/
        if (ghostNeedsToMove) {
            /* Get the ghosts position in the map array */
            positionInMapArray = getPositionInMapArray(currentMap->columns, ghost4->getRoundedX(), ghost4->getRoundedZ());
            if (positionInMapArray == 198) {
                cout << ghost4->x << endl;
                cout << ghost4->z << endl;
                cout << ghost4->getRoundedX() << endl;
                cout << ghost4->getRoundedZ() << endl;
            }
            /* Get the surrounding tiles and make a move */
            GLint northTile, southTile, eastTile, westTile;
            northTile = southTile = eastTile =  westTile = 0;

            getSurroundingTiles(*currentMap, positionInMapArray, northTile, southTile, eastTile, westTile);

            ghost4->chooseMove(northTile, southTile, eastTile, westTile, ghostCollided);
        }

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
			

			play_pacman_eating_audio();
			
			score += 10;
        }
        
        /* Avoid an error when you eat the last pellet */
        if (p_it == pelletTiles.end()) 
		//if (p_it == pelletTiles.begin()) 
        {
            break;
        }
    }

    /********************************
     * Collision With Power Pellets *
     ********************************/
    for(p_it = powerPelletTiles.begin(); p_it != powerPelletTiles.end(); ++p_it)
    {
        Vector tilePosition((*p_it)->x, 0, (*p_it)->z);
        GLdouble distance = testDistance(tilePosition, pacmanPosition);
        
        /* Eat the power pellet */
        if (distance < 0.7) {
            (*p_it)->powerPellet = false;
            powerPelletTiles.erase(p_it);

            timer2->startCountDown(15);
            enableFrenzyMode(1);
			score +=50;

        }
        
        /* Avoid an error when you eat the last pellet */
        if (p_it == powerPelletTiles.end())
        {
            break;
        }
    }
	
	if (pelletTiles.empty() && powerPelletTiles.empty())
	{
		reset(2);
		return;
	}

	/*************************
	 *GHOST/PACMAN Collisions*
	 *************************/
	if((ghost1->x<(pacman->x+1)) && (ghost1->y<(pacman->y+1)) && (ghost1->z<(pacman->z+1)))
	{
		if((ghost1->x>(pacman->x-1)) && (ghost1->y>(pacman->y-1)) && (ghost1->z>(pacman->z-1))){
			if(pacman->frenzy){
				/*ghost1->x = 9.0;
				ghost1->y = 0.2;
				ghost1->z = 11.0;*/
				ghost1->initPosition(15.0f, 0.2f, 13.0f);
				g_dead= 1;
			}
			if(!pacman->frenzy)
				dead = 1;
		}
	}

	if((ghost2->x<(pacman->x+1)) && (ghost2->y<(pacman->y+1)) && (ghost2->z<(pacman->z+1)))
	{
		if((ghost2->x>(pacman->x-1)) && (ghost2->y>(pacman->y-1)) && (ghost2->z>(pacman->z-1))){
			if(pacman->frenzy){
				/*ghost2->x = 10.0;
				ghost2->y = 0.2;
				ghost2->z = 11.0;*/
				ghost2->initPosition(14.0f, 0.2f, 13.0f);
				g_dead= 1;
			}
			if(!pacman->frenzy)
				dead = 1;
		}
	}

	if((ghost3->x<(pacman->x+1)) && (ghost3->y<(pacman->y+1)) && (ghost3->z<(pacman->z+1)))
	{
		if((ghost3->x>(pacman->x-1)) && (ghost3->y>(pacman->y-1)) && (ghost3->z>(pacman->z-1))){
			if(pacman->frenzy){
				/*ghost3->x = 11.0;
				ghost3->y = 0.2;
				ghost3->z = 11.0;*/
				ghost3->initPosition(13.0f, 0.2f, 13.0f);
				g_dead= 1;
			}
			if(!pacman->frenzy)
				dead = 1;
		}
	}

	if((ghost4->x<(pacman->x+1)) && (ghost4->y<(pacman->y+1)) && (ghost4->z<(pacman->z+1)))
	{
		if((ghost4->x>(pacman->x-1)) && (ghost4->y>(pacman->y-1)) && (ghost4->z>(pacman->z-1))){
			if(pacman->frenzy){
				/*ghost4->x = 10.0;
				ghost4->y = 0.2;
				ghost4->z = 10.0;*/
				ghost4->initPosition(12.0f, 0.2f, 13.0f);
				g_dead= 1;
			}
			if(!pacman->frenzy)
				dead = 1;
		}
	}

	if(dead)
	{
			lives--;
			dead = 0;
			/*
			pacman->x = 1.0;
			pacman->y = 0.2;
			pacman->z = 3.0;

			ghost1->x = 9.0;
			ghost1->y = 0.2;
			ghost1->z = 11.0;

			ghost2->x = 10.0;
			ghost2->y = 0.2;
			ghost2->z = 11.0;

			ghost3->x = 11.0;
			ghost3->y = 0.2;
			ghost3->z = 11.0;

			ghost4->x = 10.0;
			ghost4->y = 0.2;
			ghost4->z = 10.0;*/
			pacman->initPosition(14.0f, 0.2f, 15.0f);
			ghost1->initPosition(15.0f, 0.2f, 13.0f);
			ghost2->initPosition(14.0f, 0.2f, 13.0f);
			ghost3->initPosition(13.0f, 0.2f, 13.0f);
			ghost4->initPosition(12.0f, 0.2f, 13.0f);

			respawn = 1;
			timer1->startTimer();
			t_flag = 0;

			if(lives==-1)
				gameover = 1;

	}

	if(g_dead)
	{
		score = 1.5*score + 100;
		g_dead = 0;
	}
    
    /**********************/
    /*  MOVE CHARACTERS   */
    /**********************/
    pacman->move();
    ghost1->move();
    ghost2->move();
    ghost3->move();
    ghost4->move();

	//PACMAN'S FRENZY makes lights go crazy
	if (pacman->frenzy)
	{
	
		int s_l=rand()%4;
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
		}
		//functionKeys (GLUT_KEY_F9,0,0);

		//DISABLE ALL SPOTLIGHTS
		//functionKeys (GLUT_KEY_F9,0,0);
		//functionKeys (GLUT_KEY_F9,0,0);

		//cout << "Time: "<<timer2->getTimeLeft() << endl;

	}


	if (!timer2->getTimeLeft())
		{
			pacman->frenzy = 0;
			enableFrenzyMode(0);
			
			stop_frenzy_audio();
	
		}




    if (idleEnable)
    {	
        /* Slow Rotation */
        currentCamera->rotateY(rotStep/20);
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
    currentCamera->setViewport();
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
	if (menuEnabled)
	{
		switch (key)
		{
			case '1':
				menuEnabled=!menuEnabled;
				inMenu = !inMenu;
				break;
			case '2':
				break;
			case '3':
				break;
			/*case '4':
				menuEnabled=!menuEnabled;
				inMenu = 1;
				break;*/
			case 27:
				exit(0);
				break;
			default:
				break;
		}
	}
	else
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

			case 'z':
				offset = ++offset%3;
				ProcessMenu(offset + 2);
				break;
            
			case 'x':
				offset = ++offset%3;
				ProcessMenu(offset + 33);
				break;

			case 'c':
				ProcessMenu(29);
				break;

			case 'b':
				offset = ++offset%3;
				ProcessMenu(offset + 30);
				break;

			case 'w':
				currentCamera->moveForward(moveStep);
				break;
			case 's':
				currentCamera->moveBackward(moveStep);
				break;
			case 'a':
				currentCamera->moveLeft(moveStep);
				break;
			case 'd':
				currentCamera->moveRight(moveStep);
				break;
			case '=':
				currentCamera->zoomIn(zoomStep);
				break;
			case '-':
				currentCamera->zoomOut(zoomStep);
				break;
			case '+':
				currentCamera->zoomWithFovy(-zoomStep);
				break;
			case '_':
				currentCamera->zoomWithFovy(zoomStep);
				break;
			case ']':
				currentCamera->roll(rotStep);
				break;
			case '[':
				currentCamera->roll(-rotStep);
				break;
			case 'f':
				fullscreen = 1 - fullscreen;

				if (fullscreen) {
					enterFullscreen();
				} else {
					exitFullscreen();
				}

				break;
			case 'r':
				currentCamera = &mainCam;
				currentCamera->reset();
				break;

			//toggles menu
			case 'm':

				/*if(menuEnabled){

					menuEnabled = 0;
					timerDisplay = 1;
					g_o_display = 0;
				}
				else{*/

					menuEnabled = 1;
					timerDisplay = 0;
					lifeDisplay = 0;
					scoreDisplay = 0;
					paused = 1;
					g_o_display = 0;
				//}
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
			/*case '4':
				ProcessMenu(8);
				break;*/
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

			case 'T' :
			case 't' :
				/*if(timer1->timerIsOn){

					paused = 1;
            		timer1->stopTimer();
				}
				else{*/
					
				if(t_flag==0)
				{
					paused = 0;
					respawn = 0;
					timer1->startTimer();
				}
				t_flag++;
				//}
				break;

			default:
				cout << key << endl;
		}
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
			isWireFrame = false;
            break;
            
        case 4:
            glShadeModel(GL_FLAT);
			isWireFrame = false;
            break;
            
            /* Pacman-cam */
        case 5:
            switchCamera(0);
            break;
            
            /* Ghost1-Cam */    
        case 6:
            switchCamera(1);
            break;
            
            /* Ghost2-Cam */
        case 7:
            switchCamera(2);
            break;
            
            /* Ghost3-Cam */    
        case 8:
            switchCamera(3);
            break;
            
            /* Ghost4-Cam */
        case 9:
            switchCamera(4);
            break;
            
            /* Light1-Cam */
        case 10:
            switchCamera(5);
            break;
            
            /* Light2-Cam */
        case 11:
            switchCamera(6);
            break;
            
            /* Light3-Cam */
		case 12:
            switchCamera(7);
            break;
            
            /* Light4-Cam */
		case 13:
            switchCamera(8);
            break;
            
            /* Enable Ambient Light */
        case 14:
            glEnable(GL_LIGHT0);
            ambient_lighting_enabled = 1;
            break;
            
            /* Disable Ambient Light */
        case 15:
            glDisable(GL_LIGHT0);
            ambient_lighting_enabled = 0;
            break;
            
            /* Initial-Cam */
        case 16:
            switchCamera(9);
            break;
            
            /* Enable/Disable Color Material */
        case 17:
            if(color_material_enabled)
            color_material_enabled = 0;
            else
            color_material_enabled = 1;
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
            pacman->outfit = 0;
            break;
            
            /* Pacman Outfit 2 */
        case 31:
            pacman->outfit = 1;
            break;
            
            /* Pacman Outfit 3 */
        case 32:
            pacman->outfit = 2;
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
		   currentCamera = &mainCam;
		   currentCamera->reset();
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
    	   if(ambient_lighting_enabled)
           ProcessMenu(15);
    	   else ProcessMenu(14);
           break;
           
/*
       case GLUT_KEY_UP:
           currentCamera->rotateZ(-rotStep);
           break;
           
       case GLUT_KEY_DOWN:
           currentCamera->rotateZ(rotStep);
           break; 

		case GLUT_KEY_RIGHT:
           currentCamera->rotateY(rotStep);
           break;
           
        case GLUT_KEY_LEFT:
           currentCamera->rotateY(-rotStep);
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




int main (int argc, char *argv[])
{
    // GLUT initialization. Enable double buffer mode
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(width, height);
	glutCreateWindow("Pacman3D beta");
    //glutPositionWindow(0, 0);
    
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

    initModels();
    
    // Enter GLUT loop.
	glutMainLoop();

    return 0;
}


void initMenu()
{
    GLint nModeMenu; // menu identifier used when calling glutsetmenu
	nModeMenu = glutCreateMenu(ProcessMenu);
	glutAddMenuEntry("Solid",1);
	glutAddMenuEntry("Wire",2);
    //glutAddMenuEntry("-------------", 0);
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


void initModels()
{
	//save lighting context in an array
	for (int i=0;i<6;i++)
	{
		//array to store lighting
		for(int j=0;j<4;j++)
		{
			if(i==0)
				initalLightingValues[i][j]=lightAmbient[j];
			if(i==1)
				initalLightingValues[i][j]=lightDiffuse[j];
			if(i==2)
				initalLightingValues[i][j]=lightSpecular[j];
			if(i==3)
				initalLightingValues[i][j]=spotlightAmbient[i];
			if(i==4)
				initalLightingValues[i][j]=spotlightDiffuse[i];
			if(i==5)
				initalLightingValues[i][j]=spotlightSpecular[i];
		}
	}

	//Initializing lives, timer
	lives = 3;

    //init scene
    glShadeModel(GL_SMOOTH);

    lamp1 = new Lamp(GL_LIGHT1, spotlightDirection1);
    lamp2 = new Lamp(GL_LIGHT2, spotlightDirection2);
    lamp3 = new Lamp(GL_LIGHT3, spotlightDirection3);
    lamp4 = new Lamp(GL_LIGHT4, spotlightDirection4);

    setupLighting();
    
    /* intitialize timers */
    timer1 = new Timer((string)"PRESS 't' TO START");
    timer2 = new Timer((string)"eat power pellets to power up");

	menu1 = new Menu();

	/* init characters */
    pacman = new Pacman();
    pacman->initPosition(14.0f, 0.2f, 15.0f);
    
    ghost1 = new Ghost(1.0, 0.0, 0.0);
    ghost2 = new Ghost(0.0, 1.0, 0.0);
    ghost3 = new Ghost(1.0, 0.5, 0.7);
    ghost4 = new Ghost(1.0, 0.5, 0.0);
    
    ghost1->initPosition(15.0f,  0.2f, 13.0f);
    ghost2->initPosition(14.0f, 0.2f, 13.0f);
    ghost3->initPosition(13.0f, 0.2f, 13.0f);
    ghost4->initPosition(12.0f, 0.2f, 13.0f);
    
    /* init map */
    srand(time(NULL)); //seed rand for pellet colours
	
	loadMap(level);

    /* init cameras */
    initCameras();
    
    glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
    glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
    
    /* Init audio */
    

    atexit(cleanup);    
}


void setupLighting()
{
	/*
    // Light values and coordinates
    GLfloat lightModelIntensity[] = { 0.1f, 0.1f, 0.1f, 1.0f };

    //Ambient Light Values


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

    lamp1->setAmbDiffSpec(spotlightAmbient, spotlightDiffuse, spotlightSpecular);
    lamp2->setAmbDiffSpec(spotlightAmbient, spotlightDiffuse, spotlightSpecular);
    lamp3->setAmbDiffSpec(spotlightAmbient, spotlightDiffuse, spotlightSpecular);
    lamp4->setAmbDiffSpec(spotlightAmbient, spotlightDiffuse, spotlightSpecular);
    
    /* setup where the lamps are modeled */
    lamp1->setModelPosition(streetlightPosition1);
    lamp2->setModelPosition(streetlightPosition2);
    lamp3->setModelPosition(streetlightPosition3);
    lamp4->setModelPosition(streetlightPosition4);
    
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
    if(ambient_lighting_enabled) glEnable(GL_LIGHT0);
    
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
	delete menu1;
	delete timer1;
	delete timer2;
    delete lamp1;
    delete lamp2;
    delete lamp3;
    delete lamp4;
	//stop_intro_audio();
}


void enterFullscreen()
{
    glutFullScreen();
}


void exitFullscreen()
{
    glutReshapeWindow(WIDTH, HEIGHT);
    glutPositionWindow(0, 0);
}


void initCameras()
{
    currentCamera = &mainCam;

    /****************************************
     *NOTE: Changed viewing direction for better vision (from 2 * sqrt(2)) on lamps
     ****************************************/

    lamp1Cam.setPosition(lamp1->x, lamp1->y + 5, lamp1->z);
    lamp1Cam.setCenter(lamp1->x + 5, lamp1->y, lamp1->z + 5);

    lamp2Cam.setPosition(lamp2->x, lamp2->y + 5, lamp2->z);
    lamp2Cam.setCenter(lamp2->x - 5, lamp2->y - 4, lamp2->z + 5);

    lamp3Cam.setPosition(lamp3->x, lamp3->y + 5, lamp3->z);
    lamp3Cam.setCenter(lamp3->x + 5, lamp3->y - 4, lamp3->z - 5);

    lamp4Cam.setPosition(lamp4->x, lamp4->y + 5, lamp4->z);
    lamp4Cam.setCenter(lamp4->x - 5, lamp4->y - 4, lamp4->z - 5);
}


void switchCamera(GLuint camera)
{
    pacmanCam.enabled = 0;
    ghost1Cam.enabled = 0;
    ghost2Cam.enabled = 0;
    ghost3Cam.enabled = 0;
    ghost4Cam.enabled = 0;

    switch (camera) {
        case 0:
            pacmanCam.enabled = 1;
            currentCamera = &pacmanCam;
            break;

        case 1:
            ghost1Cam.enabled = 1;
            currentCamera = &ghost1Cam;
            break;

        case 2:
            ghost2Cam.enabled = 1;
            currentCamera = &ghost2Cam;
            break;

        case 3:
            ghost3Cam.enabled = 1;
            currentCamera = &ghost3Cam;
            break;

        case 4:
            ghost4Cam.enabled = 1;
            currentCamera = &ghost4Cam;
            break;

        case 5:
            currentCamera = &lamp1Cam;
            break;

        case 6:
            currentCamera = &lamp2Cam;
            break;

        case 7:
            currentCamera = &lamp3Cam;
            break;

        case 8:
            currentCamera = &lamp4Cam;
            break;

        default:
            currentCamera = &mainCam;
            break;
    }
}

void reset(GLuint loadLevel)
{
	currentCamera = &mainCam;
	currentCamera->reset();

	ghost1->initPosition(15.0f,  0.2f, 13.0f);
    ghost2->initPosition(14.0f, 0.2f, 13.0f);
    ghost3->initPosition(13.0f, 0.2f, 13.0f);
    ghost4->initPosition(12.0f, 0.2f, 13.0f);

	pacman->initPosition(14.0f, 0.2f, 15.0f);
	enableFrenzyMode(0);

	loadMap(loadLevel);

	t_flag = 0;
	paused = 1;
	timer1->stopTimer();
}

void loadMap(GLuint load)
{
	level = load;

	if(level == 1)
	{

		openMap(); // Reading map from file to map 
		map1.initializeMap(map, 28, 28);
		currentMap = &map1;
	}
	if(level == 2)
	{
		openMap(); // Reading map from file to map 
		map2.initializeMap(map, 28, 28);
		currentMap = &map2;
	}



	walls.clear();
	pelletTiles.clear();
	powerPelletTiles.clear();

	/* Create a vector of walls for collision detection */
    /* Create another vector of tiles with pellets for more detection */
    vector<Tile *>::const_iterator t_it;    
    for (t_it = currentMap->tiles.begin(); t_it != currentMap->tiles.end(); ++t_it) 
    {      
        if ((*t_it)->type == 'W') {
            walls.push_back((*t_it));
        }
        
        if ((*t_it)->type == 'Z') {
            pelletTiles.push_back((*t_it));
        }

        if ((*t_it)->type == 'X') {
            powerPelletTiles.push_back((*t_it));
        }
    }
    

}
