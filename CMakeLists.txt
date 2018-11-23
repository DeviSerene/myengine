cmake_minimum_required(VERSION 2.6)
project(MYENGINE)

include_directories(
	src
	contrib
    contrib/msvc-windows-x86/glew/include
    contrib/msvc-windows-x86/SDL2/include
    contrib/msvc-windows-x86/SDL2_image/include
    contrib/msvc-windows-x86/openal-soft/include
    contrib/msvc-windows-x86/ogg/include
    contrib/msvc-windows-x86/vorbis/include
    contrib/msvc-windows-x86/SDL2_ttf/include
)

  link_directories(
    ${CMAKE_SOURCE_DIR}/contrib/msvc-windows-x86/SDL2/lib
    ${CMAKE_SOURCE_DIR}/contrib/msvc-windows-x86/SDL2_image/lib
    ${CMAKE_SOURCE_DIR}/contrib/msvc-windows-x86/glew/lib
    ${CMAKE_SOURCE_DIR}/contrib/msvc-windows-x86/openal-soft/lib
    ${CMAKE_SOURCE_DIR}/contrib/msvc-windows-x86/ogg/lib
    ${CMAKE_SOURCE_DIR}/contrib/msvc-windows-x86/vorbis/lib
    ${CMAKE_SOURCE_DIR}/contrib/msvc-windows-x86/SDL2_ttf/lib
  )
  
  add_definitions(-DSDL_MAIN_HANDLED)

add_library(engine
	src/myengine/Core.cpp
	src/myengine/Core.h
	src/myengine/Entity.h
	src/myengine/Entity.cpp
	src/myengine/Component.h
	src/myengine/Component.cpp
	src/myengine/Keyboard.h
	src/myengine/Keyboard.cpp
	src/myengine/MeshRenderer.h
	src/myengine/MeshRenderer.cpp
	src/myengine/SpriteRenderer.h
	src/myengine/SpriteRenderer.cpp
	src/myengine/Shader.h
	src/myengine/Shader.cpp
	src/myengine/VertexArray.h
	src/myengine/VertexArray.cpp
	src/myengine/VertexBuffer.h
	src/myengine/VertexBuffer.cpp
	src/myengine/Material.h
	src/myengine/Material.cpp
	src/myengine/Mesh.h
	src/myengine/Mesh.cpp
	src/myengine/TestResource.h
	src/myengine/TestResource.cpp
	src/myengine/Resource.h
	src/myengine/Resource.cpp
	src/myengine/Resources.h
	src/myengine/Resources.cpp
	src/myengine/Sound.h
	src/myengine/Sound.cpp
	src/myengine/MyEngineException.h
	src/myengine/Transform.h
	src/myengine/Transform.cpp
	src/myengine/Gui.h
	src/myengine/Gui.cpp
	src/myengine/FrameBuffer.h
	src/myengine/FrameBuffer.cpp
	src/myengine/DepthBuffer.h
	src/myengine/DepthBuffer.cpp
	src/myengine/Texture.h
	src/myengine/Texture.cpp
	src/myengine/TextTexture.h
	src/myengine/TextTexture.cpp
	src/myengine/Camera.h
	src/myengine/Camera.cpp
	src/myengine/Scene.h
	src/myengine/Scene.cpp
	src/myengine/Compositor.h
	src/myengine/Compositor.cpp
	src/myengine/PostProcess.h
	src/myengine/PostProcess.cpp
	src/myengine/Collisions.h
	src/myengine/Collisions.cpp
	src/myengine/Collider.h
	src/myengine/Collider.cpp
)

add_executable(game
	src/game/main.cpp
	src/game/TestScene.cpp
	src/game/TestScene.h
	src/game/BattleScene.cpp
	src/game/BattleScene.h
	src/game/BossScene.cpp
	src/game/BossScene.h
	src/game/BattleBackground.cpp
	src/game/BattleBackground.h
	src/game/Character.cpp
	src/game/Character.h
	src/game/Stats.cpp
	src/game/Stats.h
	src/game/Enemy.cpp
	src/game/Enemy.h
	src/game/ActionBar.cpp
	src/game/ActionBar.h
	src/game/TurnBar.cpp
	src/game/TurnBar.h
	src/game/Ability.cpp
	src/game/Ability.h
	src/game/BlurEffect.cpp
	src/game/BlurEffect.h
	src/game/CollisionChecker.cpp
	src/game/CollisionChecker.h
)

target_link_libraries(game
	engine
	
    SDL2 SDL2_image glew32 opengl32 OpenAL32 ogg vorbis vorbisfile SDL2_ttf
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
      "${CMAKE_SOURCE_DIR}/contrib/msvc-windows-x86/SDL2_ttf/bin/SDL2_ttf.dll"
      "$<TARGET_FILE_DIR:game>"
  )

   add_custom_command(TARGET game POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
      "${CMAKE_SOURCE_DIR}/contrib/msvc-windows-x86/SDL2_ttf/bin/libfreetype-6.dll"
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

  add_custom_command(TARGET game POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
      "${CMAKE_SOURCE_DIR}/contrib/msvc-windows-x86/openal-soft/bin/OpenAL32.dll"
      "$<TARGET_FILE_DIR:game>"
  )