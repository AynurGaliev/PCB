//
// Created by Aynur Galiev on 20/05/2018.
//

#ifndef ACOALGORITHM_HASHABLE_H
#define ACOALGORITHM_HASHABLE_H

#include <cstdint>

struct Hashable {
public:
    virtual int32_t hashValue() const = 0;
};

#endif //ACOALGORITHM_HASHABLE_H
