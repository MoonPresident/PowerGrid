cmake_minimum_required(VERSION 3.17)

add_executable(${PROJECT_NAME} 
    "main.cpp"
)

target_sources(${PROJECT_NAME} PUBLIC "components/AbstractSimulation.cpp")
target_sources(${PROJECT_NAME} PUBLIC "components/WorldData.cpp")
# target_sources(${PROJECT_NAME} PUBLIC "models/*")
target_sources(${PROJECT_NAME} PUBLIC "games/example_game_3D.cpp")
target_sources(${PROJECT_NAME} PUBLIC "games/squares_original.cpp")
target_sources(${PROJECT_NAME} PUBLIC "graphics/shaderStore.cpp")
target_sources(${PROJECT_NAME} PUBLIC "graphics/TextureFactory.cpp")
target_sources(${PROJECT_NAME} PUBLIC "gui/callbacks.cpp")
target_sources(${PROJECT_NAME} PUBLIC "gui/Font.cpp")
target_sources(${PROJECT_NAME} PUBLIC "gui/Terminal.cpp")
target_sources(${PROJECT_NAME} PUBLIC "gui/Text.cpp")
target_sources(${PROJECT_NAME} PUBLIC "gui/Window.cpp")
# target_sources(${PROJECT_NAME} PUBLIC "inputs/*")
# target_sources(${PROJECT_NAME} PUBLIC "games/opengl_examples/*")