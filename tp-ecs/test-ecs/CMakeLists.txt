
cmake_minimum_required( VERSION 3.16 )

project( test-ecs )

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
# test-ecs
###############################################################################

add_executable( test-ecs
  src/main.cpp
)

target_link_libraries( test-ecs 
  flecs::flecs
)

###############################################################################
# install
###############################################################################

install( 
  TARGETS 
  test-ecs
  DESTINATION bin )

