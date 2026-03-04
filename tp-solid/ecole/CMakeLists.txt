cmake_minimum_required( VERSION 3.16 )

project( ecole LANGUAGES CXX )

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable( ecole0.out src/ecole0.cpp )

install( TARGETS 
  ecole0.out 
  DESTINATION bin )

