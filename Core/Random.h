//
// Created by Aynur Galiev on 19/05/2018.
//

#ifndef ACOALGORITHM_RANDOM_H
#define ACOALGORITHM_RANDOM_H

#include <stdlib.h>

static float randomFloat(float min, float max) {
    float value = float(arc4random()) / 0xFFFFFFFF;
    return value * (max - min) + min;
}

#endif //ACOALGORITHM_RANDOM_H
