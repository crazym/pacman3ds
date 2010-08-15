/*
 *  Map.cpp
 *  Pacman3D
 *
 *  Created by bronson on 10-07-27.
 *  Copyright 2010 Concordia University. All rights reserved.
 *
 */

#include "Map.h"
#include "Tile.h"

#include <iostream>
#include <vector>

using namespace std;

Map::Map(char* map, GLint rows, GLint columns)
{
    initializeMap(map, rows, columns);
}

void Map::initializeMap(char* map, GLint rows, GLint columns)
{
    this->rows = rows;
    this->columns = columns;
    this->size = rows * columns;
    
    mapArray = (char*)malloc(size * sizeof(char));
    
    GLint col_it = 0;
    GLint row_it = 0;    
    
    for (GLint i = 0; i < size; ++i) {
        
        switch (map[i]) {
            
            /* Wall */
            case 'W':
                this->mapArray[i] = 'W';
                tiles.push_back(new Tile('W', col_it, row_it));
                break;
                
            /* Blank */
            case 'Y':
                this->mapArray[i] = 'Y';
                tiles.push_back(new Tile('Y', col_it, row_it));
                break;
            
            /* Tile With Pellet */
            case 'Z':
                this->mapArray[i] = 'Z';
                tiles.push_back(new Tile('Z', col_it, row_it));
                break;
            
            /* Tile With Power Pellet */
            case 'X':
                this->mapArray[i] = 'X';
                tiles.push_back(new Tile('X', col_it, row_it));
                break;

            default:
                break;
        
        }
        ++col_it;
        if (col_it == columns) {
            col_it = 0;
            ++row_it;
        }
    }
}

Map::~Map()
{
    delete[] mapArray;
    
    vector<Tile*>::iterator t_it;
    for(t_it = this->tiles.begin(); t_it != this->tiles.end(); ++t_it)
    {
        delete *t_it;
    }
}



void Map::draw(GLint texturePellets, GLint texturePPellets)
{
    vector<Tile*>::iterator t_it;
    
    for (t_it = this->tiles.begin(); t_it != this->tiles.end(); ++t_it) {
        glPushMatrix();
            (*t_it)->draw(texturePellets, texturePPellets);
        glPopMatrix();
    }
}
