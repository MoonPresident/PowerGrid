cmake_minimum_required(VERSION 3.17)

project(PowerGrid VERSION 1.0)

#Get prebuilt packages virst
find_package(OpenGL REQUIRED)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)


add_subdirectory("${PROJECT_SOURCE_DIR}/Dependencies/glfw-3.3" "${PROJECT_BINARY_DIR}/dep-builds/glfw")

#TODO: Change this when I decide to actually use a safe implementation.
aux_source_directory("src/games" GAMES_DIR)
aux_source_directory("src/helpers" HELPERS_DIR)
aux_source_directory("src/games/opengl_examples" GRAPHICS_EXAMPLES_DIR)

#Create Executable.
add_executable(${PROJECT_NAME} 
    "src/main.cpp" 
    ${GAMES_DIR}
    ${HELPERS_DIR}
    ${GRAPHICS_EXAMPLES_DIR}
    # "src/helpers/Shaderstore.cpp"
    # "src/helpers/AbstractSimulation.cpp"
    # "src/helpers/callbacks.cpp"
    # "src/helpers/TextureFactory.cpp"
    # "src/games/example_game_3D.cpp"
    ) 

target_include_directories(${PROJECT_NAME} PUBLIC
                           "${PROJECT_BINARY_DIR}"
                           "${PROJECT_SOURCE_DIR}/src"
                           "${PROJECT_SOURCE_DIR}/src/helpers"
                           "${PROJECT_SOURCE_DIR}/src/games"
                           "${PROJECT_SOURCE_DIR}/Dependencies/FreeType/include"
                           "${PROJECT_SOURCE_DIR}/Dependencies/glfw-3.3/include/GLFW"
                           "C:/dev-builds/PowerGrid/dep-builds/glfw/src/Debug/"
                           "${PROJECT_SOURCE_DIR}/Dependencies/GLAD/include"
                           "${PROJECT_SOURCE_DIR}/Dependencies/glm-stable/glm"
                           "${PROJECT_SOURCE_DIR}/Dependencies/stb-master"
                           )


                     

#GLFW Library
set(GLFW_INSTALL OFF CACHE BOOL  "GLFW lib only" )
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

set(GLFW_LIB_PATH "${PROJECT_BINARY_DIR}/dep-builds/glfw/src/Debug/")

target_include_directories(${PROJECT_NAME} PUBLIC "${GLFW_LIB_PATH}")
target_link_libraries(${PROJECT_NAME} PUBLIC "${GLFW_LIB_PATH}/glfw3.lib")
target_link_libraries(${PROJECT_NAME} PUBLIC OpenGL::GL)


#GLAD Library
add_library(GLAD STATIC "Dependencies/GLAD/src/glad.c" "Dependencies/GLAD/include/glad/glad.h" "${GLFW_LIB_PATH}/glfw3.lib")
target_include_directories(GLAD PRIVATE "${PROJECT_SOURCE_DIR}/Dependencies/GLAD/include" "${GLFW_LIB_PATH}")
target_link_libraries(${PROJECT_NAME} PUBLIC GLAD)