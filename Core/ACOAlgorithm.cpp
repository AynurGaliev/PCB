//
// Created by Aynur Galiev on 20/05/2018.
//

#include <cstdint>
#include <unordered_set>
#include "ACOAlgorithm.h"
#include "Input.h"
#include "vector"
#include "map"
#include "Edge.h"
#include "CrossPoint.h"
#include "set"
#include "Constants.h"
#include "Coordinate3D.h"
#include "Random.h"
#include "unordered_map"
#include "Hashers.h"
#include "thread"

using namespace std;

ACOAlgorithm::ACOAlgorithm(
        uint32_t antsCount,
        uint32_t iterationsCount,
        float alpha,
        float beta,
        float p,
        float k,
        Input input
      ):antsCount(antsCount),
        iterationsCount(iterationsCount),
        alpha(alpha),
        beta(beta),
        p(p),
        k(k),
        input(input),
        lockMutex(nullptr)
{
      if (alpha + beta != 1) {
            throw invalid_argument("Wrong alpha & beta");
      }

      Node defaultNode;
      vector<Node> zArray(input.maxLevelLayer + 1);
      for (int i = 0; i < input.maxLevelLayer + 1; i++) {
            zArray[i] = defaultNode;
      }

      vector<vector<Node>> yArray(input.size.height / input.step + 1);
      for (int i = 0; i < input.size.height / input.step + 1; i++) {
            yArray[i] = zArray;
      }

      vector<vector<vector<Node>>> xArray(input.size.width / input.step + 1);
      for (int i = 0; i < input.size.width / input.step + 1; ++i) {
            xArray[i] = yArray;
      }

      this->nodes = xArray;

      for (uint32_t x = 0; x < input.size.width / input.step + 1; x++) {
            for (uint32_t y = 0; y < input.size.height / input.step + 1; y++) {
                  for (uint32_t z = 0; z < input.maxLevelLayer + 1; z++) {
                        Coordinate3D coordinate3D(x, y, z);
                        Node node(coordinate3D);
                        nodes[x][y][z] = node;
                  }
            }
      }

      this->threads = new vector<thread>(antsCount);

      this->lockMutex = new mutex();
}

vector<Interconnection> ACOAlgorithm::start() {

    // Сортировка соединений по длине, начиная с самых длинных
    sort(input.connections.begin(), input.connections.end(),
         [](const Connection& lhs, const Connection& rhs) -> bool
         {
             return distance(lhs.startPoint, lhs.endPoint) > distance(rhs.startPoint, rhs.endPoint);
         });

    unordered_set<Coordinate2D> allNodes;
    for (auto &connection : input.connections) {
        allNodes.insert(connection.startPoint);
        allNodes.insert(connection.endPoint);
    }

    vector<Coordinate2D> output;
    output.insert(output.end(), allNodes.begin(), allNodes.end());

    vector<Interconnection> interconnections;
    for (const auto &connection : input.connections) {
        Interconnection* interconnection = start(connection, output);
        if (interconnection != nullptr) {
            interconnections.push_back(*interconnection);
        }
    }

    return interconnections;
}

