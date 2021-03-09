cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)

set(PROJECT_NAME open_sandbox)

project(${PROJECT_NAME})

add_executable(
		${PROJECT_NAME}
		src/main.cpp

        src/game/Block.cpp
		src/game/Block.h
		src/game/Game.cpp
		src/game/Game.h

		src/render/AnimatedSprite.cpp
		src/render/AnimatedSprite.h
		src/render/IndexBuffer.cpp
		src/render/IndexBuffer.h
		src/render/Renderer.cpp
		src/render/Renderer.h
		src/render/ShaderProgram.cpp
		src/render/ShaderProgram.h
		src/render/Sprite.cpp
		src/render/Sprite.h
		src/render/Texture.cpp
		src/render/Texture.h
		src/render/VertexArray.cpp
		src/render/VertexArray.h
		src/render/VertexBuffer.cpp
		src/render/VertexBuffer.h
		src/render/VertexBufferLayout.cpp
		src/render/VertexBufferLayout.h

		src/resources/ResourceManager.cpp
		src/resources/ResourceManager.h
		src/resources/stb_image.h
)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

add_subdirectory(external/glfw)
target_link_libraries(${PROJECT_NAME} glfw)

add_subdirectory(external/glad)
target_link_libraries(${PROJECT_NAME} glad)

add_subdirectory(external/glm)
target_link_libraries(${PROJECT_NAME} glm)

set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/)
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/res $<TARGET_FILE_DIR:${PROJECT_NAME}>/res)
