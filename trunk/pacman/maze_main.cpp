


#include "maze.h"
#include <GL/glut.h>

using namespace std;




// Some of the code in this main.cpp was used from OpenGl Superbible 4 SB-AllSource source code. This book is a great reference 
// source as well as a learning tool for OpenGL. http://www.starstonesoftware.com/OpenGL/new_page_1.htm provides various source 
// code examples used.


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Rotation amounts
static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;
static GLfloat xTranslate = 0.0f;
static GLfloat yTranslate = 0.0f;

// Initial size of graphics window.
const int WIDTH  = 600;
const int HEIGHT = 400;

// Current size of window.
int width  = WIDTH;
int height = HEIGHT;

// Mouse positions, normalized to [0,1].
double xMouse = 0.5;
double yMouse = 0.5;

// Bounds of viewing frustum.

double nearPlane =  5;
double farPlane  = 15;

// Viewing angle.
double fovy = 40.0;

bool FlatWireMode = false; // Flat = false, Wire = True


///////////////////////////////////////////////////////////////////////////////
// Reset flags as appropriate in response to menu selections
void ProcessMenu(int value)
	{
	switch(value)
		{
		case 1:
			FlatWireMode = false;
			break;

		case 2:
			FlatWireMode = true;
			break;
	}

	glutPostRedisplay();
}



// Change viewing volume and viewport.  Called when window is resized
void ChangeSize(int w, int h)
{
    GLfloat nRange = 120.0f;
    // Prevent a divide by zero
    if(h == 0)
        h = 1;

    // Set Viewport to window dimensions
    glViewport(0, 0, w, h);

    // Reset coordinate system
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Establish clipping volume (left, right, bottom, top, near, far)
    if (w <= h) 
        glOrtho (-nRange, nRange, -nRange*h/w, nRange*h/w, -nRange*2.0f, nRange*2.0f);
    else 
        glOrtho (-nRange*w/h, nRange*w/h, -nRange, nRange, -nRange*2.0f, nRange*2.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}



// This function does any needed initialization on the rendering
// context.  Here it sets up and initializes the lighting for
// the scene.
void SetupRC()
{
    // Light values and coordinates
    GLfloat  whiteLight[] = { 0.45f, 0.45f, 0.45f, 1.0f };
    GLfloat  sourceLight[] = { 0.25f, 0.25f, 0.25f, 1.0f };
    GLfloat	 lightPos[] = { -50.f, 25.0f, 250.0f, 0.0f };

    glEnable(GL_DEPTH_TEST);	// Hidden surface removal
    glFrontFace(GL_CCW);		// Counter clock-wise polygons face out
    glEnable(GL_CULL_FACE);		// Do not calculate inside of jet

    // Enable lighting
    glEnable(GL_LIGHTING);

    // Setup and enable light 0
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT,whiteLight);
    glLightfv(GL_LIGHT0,GL_AMBIENT,sourceLight);
    glLightfv(GL_LIGHT0,GL_DIFFUSE,sourceLight);
    glLightfv(GL_LIGHT0,GL_POSITION,lightPos);
    glEnable(GL_LIGHT0);

    // Enable color tracking
    glEnable(GL_COLOR_MATERIAL);
	
    // Set Material properties to follow glColor values
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

    // Black blue background
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f );

}

// Respond to arrow keys
void SpecialKeys(int key, int x, int y)
{
	if(key == GLUT_KEY_UP)

		yTranslate += 5.0f;

	if(key == GLUT_KEY_DOWN)
		
		yTranslate -= 5.0f;

	if(key == GLUT_KEY_LEFT)
		xTranslate -= 5.0f;

	if(key == GLUT_KEY_RIGHT)
		
		xTranslate += 5.0f;

	if(key == GLUT_KEY_PAGE_UP)
		xRot -= 1.0f;

	if(key == GLUT_KEY_PAGE_DOWN)
		xRot += 1.0f;

	if(key == GLUT_KEY_F1)
	{
		xRot = 0;
		yRot = 0;
		xTranslate = 0;
		yTranslate = 0;
	}           
        xRot = (GLfloat)((const int)xRot % 360);
        yRot = (GLfloat)((const int)yRot % 360);

	// Refresh the Window
	glutPostRedisplay();
}




////////////////////////////////////////////////////////////////////////////////////////////////
// Draw the ground as a series of triangle strips
void DrawGround()
{
	glBegin(GL_QUADS);
	
		glColor3f(0.75f,0.75f,0.75f);
		glVertex3f(-500,0,500);
		glVertex3f(500,0,500);
		glVertex3f(500,0,-500);
		glVertex3f(-500,0,-500);

	glEnd();

}


// Variables.
double alpha = 0;                                  // Set by idle function.
double beta = 0;                                   // Set by mouse X.
double Distance = 5.0;                             // Set by mouse Y.


// Called to draw scene
void RenderScene(void)
{
    float fZ,bZ;

	// Draw everything as wireframe only, if flag is set
	if(FlatWireMode == true)
	{
		glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
	}

	// Clear the window with current clearing color
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Translate using Y mouse.
    alpha = 180 * yMouse;
    glRotatef(alpha, 0, 1, 0);

    	// Rotation using X mouse.
    	beta = 180.0 * xMouse;
    	glRotatef(beta, 1, 0, 0);



    // Draw model axes in centre of room.
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


    fZ = 100.0f;
    bZ = -100.0f;

    // Save the matrix state and do the rotations

    glPushMatrix();
    glRotatef(xRot, 1.0f, 0.0f, 0.0f);
    glRotatef(yRot, 0.0f, 1.0f, 0.0f);
	glTranslatef(xTranslate,0.0f,0.0f);
	glTranslatef(0.0f,yTranslate,0.0f);
  
	//DrawGround();

	DrawMaze();   
 
	
    // Restore the matrix state
    glPopMatrix();


    // Buffer swap
    glutSwapBuffers();
}

void mouseMovement (int mx, int my)
{
	// Normalize mouse coordinates.
	xMouse = double(mx) / double(width);
	yMouse = 1 - double(my) / double(height);

	// Redisplay image.
	glutPostRedisplay();
}

int main2(int argc, char *argv[])
{
	int nModeMenu;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Pacman Beta v0.1");


	// Create the Menu
	nModeMenu = glutCreateMenu(ProcessMenu);
	glutAddMenuEntry("Flat ",1);
	glutAddMenuEntry("Wire",2);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

    glutReshapeFunc(ChangeSize);
    glutSpecialFunc(SpecialKeys);
    glutDisplayFunc(RenderScene);
	glutMotionFunc(mouseMovement);
    SetupRC();
	
    glutMainLoop();
    
    return 0;
}
