cmake_minimum_required( VERSION 3.16 )
project( youpi )

set( CMAKE_CXX_STANDARD 20 )
set( CMAKE_CXX_STANDARD_REQUIRED ON )

# web app

find_package( libhv )
if(NOT libhv_FOUND)
  include(FetchContent)
  FetchContent_Declare(hv
    GIT_REPOSITORY https://github.com/ithewei/libhv
    GIT_TAG v1.3.4)
  FetchContent_MakeAvailable(hv)
endif()

add_executable( youpi-web.out
  src/Html.cpp
  src/RendererSvg.cpp
  src/Scene.cpp
  src/youpi-web.cpp )
target_link_libraries( youpi-web.out hv )

# web static

add_executable( youpi-static.out 
  src/Html.cpp
  src/RendererSvg.cpp
  src/Scene.cpp
  src/youpi-static.cpp )
target_link_libraries( youpi-static.out hv )

# desktop app

find_package( PkgConfig REQUIRED )
pkg_check_modules( PKGS REQUIRED gtkmm-4.0 )
add_executable( youpi-gui.out 
  src/RendererCairo.cpp
  src/Scene.cpp
  src/youpi-gui.cpp )
target_include_directories( youpi-gui.out PRIVATE ${PKGS_INCLUDE_DIRS})
target_link_libraries( youpi-gui.out ${PKGS_LIBRARIES} )

# install

install(
  TARGETS
  youpi-gui.out
  youpi-static.out
  youpi-web.out
  DESTINATION bin )

install( 
  FILES 
  static/favicon.ico
  static/style.css
  static/test.html
  DESTINATION static )

