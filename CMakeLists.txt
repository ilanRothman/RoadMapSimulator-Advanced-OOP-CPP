cmake_minimum_required(VERSION 3.20)
project(Assignment_Two)

set(CMAKE_CXX_STANDARD 14)

add_executable(EX2 main.cpp Menu.cpp Menu.h FileMgr.cpp FileMgr.h
        Vehicle/Vehicle.cpp Vehicle/Vehicle.h Vehicle/Sprinter.cpp Vehicle/Sprinter.h Vehicle/Tram.cpp Vehicle/Tram.h Vehicle/Rail.cpp Vehicle/Rail.h Vehicle/Bus.cpp Vehicle/Bus.h
        Junction/Junction.cpp Junction/Junction.h
        RoadMap.cpp RoadMap.h)
