//
// Created by Aynur Galiev on 20/05/2018.
//

#ifndef ACOALGORITHM_COORDINATE2D_H
#define ACOALGORITHM_COORDINATE2D_H

#include <stdint.h>
#include "math.h"
#include "Hashable.h"
#include "iostream"

using namespace std;

struct Coordinate2D: Hashable {

    int32_t x;
    int32_t y;

    Coordinate2D():x(0), y(0) {}

    Coordinate2D(int32_t x, int32_t y) {
        this->x = x;
        this->y = y;
    }

    bool operator==(const Coordinate2D& coordinate) const {
        return coordinate.x == this->x && coordinate.y == this->y;
    }

    bool operator!=(const Coordinate2D& coordinate) const {
        return coordinate.x != this->x || coordinate.y != this->y;
    }

    Coordinate2D& operator=(const Coordinate2D& coordinate) {
        Coordinate2D *newCoordinate = new Coordinate2D(coordinate.x, coordinate.y);
        return *newCoordinate;
    }

    int32_t hashValue() const {
        return __hash_combine(x, y);
    }
};


static float distance(Coordinate2D lhs, Coordinate2D rhs) {
    float diffX = fabs(lhs.x - rhs.x);
    float diffY = fabs(lhs.y - rhs.y);
    return fabs(diffX - diffY) + fmin(diffX, diffY) * sqrt(2);
};

#endif //ACOALGORITHM_COORDINATE2D_H
