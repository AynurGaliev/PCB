//
// Created by Aynur Galiev on 20/05/2018.
//

#include "Interconnection.h"

vector<Coordinate3D> Interconnection::coordinates() {
    return this->_coordinates;
}

Interconnection::Interconnection():_coordinates(vector<Coordinate3D>()) {}

Interconnection::Interconnection(vector<Coordinate3D> coordinates):_coordinates(coordinates) {}