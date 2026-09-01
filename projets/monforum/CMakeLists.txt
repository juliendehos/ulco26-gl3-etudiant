cmake_minimum_required( VERSION 3.16 )

project( monforum )

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package( libhv )
if(NOT libhv_FOUND)
  include(FetchContent)
  FetchContent_Declare(hv
    GIT_REPOSITORY https://github.com/ithewei/libhv
    GIT_TAG v1.3.4)
  FetchContent_MakeAvailable(hv)
endif()

add_executable( monforum.out 
  src/MonForum.cpp
  src/View.cpp
  src/main.cpp
)
target_link_libraries( monforum.out PRIVATE hv )

install(
  TARGETS
  monforum.out
  DESTINATION bin )

install( 
  FILES 
  static/favicon.ico
  static/style.css
  DESTINATION static )

