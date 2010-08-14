/*
 * quiz3.cpp
 *
 *  Created on: 2010-08-05
 *      Author: sid
 *      Student ID: 9209905
 *      Team #8
 *The following code is based off sampleglprogram.cpp and our project

- (1) Set the background color of the world gray.

- (3) Draw (x,y,z) axes as lines originating at (0,0,0) to their
      positive direction, 2.5 units in length, x: green, y: red,
      z: blue.

- (4) Extract the models of the Floor Tile and the Pellet from your
      project. The models should be texture-free.

- (1) Place the Floor Tile at the origin, 1x1x0.5 units in size.
      Place the Pellets covering the Tile such that there are 8
      of them there spred evenly on the sides as roughly ASCII
      illustrated:
      
    ____
   /ooo/|
  /o o/ |
 /ooo/ /
/---/ /
|   |/
|___|

- (2) Place a camera looking at the scene as in PA1.

- (4) Model a quadric cone at the top of the Tile pointing upward
      the Y axis. Its bottom diameter should be the same as that of
      the pellets. Color it as you did for the Pellets. Use whatever
      transformations necessary to achieve that. The length of the code
      is 1 unit.

- (1) Allow for smooth and flat shading with a key.

- (6) Model your student ID's first and last digits as old Timex watch using
      parallelopipeds (3D "cubes", scaled approprately) standing on both sides
      of the tile along X, unit tall, .5 unit deep, unit wide. You can
      keep them as wireframe or fill in with any color you like
      as long as they are visible.
   ___    ___
 /|___| /|___|
|/___/ |/___/

- (8) Apply various transformations below to the Tile with the Pellets and the cone
      (the model), BUT NOT TO YOUR DIGITS NOR AXES. Pay attention to the order.
    - key '1': Rotate the model 60 degrees about Y and translate it 2 units over Z
    - key '2': Scale the model by 3x, 0.5y, and -0.5z
    - key '3': Combine '1' and '2' with the scaling being last applied to the model.
    - key '4': Combine '1' and '2' with the scaling being first applied to the model.
    - key '5': Rotate the model about the fixed point (4.0, 5.0, 6.0) 45 degrees with the 1.0, 2.0 and 3.0 components.
    - key '6': Combine '4' and '5' with the '5' being last applied to the model.
    - key 'R': key to reset to the initial state before any transformation.

*/

#include <cstdlib>
#include <GL/glut.h>
#include <cmath>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <ctime>

#include "Tile.h"

using namespace std;

void ProcessMenu(int value);
void resetViewParameters();
void functionKeys (int key, int x, int y);
void graphicKeys (unsigned char key, int x, int y);


/**************************
 Scene Objects
 **************************/
static Tile *tile3;
//static Tile *tile0;

// Initial size of graphics window on your screen in pixels.
#define WIDTH 800
#define HEIGHT 600

// Current size of window (will change when you resize window)
GLint width  = WIDTH;
GLint height = HEIGHT;

// Mouse positions, normalized to [0,1].
double xMouse = 0.5;
double yMouse = 0.5;

// View Paramaters

GLdouble nearPlane =  1.5;
GLdouble farPlane  = 120;
GLdouble fovy = 60; // Viewing angle.

/* Rotation */
GLdouble yaw = 0;                                     // rotation angle about Y axis.
GLdouble pitch = 0;                                   // rotation angle about X axis.
GLdouble roll = 0;

/* misc */
GLdouble halfway = - (farPlane + nearPlane) / 2;	   // half way between near and far planes
bool useSmoothShading = 0;
bool isWireFrame = 1;
char t=0;                                                //choice of transform

/* Camera */
/* Set initial values */
const GLdouble initial_eye[3] = {3.0, 3.0, 3.0};
const GLdouble initial_center[3] = {0, 0, 0};


GLdouble eye_x=3.0;
GLdouble eye_y=3.0;
GLdouble eye_z=3.0;

