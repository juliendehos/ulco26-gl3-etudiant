
cmake_minimum_required(VERSION 3.16)
project(hello-sfml LANGUAGES CXX)

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

add_executable(hello-sfml-1.out src/hello-sfml-1.cpp)
target_link_libraries(hello-sfml-1.out PRIVATE SFML::Graphics)

add_executable(hello-sfml-2.out src/hello-sfml-2.cpp)
target_link_libraries(hello-sfml-2.out PRIVATE SFML::Graphics)

install( 
  TARGETS
  hello-sfml-1.out 
  hello-sfml-2.out 
  DESTINATION bin )
install( 
  FILES 
  data/arial.ttf 
  data/bob.png
  DESTINATION data )


