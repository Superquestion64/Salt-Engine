set(SOURCE_FILES 
	SaltApp.cpp 
	GameWindow.cpp 
	GLFWimpl/GlfwImplementation.cpp
	OpenGLimpl/OpenGLRenderer.cpp
	OpenGLimpl/OpenGLShader.cpp
	OpenGLimpl/OpenGLSprite.cpp
	Renderer.cpp
	Shader.cpp
	Sprite.cpp
)
set(HEADER_FILES 
	Salt.h 
	SaltApp.h 
	SaltUtils.h 
	WindowImplementation.h 
	GameWindow.h 
	GLFWimpl/GlfwImplementation.h
	OpenGLimpl/OpenGLRenderer.h
	OpenGLimpl/OpenGLShader.h
	OpenGLimpl/OpenGLSprite.h
	Renderer.h
	RendererImplementation.h
	Shader.h
	ShaderImplementation.h
	Sprite.h
	SpriteImplementation.h
	WindowImplementation.h
)
add_library(salt_lib SHARED ${SOURCE_FILES} ${HEADER_FILES})
target_precompile_headers(salt_lib PRIVATE pch.h)
add_definitions(-DSALT_LIB)
target_link_libraries(salt_lib glfw glad stbi)
include_directories(../glfw/include)
include_directories(../Salt)
include_directories(../glad/include)
include_directories(../stbi)