cmake_minimum_required(VERSION 3.12)
project(cs201_p4)

set(CMAKE_CXX_STANDARD 14)

add_executable(cs201_p4 main.cpp Adventure.cpp Adventure.h AdvRoom.cpp AdvRoom.h AdvObject.cpp AdvObject.h AdvMotionTableEntry.cpp AdvMotionTableEntry.h)