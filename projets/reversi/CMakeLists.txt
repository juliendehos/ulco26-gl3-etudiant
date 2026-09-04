
cmake_minimum_required(VERSION 3.16)

project( reversi LANGUAGES CXX )

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# reversi.out
find_package( PkgConfig REQUIRED )
pkg_check_modules( GTKMM REQUIRED gtkmm-4.0 )
add_executable( reversi.out 
  src/Game.cpp
  src/Ui.cpp
  src/main.cpp
)
target_include_directories( reversi.out PRIVATE ${GTKMM_INCLUDE_DIRS})
target_link_libraries( reversi.out ${GTKMM_LIBRARIES} )
install( TARGETS reversi.out DESTINATION bin )

# test.out
find_package( Catch2 REQUIRED )
add_executable( test.out
  src/Game.cpp
  src/GameTest.cpp
)
target_link_libraries( test.out PRIVATE Catch2::Catch2WithMain )
enable_testing()
add_test( NAME test COMMAND test.out )

