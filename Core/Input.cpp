//
// Created by Aynur Galiev on 19/05/2018.
//

#include "Input.h"
#include "Size.h"

Input::Input(
        Size size,
        std::vector<Connection> connections,
        uint32_t maxLevelLayer,
        uint32_t step
):size(size), connections(connections), maxLevelLayer(maxLevelLayer), step(step) {

    for (int i = 0; i < connections.size(); ++i) {
        if (!(size.isCoordinateInside(connections[i].startPoint)
            && size.isCoordinateInside(connections[i].endPoint)
            && connections[i].endPoint.x % step == 0
            && connections[i].endPoint.y % step == 0
            && connections[i].startPoint.x % step == 0
            && connections[i].startPoint.y % step == 0)) {
            throw std::invalid_argument("Invalid arguments");
        }
    }

    if (!(size.width % step == 0 && size.height % step == 0)) {
        throw std::invalid_argument("Invalid arguments");
    }
}
