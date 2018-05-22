//
// Created by Aynur Galiev on 19/05/2018.
//

#ifndef ACOALGORITHM_EDGE_H
#define ACOALGORITHM_EDGE_H

#include "Node.h"

struct Edge: Hashable {
private:
    Node _startPoint;
    Node _endPoint;
public:
    Node startPoint() const { return _startPoint; };
    Node endPoint() const { return _endPoint; };
    Edge(Node startPoint, Node endPoint);

    Edge& operator=(const Edge& edge) const {
        auto newEdge = new Edge(edge.startPoint(), edge.endPoint());
        return reinterpret_cast<Edge &>(newEdge);
    }

    bool operator==(const Edge& edge) const {
        return startPoint() == edge.startPoint() && endPoint() == edge.endPoint();
    }

    int32_t hashValue() const {
        return __hash_combine(_startPoint.hashValue(), _endPoint.hashValue());
    }
};

#endif //ACOALGORITHM_EDGE_H
