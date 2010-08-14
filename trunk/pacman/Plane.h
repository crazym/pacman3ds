/*
 *  Plane.h
 *  Pacman3D
 *
 *  Created by bronson on 10-08-11.
 *  Copyright 2010 Concordia University. All rights reserved.
 *
 */

#ifndef _PLANE_H_
#define _PLANE_H_

#include "Vector.h"

class Plane {
public:
    explicit Plane();
    Plane(const Vector &position, const Vector &normal);
    
    Vector position;
    Vector normal;
};

#endif