Interconnection* ACOAlgorithm::start(Connection connection, vector<Coordinate2D> tabuNodes) {

    vector<Coordinate3D> shortestPath;
    float shortestPathLength = numeric_limits<float>::max();
    vector<Coordinate3D> shortestPathTabuCoordinates;
    vector<CrossPoint> shortestPathTabuCrosspoints;

    vector<Coordinate2D> nodes;

    for (const auto &coordinate : tabuNodes) {
        if (!(coordinate == connection.startPoint || coordinate == connection.endPoint)) {
            nodes.push_back(coordinate);
        }
    }

    set<Coordinate3D> connectionNodes;
    for (const auto &node : nodes) {
        for (int layer = 0; layer < input.maxLevelLayer; layer++) {
            Coordinate3D coordinate3D(node, layer);
            connectionNodes.insert(coordinate3D);
        }
    }

    vector<Coordinate3D> connectionNodesArray;
    for (const auto &node: connectionNodes) {
        connectionNodesArray.push_back(node);
    }

    for (int i = 0; i < iterationsCount; ++i) {
        vector<unordered_map<Edge, float>> newEdges(antsCount);
        vector<thread*> threads;
        for (int j = 0; j < antsCount; ++j) {

                Coordinate3D startPoint3D = Coordinate3D(connection.startPoint);
                vector<Coordinate3D> path = {startPoint3D};
                float pathLength = 0.0;
                bool isPathSet = true;
                vector<CrossPoint> crosspoints;

                while (startPoint3D.coordinate2D() != connection.endPoint) {

                    vector<Coordinate3D> allTabuCoordinates;
                    allTabuCoordinates.insert(allTabuCoordinates.end(), path.begin(), path.end());
                    allTabuCoordinates.insert(allTabuCoordinates.end(), this->tabuCoordinates.begin(),
                                              this->tabuCoordinates.end());
                    allTabuCoordinates.insert(allTabuCoordinates.end(), connectionNodesArray.begin(),
                                              connectionNodesArray.end());

                    vector<CrossPoint> allTabuCrosspoints;
                    allTabuCrosspoints.insert(allTabuCrosspoints.end(), crosspoints.begin(), crosspoints.end());
                    allTabuCrosspoints.insert(allTabuCrosspoints.end(), this->tabuCrosspoints.begin(),
                                              this->tabuCrosspoints.end());

                    auto neighbours = this->neighbours(startPoint3D, allTabuCoordinates, allTabuCrosspoints);

                    if (neighbours.empty()) {
                        isPathSet = false;
                        break;
                    }

                    unordered_map<Node, float> neighboursProbability;
                    for (auto neighbour: neighbours) {
                        Node sourceNode = this->node(startPoint3D);
                        Node targetNode = this->node(neighbour);
                        float probability = this->probability(sourceNode, targetNode, allTabuCoordinates,
                                                              allTabuCrosspoints);
                        neighboursProbability[targetNode] = probability;
                    }
                    float sumProbabilities = 0.0;
                    for (auto item: neighboursProbability) {
                        sumProbabilities += item.second;
                    }
                    float randomFloatValue = randomFloat(0.0, sumProbabilities);
                    const Node *targetNode;
                    float tempProbability = 0.0;
                    for (auto item: neighboursProbability) {
                        float lowerbound = tempProbability;
                        float upperbound = lowerbound + item.second;
                        if (randomFloatValue >= lowerbound && randomFloatValue <= upperbound) {
                            targetNode = &item.first;
                            break;
                        } else {
                            tempProbability = upperbound;
                        }
                    }
                    path.push_back(targetNode->coordinate3D());

                    auto crossPoint = CrossPoint::crossPoint(startPoint3D, targetNode->coordinate3D());

                    if (crossPoint != nullptr) {
                        crosspoints.push_back(*crossPoint);
                    }
                    pathLength += distance(startPoint3D, targetNode->coordinate3D());
                    startPoint3D = targetNode->coordinate3D();
                }

                if (isPathSet) {
                    float sumLength = 0.0;
                    for (int i = 0; i < path.size() - 1; ++i) {
                        sumLength += distance(path[i], path[i + 1]);
                    }

                    this->lockMutex->lock();
                    if (shortestPathLength > sumLength) {
                        shortestPath = path;
                        shortestPathLength = sumLength;
                        shortestPathTabuCoordinates = path;
                        shortestPathTabuCrosspoints = crosspoints;
                    }
                    this->lockMutex->unlock();

                    float updatedPheromone = this->k / sumLength;
                    unordered_map<Edge, float> updatedEdges;
                    for (int j = 0; j < path.size() - 1; ++j) {
                        Node node1 = path[j];
                        Node node2 = path[j + 1];
                        Edge edge(node1, node2);
                        auto it = updatedEdges.find(edge);
                        if (it == updatedEdges.end()) {
                            updatedEdges[edge] = 0.0;
                        } else {
                            updatedEdges[edge] += updatedPheromone;
                        }
                    }

                    this->lockMutex->lock();
                    newEdges[j] = updatedEdges;
                    this->lockMutex->unlock();
                }
        }

        unordered_map<Edge, float> edges;
        for (auto item: newEdges) {
            for (auto dict: item) {
                auto it = edges.find(dict.first);
                if (it == edges.end()) {
                    edges[dict.first] = 0.0;
                } else {
                    edges[dict.first] += dict.second;
                }
            }
        }

        for (auto edge: edges) {
            float oldValue = 0.0;
            auto it = pheromones.find(edge.first);
            if (it != pheromones.end()) {
                oldValue = it->second;
            }
            float oldEdgesValue = 0.0;
            auto it1 = edges.find(edge.first);
            if (it1 != edges.end()) {
                oldEdgesValue = it1->second;
            }
            pheromones[edge.first] = (1 - p) * oldValue + oldEdgesValue;
        }
    }

    cout<<"Size - "<<shortestPath.size()<<endl;
    for(auto value: shortestPath) {
        cout<<"Path: "<<"x - "<<value.x<<"; y - "<<value.y<<"; z - "<<value.z<<endl;
    }
    return new Interconnection(shortestPath);
}

