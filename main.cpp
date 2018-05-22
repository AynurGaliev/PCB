#include <iostream>
#include <unordered_set>
#include "Core/ACOAlgorithm.h"
#include "thread"

int main() {

    Size size(10, 10);

    Coordinate2D startPoint1(1, 1);
    Coordinate2D endPoint1(3, 4);

    Coordinate2D startPoint2(2, 8);
    Coordinate2D endPoint2(9, 1);

    Connection connection1(startPoint1, endPoint1);
    Connection connection2(startPoint2, endPoint2);

    Input input(size, { connection1, connection1 }, 1, 1);
    ACOAlgorithm algorithm(10, 10, 0.3, 0.7, 0.2, 10, input);
    auto interconnections = algorithm.start();

    return 0;
}