GLdouble center_x=0.0;
GLdouble center_y=0.0;
GLdouble center_z=0.0;

GLdouble up_x=0.0;
GLdouble up_y=1.0;
GLdouble up_z=0.0;

GLdouble fw_rw=0;
GLdouble up_dn=0;
GLdouble lt_rt=0;

const GLdouble RotSTEP = 0.2;
const GLdouble mvSTEP = 5.0;
const GLdouble ALL_ROUND = 360;

void resetViewParameters()
{
	nearPlane =  60;
	farPlane  = 120;
    fovy = 60;

    //reset camera
				eye_x = initial_eye[0];
                eye_y = initial_eye[1];
                eye_z = initial_eye[2];

                center_x = initial_center[0];
                center_y = initial_center[1];
                center_z = initial_center[2];

                fw_rw = 0;
                up_dn = 0;
                lt_rt = 0;

                yaw = 0;
                pitch  = 0;
                roll = 0;

}


void setView()
{
	// set Projection Matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
    gluPerspective(fovy, (GLfloat) 1.0, nearPlane, farPlane);

				//set camera parameters
				eye_x = initial_eye[0];
                eye_y = initial_eye[1];
                eye_z = initial_eye[2];

                center_x = initial_center[0];
                center_y = initial_center[1];
                center_z = initial_center[2];

                fw_rw = 0;
                up_dn = 0;
                lt_rt = 0;

                yaw = 0;
                pitch  = 0;
                roll = 0;

}

void drawAxes(){

	glPushMatrix();
		glBegin(GL_LINES);
		// X axis
		glColor3f(0, 1, 0); //greeen
		glVertex3f(0, 0, 0);
		glVertex3f(3, 0, 0);
		// Y axis
		glColor3f(1, 0, 0); //red
		glVertex3f(0, 0, 0);
		glVertex3f(0, 3, 0);
		// Z axis
		glColor3f(0, 0, 1); //blue
		glVertex3f(0, 0, 0);
		glVertex3f(0, 0, 3);
		glEnd();
    glPopMatrix();
}

void draw9(){

	glColor3f(0.0,0.5,0.7);
	//top long
	glPushMatrix();
	glTranslatef(-1,0.5-0.0625,0);
	glScalef(2,0.25,1);
	glutSolidCube(0.25);
	glPopMatrix();

	//left short
	glPushMatrix();
	glTranslatef(-1.25+0.0625/2,0.375-0.0625/2,0);
	glScalef(0.25,1,1);
	glutSolidCube(0.25);
	glPopMatrix();

	//middle long
	glPushMatrix();
	glTranslatef(-1,0.25,0);
	glScalef(2,0.25,1);
	glutSolidCube(0.25);
	glPopMatrix();

	//right long
	glPushMatrix();
	glTranslatef(-0.78125,0.21875,0);
	glScalef(0.25,2,1);
	glutSolidCube(0.25);
	glPopMatrix();

	//bottom
	glPushMatrix();
	glTranslatef(-1,0,0);
	glScalef(2,0.25,1);
	glutSolidCube(0.25);
	glPopMatrix();

}
//you should draw whatever at the origin then translate;

void draw5(){

	glColor3f(0.0,0.7,0.5);
	//top long
		glPushMatrix();
		glTranslatef(1,0.5-0.0625,0);
		glScalef(2,0.25,1);
		glutSolidCube(0.25);
		glPopMatrix();


	//left short
		glPushMatrix();
		glTranslatef(1.25-0.0625/2,0.125+0.0625/2,0);
		glScalef(0.25,1,1);
		glutSolidCube(0.25);
		glPopMatrix();


	//middle long
		glPushMatrix();
		glTranslatef(1,0.25,0);
		glScalef(2,0.25,1);
		glutSolidCube(0.25);
		glPopMatrix();



	//right short
		glPushMatrix();
		glTranslatef(0.75+0.0625/2,0.375-0.0625/2,0);
		glScalef(0.25,1,1);
		glutSolidCube(0.25);
		glPopMatrix();


	//bottom
		glPushMatrix();
		glTranslatef(1,0,0);
		glScalef(2,0.25,1);
		glutSolidCube(0.25);
		glPopMatrix();

}

