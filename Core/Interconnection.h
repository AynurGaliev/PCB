//
// Created by Aynur Galiev on 20/05/2018.
//

#ifndef ACOALGORITHM_INTERCONNECTION_H
#define ACOALGORITHM_INTERCONNECTION_H

#include "vector"
#include "Coordinate3D.h"

using namespace std;

struct Interconnection {
private:
    vector<Coordinate3D> _coordinates;
public:
    vector<Coordinate3D> coordinates();
    Interconnection();
    Interconnection(vector<Coordinate3D> coordinates);
};

#endif //ACOALGORITHM_INTERCONNECTION_H
