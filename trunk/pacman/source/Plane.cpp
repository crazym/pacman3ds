/*
 *  Plane.cpp
 *  Pacman3D
 *
 *  Created by bronson on 10-08-11.
 *  Copyright 2010 Concordia University. All rights reserved.
 *
 */

#include "../include/Plane.h"

Plane::Plane(const Vector &position, const Vector &normal)
{
    this->position = position;
    this->normal = normal;
}


Plane::Plane()
{
    this->position = Vector(0, 0, 0);
    this->normal = Vector(0, 0, 0);
}