void drawModelthing(){

	glPushMatrix();
		glTranslatef(0,0.25,0);
		glScalef(0.5,0.5,0.5);
		glRotatef(-90,1,0,0);
		glutSolidCone(0.5,1,20,20);
	glPopMatrix();

	glPushMatrix();
		tile3->draw(0,0);
	glPopMatrix();


}

void setupLighting(){

	GLfloat lightModelIntensity[] = { 0.1f, 0.1f, 0.1f, 1.0f };

	    /* Ambient Light Values */

	    GLfloat lightAmbient[]  = { 0.7f, 0.7f, 0.7f, 1.0f };
	    GLfloat lightDiffuse[]  = { 0.7f, 0.7f, 0.7f, 1.0f };
	    GLfloat lightSpecular[] = { 0.7f, 0.7f, 0.7f, 1.0f };
	    GLfloat lightPosition[] = { 1.0f, 0.0f, 0.0f, 0.0f }; /* Point down Y-Axis */
	/*
	 *
	 */

	    /* Setup and enable light 0 */
	       glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lightModelIntensity);
	       glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
	       glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
	       glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);
	       glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
	       glEnable(GL_LIGHT0);

	       glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	       glEnable(GL_BLEND);
	       glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


}

// This function is called to display the scene.
void display ()
{
	setupLighting();
	//set background color
    glClearColor(0.5,0.5,0.5,1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // set modelling mode
	glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    //update camera position
    GLfloat eye_position[3] = { eye_x+lt_rt, eye_y+up_dn, eye_z+fw_rw };
    GLfloat center_position[3] = { center_x+lt_rt, center_y+up_dn, center_z+fw_rw };

    //set camera
    gluLookAt(eye_position[0], eye_position[1], eye_position[2],
              center_position[0], center_position[1], center_position[2],
              up_x, up_y, up_z);

    //rotate camera - yaw pitch roll

    glRotatef(pitch, up_y*(center_z - eye_z) - up_z*(center_y - eye_y),
                 up_z*(center_x - eye_x) - up_x*(center_z - eye_z),
                 up_x*(center_y - eye_y) - up_y*(center_x - eye_x));
   	glRotatef(yaw, up_x, up_y, up_z);
   	glRotatef(roll, center_x - eye_x, center_y - eye_y, center_z - eye_z);


   	//OpenGL rendering parameters
   			if(isWireFrame)
   		       glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
   		    else
   		       glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);

   		    if(useSmoothShading)
   		    	glShadeModel(GL_SMOOTH);
   		    else
   		    	glShadeModel(GL_FLAT);

   		    glEnable(GL_COLOR_MATERIAL);

   	//drawing routines
   	draw9();
   	draw5();
   	drawAxes();

   	//draw ghost with different transforms based on choice..
   	switch(t){

   		case 1 :

   			//key '1': Rotate Ghost 45 degrees about Z and translate it 1 unit over X
   			glPushMatrix();
   			glTranslatef(-1,0,0);
   			glRotatef(45,0,0,1);
			
   			drawModelthing();
   			
			glPopMatrix();
   			break;


   		case 2 :

   			//Scale Ghost by -0.5x, 2y, and 3z
   			glPushMatrix();
   			glScalef(0.5,2,3);
			
   			drawModelthing();

   			
			glPopMatrix();
 		 	break;

   		case 3 :

   			//Combine '1' and '2' with the scaling being last applied to the model.
   			glPushMatrix();
   			glScalef(0.5,2,3);
   			glTranslatef(-1,0,0);
   			glRotatef(45,0,0,1);
			
   			drawModelthing();

   			
			glPopMatrix();
   			break;


   		case 4 :
   			//Combine '1' and '2' with the scaling being applied first to the model.
   			glPushMatrix();
   			glTranslatef(-1,0,0);
   			glRotatef(45,0,0,1);
   			glScalef(0.5,2,3);
			
   			drawModelthing();

   			
			glPopMatrix();
   			break;

   		case 5 :
 		  //"key '5': Rotate Ghost about the fixed point (4.0, 5.0, 6.0) 45 degrees with the 1.0, 2.0 and 3.0 components."<<endl

   			glPushMatrix();
   			glTranslatef(4.0, 5.0, 6.0);
   			glRotatef(45,1,2,3);
   			glTranslatef(-4.0, -5.0, -6.0);

   			glTranslatef(-1,0,0);
   			glRotatef(45,0,0,1);
   			glScalef(0.5,2,3);
			
   			drawModelthing();

   			
			glPopMatrix();

   			break;

   		case 6 :
			//   "key '6': Combine '4' and '5' with the '5' being last."<<endl

   			glPushMatrix();
   			glTranslatef(-4.0, -5.0, -6.0);
   			glRotatef(45,1,2,3);
			
   			drawModelthing();

   			
			glTranslatef(4.0, 5.0, 6.0);
   			glPopMatrix();

   			break;

   		default:
   			
   			drawModelthing();

   			break;

   		}

    // now swap buffer
    glutSwapBuffers();

}

