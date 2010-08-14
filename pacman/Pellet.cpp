/*
 * Pellet.cpp
 *
 *  Created on: 2010-08-08
 *      Author: sid
 */
#include <GL/glut.h>

#include "Pellet.h"
#include "Material.h"
#include <iostream>
//#include "texture.h"

using namespace std;

extern GLuint pelletTextureID;
extern GLfloat pellet_color[4];

Pellet::Pellet(){

	//pelletTextureID = LoadTextureRAW("stone.raw", 1, 256, 256);
	cout << "creating pellet.. " << endl;

	 pellet_color[0] = (rand()%255)/255.0f;
	 pellet_color[1] = (rand()%255)/255.0f;
	 pellet_color[2] = (rand()%255)/255.0f;
	 pellet_color[3] = 1.0f;

}

void Pellet::setColor(){


	 pellet_color[0] = (rand()%255)/255.0f;
	 pellet_color[1] = (rand()%255)/255.0f;
	 pellet_color[2] = (rand()%255)/255.0f;
	 pellet_color[3] = 1.0f;

}

void Pellet::drawPellet(GLboolean texture, GLboolean power){

	/*
	 this->pellet_color[0] = (rand()%255)/255.0f;
	 this->pellet_color[1] = (rand()%255)/255.0f;
	 this->pellet_color[2] = (rand()%255)/255.0f;
	 this->pellet_color[3] = 1.0f;
	*/

			if (texture) {
	            glEnable(GL_TEXTURE_GEN_S);
	            glEnable(GL_TEXTURE_GEN_T);

	            glBindTexture(GL_TEXTURE_2D, this->pelletTextureID);
	        }

	        //glTranslatef(0.0, 0.1, 0.0);
	        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, pellet_color);
	        glColor4fv(pellet_color);
	        glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, high_shininess);
	        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);

	        if(power)
				glutSolidSphere(0.4, 20, 20);
	        else
	        	glutSolidSphere(0.2, 20, 20);

	        glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, no_shininess);
	        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, no_specular);

	        if (texture) {
	            glDisable(GL_TEXTURE_GEN_S);
	            glDisable(GL_TEXTURE_GEN_T);
	        }

}
