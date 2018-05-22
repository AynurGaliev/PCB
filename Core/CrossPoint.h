//
// Created by Aynur Galiev on 19/05/2018.
//

#ifndef ACOALGORITHM_CROSSPOINT_H
#define ACOALGORITHM_CROSSPOINT_H

#include <cstdint>
#include "Coordinate3D.h"

struct CrossPoint {
private:
    float _x;
    float _y;
    float _z;
public:
    float x() const;
    float y() const;
    float z() const;
    CrossPoint(float x, float y, float z);
    CrossPoint();
    static CrossPoint* crossPoint(const Coordinate3D& lhs, const Coordinate3D& rhs);
    bool operator==(const CrossPoint& crossPoint) const {
        return x() == crossPoint.x() && y() == crossPoint.y() && z() == crossPoint.z();
    }
};

#endif //ACOALGORITHM_CROSSPOINT_H