// Respond to window resizing, preserving proportions.
// Parameters give new window size in pixels.
void reshapeMainWindow (int newWidth, int newHeight)
{
	glEnable(GL_DEPTH_TEST);
  	width = newWidth;
	height = newHeight;
	glViewport(0, 0, width, height); //specifies the affine transformation of x and y from normalized device coordinates to window coordinates
    setView();
	glMatrixMode (GL_MODELVIEW);

	//update camera position
	 GLfloat eye_position[3] = { eye_x+lt_rt, eye_y+up_dn, eye_z+fw_rw };
	 GLfloat center_position[3] = { center_x+lt_rt, center_y+up_dn, center_z+fw_rw };

    gluLookAt(eye_position[0], eye_position[1], eye_position[2],
              center_position[0], center_position[1], center_position[2],
              0, 1, 0);
}

// Display Help.
void help()
{
   cout <<      "key '1': Rotate Ghost 45 degrees about Z and translate it 1 unit over X" << endl
		   <<   "key '2': Scale Ghost by -0.5x, 2y, and 3z" << endl
		   <<   "key '3': Combine '1' and '2' with the scaling being last applied to the model." <<endl
		   <<   "key '4': Combine '1' and '2' with the scaling being first applied to the model."
		   <<   "key '5': Rotate Ghost about the fixed point (4.0, 5.0, 6.0) 45 degrees with the 1.0, 2.0 and 3.0 components."<<endl
		   <<   "key '6': Combine '4' and '5' with the '5' being last."<<endl
		   <<   "key 'R': key to reset to the initial state"<<endl
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

        case '1':
            //Rotate Ghost 45 degrees about Z and translate it 1 unit over X
        	t=1;

            break;

        case '2':
        	 //Scale Ghost by -0.5x, 2y, and 3z
        	t=2;

        	break;
        case '3':
        	//Combine '1' and '2' with the scaling being last applied to the model.
        	t=3;

            break;

        case '4':
        	//Combine '1' and '2' with the scaling being first applied to the model.
        	t=4;

        	break;

        case '5':
        	//Rotate Ghost about the fixed point (4.0, 5.0, 6.0) 45 degrees with the 1.0, 2.0 and 3.0 components.
        	t=5;
            break;

        case '6':
        	//Combine '4' and '5' with the '5' being last.
        	t=6;

            break;
        case 'r':
        	//key to reset to the initial state
        	t=0;
        	resetViewParameters();
        	break;

        case '7':
            //toggle shading
        	ProcessMenu('1');
            break;

        case '8':
            //toggle wireframe
        	ProcessMenu('2');
            break;

        case ']':
                    roll -= 10*RotSTEP;
        		    if (roll < -ALL_ROUND) {
                        roll += ALL_ROUND;
                    }
                    break;

        case '[':
                    roll += 10*RotSTEP;
                    if (roll > -ALL_ROUND) {
                        roll += ALL_ROUND;
                    }
                    break;

        case 'w':
                    fw_rw -= 0.2*mvSTEP;
                    break;
                case 's':
                    fw_rw += 0.2*mvSTEP;
                    break;
                case 'a':
                    lt_rt -= 0.2*mvSTEP;
                    break;
                case 'd':
                    lt_rt += 0.2*mvSTEP;
                    break;
        		case ',':
        			up_dn -= 0.2*mvSTEP;
                    break;
        		case '.':
        			up_dn += 0.2*mvSTEP;
                    break;


   case 'i':
              pitch += 10*RotSTEP;
              if (pitch > ALL_ROUND){
                  pitch -= ALL_ROUND;
              }
              break;

   case 'k':
              pitch -= 10*RotSTEP;
              if (pitch < -ALL_ROUND){
                  pitch += ALL_ROUND;
              }
              break;

   case 'l':
               yaw -= 10*RotSTEP;
   		    if (yaw < -ALL_ROUND) {
                   yaw += ALL_ROUND;
               }
               break;

   case 'j':
               yaw += 10*RotSTEP;
               if (yaw > -ALL_ROUND) {
                   yaw += ALL_ROUND;
               }
               break;
        default:
            cout << key <<  " not mapped" << endl;
	}
    glutPostRedisplay();
}

