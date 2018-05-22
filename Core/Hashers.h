//
// Created by Aynur Galiev on 21/05/2018.
//

#ifndef ACOALGORITHM_HASHERS_H
#define ACOALGORITHM_HASHERS_H

#include "Node.h"
#include "Edge.h"

namespace std
{
    template<>
    struct hash<Node>
    {
        size_t operator()(const Node& node) const
        {
            return node.hashValue();
        }
    };

    template<>
    struct hash<Coordinate2D>
    {
        size_t operator()(const Coordinate2D& coordinate) const
        {
            return coordinate.hashValue();
        }
    };

    template<>
    struct hash<Edge>
    {
        size_t operator()(const Edge& edge) const
        {
            return edge.hashValue();
        }
    };
}

#endif //ACOALGORITHM_HASHERS_H
