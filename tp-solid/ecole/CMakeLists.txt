cmake_minimum_required( VERSION 3.16 )
project( ecole LANGUAGES CXX )

add_executable( ecole0.out src/ecole0.cpp )

install( TARGETS 
  ecole0.out 
  DESTINATION bin )

