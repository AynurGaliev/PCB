//
// Created by Aynur Galiev on 19/05/2018.
//

#include <cstdint>
#include <stdexcept>
#include "CrossPoint.h"
#include "Coordinate3D.h"
#include "math.h"
#include "stdlib.h"

CrossPoint::CrossPoint(float x, float y, float z):_x(x), _y(y), _z(z) {}

CrossPoint* CrossPoint::crossPoint(const Coordinate3D& lhs, const Coordinate3D& rhs) {
    if (!(fabs(lhs.x - rhs.x) == 1 && fabs(lhs.y - rhs.y) == 1)) {
        return nullptr;
    }
    CrossPoint *crossPoint = new CrossPoint(fabs(lhs.x - rhs.x) / 2, fabs(lhs.y - rhs.y) / 2, lhs.z);
    return crossPoint;
}

CrossPoint::CrossPoint():_x(0.0), _y(0.0), _z(0.0) {}

float CrossPoint::x() const {
    return this->_x;
}

float CrossPoint::y() const {
    return this->_y;
}

float CrossPoint::z() const {
    return this->_z;
}


