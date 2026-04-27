
cmake_minimum_required(VERSION 3.16)

project(snake LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package( SFML COMPONENTS Graphics )
if(NOT SFML_FOUND)
  include(FetchContent)
  FetchContent_Declare(SFML
      GIT_REPOSITORY https://github.com/SFML/SFML.git
      GIT_TAG 3.0.2
      GIT_SHALLOW ON
      EXCLUDE_FROM_ALL
      SYSTEM)
  FetchContent_MakeAvailable(SFML)
endif()

find_package( PkgConfig REQUIRED )
pkg_check_modules( PKGS REQUIRED gtkmm-4.0 )

add_executable(snake.out 
  src/Game.cpp
  src/GuiGtkmm.cpp
  src/GuiSfml.cpp
  src/Randomizer.cpp
  src/main.cpp)
target_include_directories( snake.out PRIVATE ${PKGS_INCLUDE_DIRS})
target_link_libraries( snake.out ${PKGS_LIBRARIES} SFML::Graphics)

install( 
  TARGETS 
  snake.out 
  DESTINATION bin )

install( 
  FILES 
  data/apple-32.png 
  data/arial.ttf
  DESTINATION data )

