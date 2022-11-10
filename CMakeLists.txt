cmake_minimum_required(VERSION 3.16)

project(R-TYPE VERSION 1.0.0 LANGUAGES CXX)

add_compile_options(-g)

file(GLOB_RECURSE HEADERS "include/*.hpp")
add_library(${PROJECT_NAME} ${HEADERS})
add_executable(r-type_server src/main_server.cpp )
target_link_libraries(r-type_server ${PROJECT_NAME})
add_executable(r-type_client src/main_client.cpp)
target_link_libraries(r-type_client ${PROJECT_NAME})
find_package(SFML COMPONENTS system window graphics CONFIG REQUIRED)

# Call the cmake that checks and pulls the raylib
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

if(CMAKE_COMPILER_IS_GNUCXX)
    target_link_libraries(${PROJECT_NAME} -lstdc++fs sfml-graphics sfml-system sfml-window -pthread)
endif(CMAKE_COMPILER_IS_GNUCXX)

if (MSVC)
    target_link_libraries(${PROJECT_NAME} sfml-system sfml-graphics sfml-window)
endif (MSVC)

set(CMAKE_CXX_STANDARD 20)

target_sources(${PROJECT_NAME}
    PRIVATE

        src/Core.cpp
        src/SceneManager.cpp
        src/AnimationManager.cpp
        src/Entity.cpp
        src/Scene.cpp
        src/ButtonCallback.cpp
        src/MouseCallback.cpp
        src/Script.cpp

        src/components/Component.cpp
        src/components/Position.cpp
        src/components/Player.cpp
        src/components/Velocity.cpp
        src/components/Text.cpp
        src/components/Sprite.cpp
        src/components/Event.cpp
        src/components/Ennemy.cpp
        src/components/Projectiles.cpp
        src/components/Animation.cpp

        src/systems/EventSystem.cpp
        src/systems/GraphicSystem.cpp
        src/systems/GameSystem.cpp
        src/systems/CollideSystem.cpp
        src/systems/NetworkSystem.cpp
        src/systems/ServerSystem.cpp
        src/systems/ClientSystem.cpp
        src/systems/network/Connection.cpp
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
        src/components
        src/systems
        src
)

# Set default compile flags for GCC
if(CMAKE_COMPILER_IS_GNUCXX)
    message(STATUS "GCC detected, adding compile flags")
    target_compile_options(${PROJECT_NAME}
        PRIVATE
            -Wall
            -Wextra
    )
endif(CMAKE_COMPILER_IS_GNUCXX)

set_target_properties(
    ${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "../"
)
