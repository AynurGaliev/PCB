cmake_minimum_required(VERSION 3.10)
project(ACOAlgorithm)

set(CMAKE_CXX_STANDARD 17)

add_executable(ACOAlgorithm main.cpp Core/Connection.h Core/Connection.cpp Core/Size.h Core/Size.cpp Core/CrossPoint.cpp Core/CrossPoint.h Core/Random.h Core/Input.cpp Core/Input.h Core/Node.cpp Core/Node.h Core/Edge.cpp Core/Edge.h Core/ACOAlgorithm.cpp Core/ACOAlgorithm.h Core/Interconnection.cpp Core/Interconnection.h Core/Hashable.cpp Core/Hashable.h Core/Coordinate2D.cpp Core/Coordinate2D.h Core/Coordinate3D.cpp Core/Coordinate3D.h Core/Constants.h Core/Hashers.cpp Core/Hashers.h)