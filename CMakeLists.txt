cmake_minimum_required(VERSION 3.20)
project(Dungeon-of-Sorrows)

set(CMAKE_CXX_STANDARD 20)

add_executable(Dungeon-of-Sorrows main.cpp
        Core/Game.cpp
        Core/Game.h
        World/Map.cpp
        World/Map.h
        Entities/Entity.cpp
        Entities/Entity.h
        Entities/Player.cpp
        Entities/Player.h
        Entities/Enemy.cpp
        Entities/Enemy.h)
