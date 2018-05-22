//
//  Size.h
//  PCB
//
//  Created by Aynur Galiev on 19/05/2018.
//  Copyright © 2018 Aynur Galiev. All rights reserved.
//

#ifndef Size_h
#define Size_h

#include <stdio.h>
#include "Coordinate2D.h"

struct Size {
public:
    uint32_t height;
    uint32_t width;

    Size(uint32_t height, uint32_t width);
    Size();

    bool isCoordinateInside(Coordinate2D coordinate) {
        return coordinate.x <= this->width && coordinate.y <= this->height;
    }
};

#endif /* Size_h */
