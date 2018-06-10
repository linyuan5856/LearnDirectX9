cmake_minimum_required(VERSION 3.10)
project(LearnDirectX)

set(CMAKE_CXX_STANDARD 11)

include_directories("C:/Project/CLionProjects/LearnDirectX9/LearnDirectX/include")
link_directories("C:/Project/CLionProjects/LearnDirectX9/LearnDirectX/Lib/x86")
#add_executable(LearnDirectX main.cpp d3dUtility.cpp d3dUtility.h ColorVertexExample.cpp)
add_executable(LearnDirectX  d3dUtility.cpp d3dUtility.h ColorVertexExample.cpp)
target_link_libraries(LearnDirectX d3d9.lib d3dx9.lib d3dx9d.lib XInput.lib  winmm.lib)