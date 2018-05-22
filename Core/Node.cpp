//
// Created by Aynur Galiev on 19/05/2018.
//

#include "Node.h"

Node::Node(Coordinate3D coordinate):_coordinate(coordinate) {}

Node::Node():_coordinate() {};

Coordinate3D Node::coordinate3D() const {
    return this->_coordinate;
}
