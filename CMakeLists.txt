cmake_minimum_required(VERSION 3.20)
project(Assignment_Two)

set(CMAKE_CXX_STANDARD 14)

add_executable(EX2 main.cpp Menu.cpp Menu.h FileMgr.cpp FileMgr.h
        Vehicle.cpp Vehicle.h Sprinter.h Tram.h Rail.h Bus.h
        Junction.h
        RoadMap.cpp RoadMap.h)
