cmake_minimum_required(VERSION 3.17)

project(PowerGrid VERSION 1.0)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS OFF)

add_subdirectory("src")

find_program(CLANG_TIDY_EXE NAMES "clang-tidy")
set(CLANG_TIDY_COMMAND "${CLANG_TIDY_EXE}" "-checks=-*,modernize-*")
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_CLANG_TIDY "${CLANG_TIDY_COMMAND}")


#FreeType
set(FREETYPE_DIRECTORY Dependencies/freetype)
add_subdirectory(${FREETYPE_DIRECTORY})
target_include_directories(${PROJECT_NAME} PUBLIC ${FREETYPE_DIRECTORY}/include ${FREETYPE_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PUBLIC freetype)

message(DEBUG ${FREETYPE_LIBRARY})
message(DEBUG ${FREETYPE_INCLUDE_DIRS})

#Get prebuilt packages first
find_package(OpenGL REQUIRED)

#GLFW config and GLAD Library
#set(GLFW_INSTALL OFF CACHE BOOL  "GLFW lib only" )
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(${PROJECT_SOURCE_DIR}/Dependencies/glfw)
target_link_libraries(${PROJECT_NAME} PUBLIC glfw)

set(GLFW_LIB_PATH ${PROJECT_BINARY_DIR}/dep-builds/glfw/src/Debug)

add_subdirectory(Dependencies/glad/)
add_library(GLAD STATIC Dependencies/GLAD/src/glad.c Dependencies/GLAD/include/glad/glad.h)

target_include_directories(${PROJECT_NAME} PUBLIC ${GLFW_LIB_PATH})
target_include_directories(GLAD PRIVATE ${PROJECT_SOURCE_DIR}/Dependencies/GLAD/include)

target_link_libraries(${PROJECT_NAME} PUBLIC OpenGL::GL GLAD)

# Assimp
set(ASSIMP_INSTALL OFF CACHE BOOL "" FORCE)

add_subdirectory(Dependencies/assimp)
target_link_libraries(${PROJECT_NAME} PUBLIC assimp)

add_subdirectory(Dependencies/glm)
target_link_libraries(${PROJECT_NAME} PUBLIC glm)

#include header files.
target_include_directories(
    ${PROJECT_NAME} PUBLIC
        ${PROJECT_BINARY_DIR}
        ${PROJECT_SOURCE_DIR}/src
        ${PROJECT_SOURCE_DIR}/src/helpers
        ${PROJECT_SOURCE_DIR}/src/games
        ${PROJECT_SOURCE_DIR}/src/components
        ${PROJECT_SOURCE_DIR}/src/models
        ${PROJECT_SOURCE_DIR}/src/gui
        ${PROJECT_SOURCE_DIR}/src/inputs
        ${PROJECT_SOURCE_DIR}/src/graphics
        ${PROJECT_SOURCE_DIR}/Dependencies/glfw/include/GLFW
        ${PROJECT_BINARY_DIR}/dep-builds/glfw/src/Debug/
        ${PROJECT_SOURCE_DIR}/Dependencies/GLAD/include
        ${PROJECT_SOURCE_DIR}/Dependencies/glm/glm
        ${PROJECT_SOURCE_DIR}/Dependencies/stb
        ${FREETYPE_INCLUDE_DIRS}
)
target_sources(${PROJECT_NAME} PUBLIC "src/my_debug.cpp")

#https://www.foonathan.net/2018/10/cmake-warnings/
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic)


## BREAKIN
add_executable(Breakin "src/breakin.cpp")
target_sources(Breakin PUBLIC "src/my_debug.cpp")

set_target_properties(Breakin PROPERTIES CXX_CLANG_TIDY "${CLANG_TIDY_COMMAND}")

target_link_libraries(Breakin PUBLIC glfw OpenGL::GL GLAD)

#include header files.
target_include_directories(
    Breakin PUBLIC
        ${PROJECT_BINARY_DIR}
        ${PROJECT_SOURCE_DIR}/src
        ${PROJECT_SOURCE_DIR}/src/helpers
        ${PROJECT_SOURCE_DIR}/src/games
        ${PROJECT_SOURCE_DIR}/src/components
        ${PROJECT_SOURCE_DIR}/src/models
        ${PROJECT_SOURCE_DIR}/src/gui
        ${PROJECT_SOURCE_DIR}/src/inputs
        ${PROJECT_SOURCE_DIR}/src/graphics
        ${PROJECT_SOURCE_DIR}/Dependencies/glfw/include/GLFW
        ${PROJECT_BINARY_DIR}/dep-builds/glfw/src/Debug/
        ${PROJECT_SOURCE_DIR}/Dependencies/GLAD/include
        ${PROJECT_SOURCE_DIR}/Dependencies/glm/glm
        ${PROJECT_SOURCE_DIR}/Dependencies/stb
        ${FREETYPE_INCLUDE_DIRS}
)
