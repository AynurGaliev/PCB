//
// Created by Aynur Galiev on 20/05/2018.
//

#ifndef ACOALGORITHM_COORDINATE3D_H
#define ACOALGORITHM_COORDINATE3D_H

#include <cstdint>
#include "Coordinate2D.h"
#include "Constants.h"

struct Coordinate3D: Hashable {

    int32_t x;
    int32_t y;
    int32_t z;

    Coordinate3D(int32_t x, int32_t y, int32_t z) {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    Coordinate3D(const Coordinate2D coordinate) {
        this->x = coordinate.x;
        this->y = coordinate.y;
        this->z = 0;
    }

    Coordinate3D(const Coordinate2D coordinate, int32_t z) {
        this->x = coordinate.x;
        this->y = coordinate.y;
        this->z = z;
    }

    Coordinate3D() {
        this->x = 0;
        this->y = 0;
        this->z = 0;
    }

    bool operator<(const Coordinate3D& coordinate) const {
        return hashValue() < coordinate.hashValue();
    }

    bool operator==(const Coordinate3D& coordinate) const {
        return x == coordinate.x && y == coordinate.y && z == coordinate.z;
    }

    Coordinate2D coordinate2D() {
        Coordinate2D coordinate(this->x, this->y);
        return coordinate;
    }

    int32_t hashValue() const {
        return __hash_combine(__hash_combine(x, y), z);
    }
};

static float distance(Coordinate3D lhs, Coordinate3D rhs) {
    return distance(lhs.coordinate2D(), rhs.coordinate2D()) + fabs(lhs.z - rhs.z) * interLayerEdgeWeight;
}

#endif //ACOALGORITHM_COORDINATE3D_H