float ACOAlgorithm::probability(
        Node sourceNode,
        Node targetNode,
        vector<Coordinate3D> tabuCoordinates,
        vector<CrossPoint> tabuCrosspoints
) {
    float pheromone = this->pheromone(sourceNode, targetNode);
    float distanceBetweenNodes = distance(sourceNode.coordinate3D(), targetNode.coordinate3D());
    auto neighbours = this->neighbours(sourceNode.coordinate3D(), tabuCoordinates, tabuCrosspoints);
    float neighboursProbability = 0.0;
    for(auto neighbour: neighbours) {
        Node node = this->node(neighbour);
        float pheromoneForEdge = this->pheromone(sourceNode, node);
        float distanceBetweenNeighbours = distance(sourceNode.coordinate3D(), node.coordinate3D());
        neighboursProbability += pow(pheromoneForEdge, alpha)/pow(distanceBetweenNeighbours, beta);
    }
    float topValue = pow(pheromone, alpha)/pow(distanceBetweenNodes, beta);
    return topValue/neighboursProbability;
}

float ACOAlgorithm::pheromone(Node startNode, Node endNode) {
    float pheromone = defaultPheromone;
    const Edge edge(startNode, endNode);
    this->lockMutex->lock();
    auto it = pheromones.find(edge);
    if (it == pheromones.end()) {
        pheromones[edge] = defaultPheromone;
    } else {
        pheromone = it->second;
    }
    this->lockMutex->unlock();
    return pheromone;
}

void ACOAlgorithm::add(float pheromone, Node startPoint, Node endPoint) {
    Edge edge(startPoint, endPoint);
    this->lockMutex->lock();
    auto it = pheromones.find(edge);
    if (it != pheromones.end()) {
        pheromones[edge] = defaultPheromone;
    } else {
        pheromones[edge] = it->second + pheromone;
    }
    this->lockMutex->unlock();
}

Node ACOAlgorithm::node(const Coordinate3D& coordinate3D) {
    return this->nodes[coordinate3D.x][coordinate3D.y][coordinate3D.z];
}

bool ACOAlgorithm::isNodeValid(
        int32_t x,
        int32_t y,
        int32_t z,
        Coordinate3D sourceCoordinate,
        Size bounds,
        vector<Coordinate3D> tabuCoordinates,
        vector<CrossPoint> tabuCrosspoints
) {
    if (!(x>=0 && x<=input.size.width &&
          y>=0 && y<=input.size.height &&
          z>=0 && z<=input.maxLevelLayer))
    {
        return false;
    }
    Coordinate3D coordinate3D(x, y, z);
    auto it = find(tabuCoordinates.begin(), tabuCoordinates.end(), coordinate3D);
    if (it != tabuCoordinates.end()) {
        return false;
    }
    if (coordinate3D.z != sourceCoordinate.z) {
        return coordinate3D.coordinate2D() == sourceCoordinate.coordinate2D();
    } else {
        auto crossPoint = CrossPoint::crossPoint(coordinate3D, sourceCoordinate);
        if (crossPoint != nullptr) {
            auto it = find(tabuCrosspoints.begin(), tabuCrosspoints.end(), *crossPoint);
            return (it == tabuCrosspoints.end());
        } else {
            return true;
        }
    }
}

vector<Coordinate3D> ACOAlgorithm::neighbours(
            Coordinate3D coordinate3D,
            vector<Coordinate3D> tabuCoordinates,
            vector<CrossPoint> tabuCrosspoints
) {

    vector<Coordinate3D> nodeNeighbours;

    int32_t x = coordinate3D.x;
    int32_t y = coordinate3D.y;
    int32_t z = coordinate3D.z;

    for(auto deltaX: {-1, 0, 1}) {
        for(auto deltaY: {-1, 0, 1}) {
            for(auto deltaZ: {-1, 0, 1}) {
                if (deltaX == 0 && deltaY == 0 && deltaZ == 0) { continue; }
                if (this->isNodeValid(x + deltaX, y + deltaY, z + deltaZ, coordinate3D, input.size, tabuCoordinates, tabuCrosspoints)) {
                    Coordinate3D coordinate(x + deltaX, y + deltaY, z + deltaZ);
                    nodeNeighbours.push_back(coordinate);
                }
            }
        }
    }

    return nodeNeighbours;
}
