//
// Created by Aynur Galiev on 19/05/2018.
//

#ifndef ACOALGORITHM_NODE_H
#define ACOALGORITHM_NODE_H

#include "Coordinate3D.h"

struct Node: Hashable {
private:
    Coordinate3D _coordinate;
public:
    Node(Coordinate3D coordinate);
    Node();
    Coordinate3D coordinate3D() const;

    bool operator<(const Node& node) const {
        return coordinate3D() < node.coordinate3D();
    }

    bool operator==(const Node& node) const {
        return coordinate3D() == node.coordinate3D();
    }

    int32_t hashValue() const {
        return _coordinate.hashValue();
    }
};

#endif //ACOALGORITHM_NODE_H
