//
//  Connection.cpp
//  PCB
//
//  Created by Aynur Galiev on 19/05/2018.
//  Copyright © 2018 Aynur Galiev. All rights reserved.
//

#include "Connection.h"
#include "Coordinate2D.h"

Connection::Connection(Coordinate2D startPoint, Coordinate2D endPoint):
        startPoint(startPoint), endPoint(endPoint) {}