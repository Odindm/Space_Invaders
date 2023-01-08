cmake_minimum_required(VERSION 3.15)

project(space_invaders VERSION 0.1.0 LANGUAGES CXX)

find_package(sgg REQUIRED)

add_executable(space_invaders
   playerProj.cpp
   player.cpp
   main.cpp
   game.cpp
   enemyProj.cpp
   enemy.cpp
   barrier.cpp
   UFO.cpp
   Explosion.cpp
)

target_link_libraries(space_invaders
    PRIVATE
        sgg::sgg
)

target_compile_options(space_invaders
    PRIVATE
        -Wall
        -Wpedantic
)

target_include_directories(space_invaders
    PRIVATE
        ${CMAKE_PROJECT_DIR}
)
