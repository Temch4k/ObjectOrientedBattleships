cmake_minimum_required(VERSION 3.13)
project(BattleShips)

set(CMAKE_CXX_STANDARD 14)

add_executable(BattleShips main.cpp field.cpp field.h Ships.cpp Ships.h functions.cpp functions.h)