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
	src/myengine/Component.h
	src/myengine/Component.cpp
	src/myengine/Environment.h
	src/myengine/Environment.cpp
	src/myengine/Keyboard.h
	src/myengine/Keyboard.cpp
)

add_executable(game
	src/game/main.cpp
	src/game/TestScene.cpp
	src/game/TestScene.h
)

target_link_libraries(game
	engine
)