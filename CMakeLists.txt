cmake_minimum_required(VERSION 2.6)
project(MYENGINE)

include_directories(
	src
	contrib
    contrib/msvc-windows-x86/glew/include
    contrib/msvc-windows-x86/SDL2/include
    contrib/msvc-windows-x86/SDL2_image/include
)

  link_directories(
    ${CMAKE_SOURCE_DIR}/contrib/msvc-windows-x86/SDL2/lib
    ${CMAKE_SOURCE_DIR}/contrib/msvc-windows-x86/SDL2_image/lib
    ${CMAKE_SOURCE_DIR}/contrib/msvc-windows-x86/glew/lib
  )
  
  add_definitions(-DSDL_MAIN_HANDLED)

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
	src/myengine/MeshRenderer.h
	src/myengine/MeshRenderer.cpp
	src/myengine/ShaderProgram.h
	src/myengine/ShaderProgram.cpp
	src/myengine/VertexArray.h
	src/myengine/VertexArray.cpp
	src/myengine/VertexBuffer.h
	src/myengine/VertexBuffer.cpp
	src/myengine/Material.h
	src/myengine/Material.cpp
	src/myengine/Mesh.h
	src/myengine/Mesh.cpp
)

add_executable(game
	src/game/main.cpp
	src/game/TestScene.cpp
	src/game/TestScene.h
)

target_link_libraries(game
	engine
	
    SDL2 SDL2_image glew32 opengl32 
)

 add_custom_command(TARGET game POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
      "${CMAKE_SOURCE_DIR}/contrib/msvc-windows-x86/SDL2/bin/SDL2.dll"
      "$<TARGET_FILE_DIR:game>"
  )

   add_custom_command(TARGET game POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
      "${CMAKE_SOURCE_DIR}/contrib/msvc-windows-x86/SDL2_image/bin/SDL2_image.dll"
      "$<TARGET_FILE_DIR:game>"
  )

     add_custom_command(TARGET game POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
      "${CMAKE_SOURCE_DIR}/contrib/msvc-windows-x86/SDL2_image/bin/libpng16-16.dll"
      "$<TARGET_FILE_DIR:game>"
  )

  add_custom_command(TARGET game POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
      "${CMAKE_SOURCE_DIR}/contrib/msvc-windows-x86/glew/bin/glew32.dll"
      "$<TARGET_FILE_DIR:game>"
  )