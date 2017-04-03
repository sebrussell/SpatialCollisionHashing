cmake_minimum_required(VERSION 2.6)
set(CMAKE_CXX_STANDARD 11)
project(APP)

set(CMAKE_BUILD_TYPE Release)

if (MSVC)
  include_directories(${PROJECT_SOURCE_DIR}/src/SDL2-2.0.5/include)
  link_directories(${PROJECT_SOURCE_DIR}/src/SDL2-2.0.5/lib/x86)
else()
  include_directories(${PROJECT_SOURCE_DIR}/src/SDL2-2.0.5_minGW/i686-w64-mingw32/include/SDL2)
  link_directories(${PROJECT_SOURCE_DIR}/src/SDL2-2.0.5_minGW/i686-w64-mingw32/lib)  

  include_directories(${PROJECT_SOURCE_DIR}/src/SDL2_ttf-2.0.14/i686-w64-mingw32/include/SDL2)
  link_directories(${PROJECT_SOURCE_DIR}/src/SDL2_ttf-2.0.14/i686-w64-mingw32/lib)  
endif()


set(CMAKE_CXX_FLAGS "-fopenmp")

add_executable(parallel_test
  main.cpp
  Particle.cpp
  Graphics.cpp
  Hash.cpp
)

target_link_libraries(parallel_test SDL2 SDL2_ttf)






