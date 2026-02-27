
cmake_minimum_required(VERSION 3.16)
project(snake LANGUAGES CXX)

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

add_executable( snake-sfml.out src/Game.cpp src/snake-sfml.cpp )
target_link_libraries( snake-sfml.out PRIVATE SFML::Graphics )

install( 
  TARGETS 
  snake-sfml.out 
  DESTINATION bin )

install( 
  FILES 
  data/apple-32.png 
  DESTINATION data )

