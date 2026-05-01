
cmake_minimum_required( VERSION 3.16 )

project( asteroids-ecs )

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

###############################################################################
# flecs
###############################################################################

find_package( flecs )
if(NOT flecs_FOUND)
  include(FetchContent)
  FetchContent_Declare(flecs
    GIT_REPOSITORY https://github.com/SanderMertens/flecs.git
    GIT_TAG v4.1.5
    GIT_SHALLOW ON
  )
  FetchContent_MakeAvailable(flecs)
endif()

###############################################################################
# asteroids-ecs-sfml
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

add_executable( asteroids-ecs-sfml
  src/Game.cpp
  src/ViewSfml.cpp
  src/main-sfml.cpp
)
target_link_libraries( asteroids-ecs-sfml
  SFML::Graphics
  flecs::flecs
)

###############################################################################
# install
###############################################################################

install( 
  TARGETS 
  asteroids-ecs-sfml
  DESTINATION bin )

install( 
  FILES 
  data/arial.ttf
  data/asteroid.png
  data/spaceship1.png
  data/spaceship2.png
  DESTINATION data )

