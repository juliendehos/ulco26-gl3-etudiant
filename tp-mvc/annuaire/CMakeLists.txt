cmake_minimum_required( VERSION 3.16 )

project( annuaire )

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

add_executable( annuaire.out 
  src/Annuaire.cpp
  src/Html.cpp
  src/Json.cpp
  src/main.cpp
)
target_link_libraries( annuaire.out PRIVATE hv )

install(
  TARGETS
  annuaire.out
  DESTINATION bin )

install( 
  FILES 
  static/ajouter.html
  static/favicon.ico
  static/index.html
  static/liste_xhr.html
  static/style.css
  DESTINATION static )

