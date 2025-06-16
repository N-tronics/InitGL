cmake_minimum_required(VERSION 3.17)

project(InitGL VERSION 2.0)
list(APPEND
    CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake
)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_BUILD_TYPE Debug)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)

add_subdirectory(lib/glad)
add_subdirectory(lib/glm)
add_subdirectory(lib/stb_image)
add_subdirectory(lib/glfw)

find_package(OpenGL REQUIRED)

file(GLOB_RECURSE SRC_FILES src/*.cpp)
add_library(InitGL STATIC ${SRC_FILES})

set_target_properties(InitGL
    PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED ON
)

target_include_directories(InitGL PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_link_libraries(InitGL PUBLIC
    OpenGL::GL
    glfw
    glad
    glm
    stb_image
)
