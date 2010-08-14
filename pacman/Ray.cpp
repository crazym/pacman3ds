/*
 *  Ray.cpp
 *  Pacman3D
 *
 *  Created by bronson on 10-08-11.
 *  Copyright 2010 Concordia University. All rights reserved.
 *
 */

#include "Ray.h"

Ray::Ray()
{
    this->position = Vector(0, 0, 0);
    this->direction = Vector(0, 0, 0);
}

Vector Ray::getPoint(GLfloat t)
{
    Vector point;
    
    point = this->direction * t;
    point += this->position;
    
    return point;
}