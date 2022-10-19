cmake_minimum_required(VERSION 3.12) 
project(05.quessgame)
add_executable( 05.quessgame quessgame.cpp)
set_target_properties(05.quessgame
PROPERTIES
CXX_STANDARD 17
CXX_STANDARD_REQUIRED ON )