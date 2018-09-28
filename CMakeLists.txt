cmake_minimum_required(VERSION 2.6)
project(MYENGINE)

add_executable(game
	src/game/main.cpp
	src/game/TestScene.cpp
	src/game/TestScene.h
	src/myengine/Core.cpp
	src/myengine/Core.h

)