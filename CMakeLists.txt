cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
cmake_policy(SET CMP0072 NEW)

project(InitGL VERSION 1.0)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
set(CMAKE_BUILD_TYPE Debug)
find_package(OpenGL REQUIRED)
find_package(GLFW3 REQUIRED)
find_package(GLM REQUIRED)

file(GLOB_RECURSE SRC_FILES *.cpp gl/gl.c)
add_library(InitGL STATIC ${SRC_FILES})
target_link_libraries(InitGL PUBLIC
    ${GLFW3_LIBRARY}
    ${GLM_LIBRARY}
    OpenGL::GL
)
