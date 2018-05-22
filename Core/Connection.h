//
//  Connection.hpp
//  PCB
//
//  Created by Aynur Galiev on 19/05/2018.
//  Copyright © 2018 Aynur Galiev. All rights reserved.
//

#ifndef Connection_hpp
#define Connection_hpp

#include <stdio.h>
#include "Coordinate2D.h"

struct Connection {
public:
    Coordinate2D startPoint;
    Coordinate2D endPoint;

    Connection(Coordinate2D startPoint, Coordinate2D endPoint);

    bool operator==(const Connection& connection) {
        return startPoint == connection.startPoint && endPoint == connection.endPoint;
    }
};


#endif /* Connection_hpp */
