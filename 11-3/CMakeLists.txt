cmake_minimum_required(VERSION 3.5)

project(list)

add_executable( conteiner 
              lst.h
	      lst_src.cpp
	      conteiner.cpp
	      Header.h
              Source.cpp
)
set_target_properties(conteiner PROPERTIES

CXX_STANDARD 17
CXX_STANDARD_REQUIRED ON )

if(CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR
CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
target_compile_options(conteiner PRIVATE
-g
-Wall
-Wextra
-Werror
-pedantic)

elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
target_compile_options(conteiner PRIVATE
/EHsc
/W4
/WX)
endif()