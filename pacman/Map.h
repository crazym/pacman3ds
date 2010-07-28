/*
 *  Map.h
 *  Pacman3D
 *
 *  Created by bronson on 10-07-27.
 *  Copyright 2010 Concordia University. All rights reserved.
 *
 */
#ifndef _MAP_H_
#define _MAP_H_

#include <vector>

using namespace std;

class Tile;

class Map {
public:
    Map(char* map, int rows, int columns);
    ~Map();
    
    void initializeMap(char* map, int rows, int columns);
    void draw();
    
    vector<Tile*> tiles;
    int size;
    int rows;
    int columns;
};
#endif