//updates the scene according to menu selection
void ProcessMenu(int value)
{
	switch(value)
	{
		case 1:

			if(isWireFrame)
				isWireFrame = false;
			else
				isWireFrame = true;

			break;

		case 2:
			if(useSmoothShading)
				useSmoothShading = false;
						else
				useSmoothShading = true;

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

   case GLUT_KEY_UP:
              pitch += 10*RotSTEP;
              if (pitch > ALL_ROUND){
                  pitch -= ALL_ROUND;
              }
              break;

   case GLUT_KEY_DOWN:
              pitch -= 10*RotSTEP;
              if (pitch < -ALL_ROUND){
                  pitch += ALL_ROUND;
              }
              break;

   case GLUT_KEY_RIGHT:
               yaw -= 10*RotSTEP;
   		    if (yaw < -ALL_ROUND) {
                   yaw += ALL_ROUND;
               }
               break;

   case GLUT_KEY_LEFT:
               yaw += 10*RotSTEP;
               if (yaw > -ALL_ROUND) {
                   yaw += ALL_ROUND;
               }
               break;
   }

   glutPostRedisplay();
}

void cleanup()
{
    /* Clean up */
    delete tile3;

}

int main (int argc, char **argv)
{
    // GLUT initialization. Enable double buffer mode
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(width, height);
	glutCreateWindow("Pacman3D Quiz");

	int nModeMenu; // menu identifier used when calling glutsetmenu
	nModeMenu = glutCreateMenu(ProcessMenu);
	glutAddMenuEntry("Toggle Solid / Wire Frame",1);
	glutAddMenuEntry("Toggle Smooth / Flat",2);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

	// Register call backs for standard tasks such as:
	// display, windowresize, keypress, functionkey press, mouse movement.
	glutDisplayFunc(display);
	glutReshapeFunc(reshapeMainWindow);
	glutKeyboardFunc(graphicKeys);

    // Display help.
	help();

	/* init objects */

    tile3 = new Tile('N',0,0);
	//Tile type = without pellet
	//Tile Position = origin

    atexit(cleanup);

    // Enter GLUT loop.
	glutMainLoop();
	return 0;

}

