cmake_minimum_required(VERSION 3.17)

project(PowerGrid VERSION 1.0)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

#TODO: Change this when I decide to actually use a safe implementation.
# aux_source_directory("src/components" COMPONENTS_DIR)
# aux_source_directory("src/models" MODELS_DIR)
# aux_source_directory("src/games" GAMES_DIR)
# aux_source_directory("src/helpers" HELPERS_DIR)
# aux_source_directory("src/graphics" GRAPHICS_DIR)
# aux_source_directory("src/gui" GUI_DIR)
# aux_source_directory("src/inputs" INPUTS_DIR)
# aux_source_directory("src/games/opengl_examples" GRAPHICS_EXAMPLES_DIR)

#Create Executable.
# add_executable(${PROJECT_NAME} 
#     "src/main.cpp" 
#     ${COMPONENTS_DIR}
#     ${MODELS_DIR}
#     ${GAMES_DIR}
#     ${HELPERS_DIR}
#     ${GRAPHICS_DIR}
#     ${GUI_DIR}
#     ${INPUTS_DIR}
#     ${GRAPHICS_EXAMPLES_DIR}
# )
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

##GLM Stuff
#FindPackage Module path:
#set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmakeFinders/")
# find_package(GLM REQUIRED)
# target_link_libraries(${PROJECT_NAME} PUBLIC GLM)

#GLFW config and GLAD Library
# set(GLFW_INSTALL OFF CACHE BOOL  "GLFW lib only" )
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
        ${FREETYPE_PATH}/include/freetype2
        ${FREETYPE_PATH}/include/freetype2/freetype
        ${PROJECT_SOURCE_DIR}/Dependencies/glfw/include/GLFW
        ${FREETYPE_DIRECTORY}/include
        ${FREETYPE_DIRECTORY}/include/freetype
        ${FREETYPE_INCLUDE_DIRS}
        ${PROJECT_BINARY_DIR}/dep-builds/glfw/src/Debug/
        ${PROJECT_SOURCE_DIR}/Dependencies/GLAD/include
        ${PROJECT_SOURCE_DIR}/Dependencies/glm/glm
        ${PROJECT_SOURCE_DIR}/Dependencies/stb
        ${FREETYPE_INCLUDE_DIRS}
)