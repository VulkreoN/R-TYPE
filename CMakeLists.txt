cmake_minimum_required(VERSION 3.16)

project(R-TYPE VERSION 1.0.0 LANGUAGES CXX)

add_executable(${PROJECT_NAME})

# Call the cmake that checks and pulls the raylib
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

if(CMAKE_COMPILER_IS_GNUCXX)
    target_link_libraries(${PROJECT_NAME} -lstdc++fs sfml-graphics sfml-system sfml-window)
endif(CMAKE_COMPILER_IS_GNUCXX)

set(CMAKE_CXX_STANDARD 17)

target_sources(${PROJECT_NAME}
    PRIVATE
        src/main.cpp
        src/Core.cpp
        src/SceneManager.cpp
        src/Entity.cpp
        src/Scene.cpp
        src/ButtonCallback.cpp

        src/components/Component.cpp
        src/components/Position.cpp
        src/components/Velocity.cpp
        src/components/Text.cpp
        src/components/Sprite.cpp
        src/components/Event.cpp

        src/systems/EventSystem.cpp
        src/systems/GraphicSystem.cpp
        src/systems/GameSystem.cpp
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