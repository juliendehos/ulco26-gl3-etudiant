
cmake_minimum_required(VERSION 3.16)
project(paint LANGUAGES CXX)

find_package( PkgConfig REQUIRED )
pkg_check_modules( GTKMM REQUIRED gtkmm-4.0 )

add_executable( paint.out 
  src/Paint.cpp
  src/Ui.cpp
  src/main.cpp )
target_include_directories( paint.out PRIVATE ${GTKMM_INCLUDE_DIRS})
target_link_libraries( paint.out ${GTKMM_LIBRARIES} )

install( TARGETS paint.out DESTINATION bin )

