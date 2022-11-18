cmake_minimum_required(VERSION 3.5)

project(list)

add_executable( list 
              lst.h
	      List.cpp
	      lst_src.cpp)
set_target_properties(list PROPERTIES

CXX_STANDARD 17
CXX_STANDARD_REQUIRED ON )

if(CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR
CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
target_compile_options(list PRIVATE
-g
-Wall
-Wextra
-Werror
-pedantic)

elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
target_compile_options(list PRIVATE
/EHsc
/W4
/WX)
endif()