//
// Created by Aynur Galiev on 19/05/2018.
//

#ifndef ACOALGORITHM_INPUT_H
#define ACOALGORITHM_INPUT_H

#include "vector"
#include "Size.h"
#include "Connection.h"

using namespace std;

struct Input {
    vector<Connection> connections;
    Size size;
    int32_t step;
    int32_t maxLevelLayer;

    Input(
            Size size,
            std::vector<Connection> connections,
            uint32_t maxLevelLayer,
            uint32_t step
    );
};

#endif //ACOALGORITHM_INPUT_H
