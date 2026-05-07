
cmake_minimum_required(VERSION 3.16)

project( connect4 LANGUAGES CXX )

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# connect4.out
find_package( PkgConfig REQUIRED )
pkg_check_modules( GTKMM REQUIRED gtkmm-4.0 )
add_executable( connect4.out 
  src/Game.cpp
  src/UiGtkmm.cpp
  src/main-gtkmm.cpp
)
target_include_directories( connect4.out PRIVATE ${GTKMM_INCLUDE_DIRS})
target_link_libraries( connect4.out ${GTKMM_LIBRARIES} )
install( TARGETS connect4.out DESTINATION bin )

# test.out
find_package( Catch2 REQUIRED )
add_executable( test.out
  src/Game.cpp
  src/GameTest.cpp
)
target_link_libraries( test.out PRIVATE Catch2::Catch2WithMain )
enable_testing()
add_test( NAME test COMMAND test.out )

