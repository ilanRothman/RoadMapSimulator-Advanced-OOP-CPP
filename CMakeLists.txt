cmake_minimum_required(VERSION 3.20)
project(Assignment_Two)

set(CMAKE_CXX_STANDARD 14)

add_executable(EX2 main.cpp Menu.cpp Menu.h FileMgr.cpp FileMgr.h Vehicle/Vehicle.cpp Vehicle/Vehicle.h Vehicle/Sprinter.cpp Vehicle/Sprinter.h Vehicle/Tram.cpp Vehicle/Tram.h Vehicle/Rail.cpp Vehicle/Rail.h Vehicle/Bus.cpp Vehicle/Bus.h Junction/Junction.cpp Junction/Junction.h Junction/interCity.cpp Junction/interCity.h Junction/Central.cpp Junction/Central.h Junction/Stad.cpp Junction/Stad.h RoadMap.cpp RoadMap.h)
