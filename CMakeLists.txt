cmake_minimum_required(VERSION 3.26)
project(space_shooter)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_executable(space_shooter src/main.cpp src/Entity/Player.cpp src/Entity/Enemy.cpp src/Projectile/BulletPlayer.cpp src/Projectile/BulletEnemy.cpp
        src/Game.cpp src/Manager/AssetManager.cpp src/Powerup.cpp src/Entity/Entity.cpp src/Grid.cpp src/Cell.cpp src/Window.cpp
        src/SpaceObject/SpaceObject.cpp src/SpaceObject/Planet.cpp src/Object.cpp src/PIDController.cpp src/Projectile/Projectile.cpp src/Projectile/Missile.cpp
        src/Manager/EnemyManager.cpp
        src/Manager/ProjectileManager.cpp
        src/Manager/PowerupManager.cpp
        src/Manager/PlayerManager.cpp
        src/Manager/SpaceObjectManager.cpp
        src/Manager/CollisionManager.cpp
)

file(COPY resources DESTINATION ${CMAKE_BINARY_DIR})

find_package(SFML 2.5 COMPONENTS system window graphics REQUIRED)
target_link_libraries(space_shooter sfml-system sfml-window sfml-graphics)
