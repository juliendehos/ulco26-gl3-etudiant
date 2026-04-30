
cmake_minimum_required( VERSION 3.16 )

project( maze-oop )

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

###############################################################################
# maze-opp-sfml
###############################################################################

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

add_executable( maze-oop-sfml
  src/Game.cpp
  src/ViewSfml.cpp
  src/main-sfml.cpp
)
target_link_libraries( maze-oop-sfml
  SFML::Graphics
)

###############################################################################
# install
###############################################################################

install( 
  TARGETS 
  maze-oop-sfml
  DESTINATION bin )

install( 
  FILES 
  data/arial.ttf
  data/bob.png
  data/miso.png
  data/maze1.txt
  data/maze2.txt
  data/maze3.txt
  data/maze4.txt
  DESTINATION data )

