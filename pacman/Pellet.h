/*
 * Pellet.h
 *
 *  Created on: 2010-08-08
 *      Author: sid
 */

#ifndef PELLET_H_
#define PELLET_H_

class Pellet{

public:
	Pellet();
	~Pellet();
	void drawPellet(GLboolean texture, GLboolean power);
	void setColor();

private:
	GLuint pelletTextureID;
	GLfloat pellet_color[4];
};



#endif /* PELLET_H_ */
