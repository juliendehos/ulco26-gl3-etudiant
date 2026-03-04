
cmake_minimum_required(VERSION 3.16)

project(mul2 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package( PkgConfig REQUIRED )
pkg_check_modules( GTKMM REQUIRED gtkmm-4.0 )

add_executable( mul2.out src/main.cpp )
target_include_directories( mul2.out PRIVATE ${GTKMM_INCLUDE_DIRS})
target_link_libraries( mul2.out ${GTKMM_LIBRARIES} )

install( TARGETS mul2.out DESTINATION bin )

