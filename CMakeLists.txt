cmake_minimum_required(VERSION 3.20)
project(Dungeon-of-Sorrows)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXE_LINKER_FLAGS "-static")

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
        Entities/Enemy.h
        utilities.cpp
        utilities.h
        Entities/Item.cpp
        Entities/Item.h
        Entities/Actor.cpp
        Entities/Actor.h)
