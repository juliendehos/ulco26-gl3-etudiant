
cmake_minimum_required(VERSION 3.16)

project(hello-gtkmm LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package( PkgConfig REQUIRED )
pkg_check_modules( GTKMM REQUIRED gtkmm-4.0 )

add_executable( hello-gtkmm-1.out src/hello-gtkmm-1.cpp )
target_include_directories( hello-gtkmm-1.out PRIVATE ${GTKMM_INCLUDE_DIRS})
target_link_libraries( hello-gtkmm-1.out ${GTKMM_LIBRARIES} )

add_executable( hello-gtkmm-2.out src/hello-gtkmm-2.cpp )
target_include_directories( hello-gtkmm-2.out PRIVATE ${GTKMM_INCLUDE_DIRS})
target_link_libraries( hello-gtkmm-2.out ${GTKMM_LIBRARIES} )

add_executable( hello-gtkmm-3.out src/hello-gtkmm-3.cpp )
target_include_directories( hello-gtkmm-3.out PRIVATE ${GTKMM_INCLUDE_DIRS})
target_link_libraries( hello-gtkmm-3.out ${GTKMM_LIBRARIES} )

install( 
  TARGETS 
  hello-gtkmm-1.out 
  hello-gtkmm-2.out 
  hello-gtkmm-3.out 
  DESTINATION bin )

