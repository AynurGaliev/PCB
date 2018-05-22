//
// Created by Aynur Galiev on 19/05/2018.
//

#include "Edge.h"

Edge::Edge(Node startPoint, Node endPoint):_startPoint(startPoint), _endPoint(endPoint) {
    if (startPoint.coordinate3D().x == endPoint.coordinate3D().x) {
        if (startPoint.coordinate3D().y < endPoint.coordinate3D().y) {
            this->_startPoint = startPoint;
            this->_endPoint = endPoint;
        } else if (startPoint.coordinate3D().y > endPoint.coordinate3D().y) {
            this->_startPoint = endPoint;
            this->_endPoint = startPoint;
        } else {
            if (startPoint.coordinate3D().z < endPoint.coordinate3D().z) {
                this->_startPoint = startPoint;
                this->_endPoint = endPoint;
            } else {
                this->_startPoint = endPoint;
                this->_endPoint = startPoint;
            }
        }
    } else if (startPoint.coordinate3D().x < endPoint.coordinate3D().x) {
        this->_startPoint = startPoint;
        this->_endPoint = endPoint;
    } else {
        this->_startPoint = endPoint;
        this->_endPoint = startPoint;
    }
}
