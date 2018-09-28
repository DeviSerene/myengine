cmake_minimum_required(VERSION 2.6)
project(MYENGINE)

include_directories(
	src
)

add_library(engine
	src/myengine/Core.cpp
	src/myengine/Core.h
	src/myengine/Entity.h
	src/myengine/Entity.cpp
)

add_executable(game
	src/game/main.cpp
	src/game/TestScene.cpp
	src/game/TestScene.h
)

target_link_libraries(game
	engine
)