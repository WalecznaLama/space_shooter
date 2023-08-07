cmake_minimum_required(VERSION 3.26)
project(space_shooter)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_executable(space_shooter src/main.cpp src/Player.cpp src/Enemy.cpp src/Bullet.cpp src/Game.cpp
                             src/AssetManager.cpp src/PassiveObject.cpp src/Powerup.cpp src/Entity.cpp
                             src/Grid.cpp src/Cell.cpp src/Window.cpp
                             src/SpaceObject.cpp src/Planet.cpp src/Object.cpp)

file(COPY resources DESTINATION ${CMAKE_BINARY_DIR})

find_package(SFML 2.5 COMPONENTS system window graphics REQUIRED)
target_link_libraries(space_shooter sfml-system sfml-window sfml-graphics)
