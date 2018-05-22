//
// Created by Aynur Galiev on 20/05/2018.
//

#ifndef ACOALGORITHM_ACOALGORITHM_H
#define ACOALGORITHM_ACOALGORITHM_H

#include <mutex>
#include <thread>
#include "CrossPoint.h"
#include "Input.h"
#include "Edge.h"
#include "vector"
#include "unordered_map"
#include "Node.h"
#include "Interconnection.h"
#include "Hashers.h"

using namespace std;

struct ACOAlgorithm {
private:
    uint32_t antsCount;
    uint32_t iterationsCount;
    float alpha;
    float beta;
    float p;
    float k;
    Input input;
    vector<vector<vector<Node>>> nodes;
    unordered_map<Edge, float> pheromones;
    mutex *lockMutex;
    vector<Coordinate3D> tabuCoordinates;
    vector<CrossPoint> tabuCrosspoints;
    vector<thread>* threads;
    Node node(const Coordinate3D& coordinate3D);
    bool isNodeValid(
            int32_t x,
            int32_t y,
            int32_t z,
            Coordinate3D sourceCoordinate,
            Size bounds,
            vector<Coordinate3D> tabuCoordinates,
            vector<CrossPoint> tabuCrosspoints
    );
    vector<Coordinate3D> neighbours(
            Coordinate3D coordinate3D,
            vector<Coordinate3D> tabuCoordinates,
            vector<CrossPoint> tabuCrosspoints
    );
    float probability(
            Node sourceNode,
            Node targetNode,
            vector<Coordinate3D> tabuCoordinates,
            vector<CrossPoint> tabuCrosspoints
    );
    float pheromone(Node startNode, Node endNode);
    void add(float pheromone, Node startPoint, Node endPoint);
    Interconnection* start(Connection connection, vector<Coordinate2D> tabuNodes);
public:
    vector<Interconnection> start();
    ACOAlgorithm(uint32_t antsCount, uint32_t iterationsCount, float alpha, float beta, float p, float k, Input input);
};

#endif //ACOALGORITHM_ACOALGORITHM_H
