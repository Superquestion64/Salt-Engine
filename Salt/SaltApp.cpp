#include "pch.h"

#include "SaltApp.h"
#include "Sprite.h"
#include "Shader.h"
#include "Renderer.h"

#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"
#include "glad/glad.h"

#include "stb_image.h"

namespace Salt
{
	// This will run the game
	void SaltApp::Run()
	{
		std::cout << "Salt is running..." << std::endl;

		mGameWindow.CreateWindow(800, 600, "Test");

		Renderer::Init();

		// Shaders
		Salt::Shader myShader;
		myShader.Load("C:/Users/Anonymous/Downloads/Game Engine/MyGame/Salt/Assets/Shader/myVertexShader.glsl", 
			"C:/Users/Anonymous/Downloads/Game Engine/MyGame/Salt/Assets/Shader/myFragmentShader.glsl");
		myShader.SetVec2IntUniform("screenSize",
			mGameWindow.GetWindowWidth(),
			mGameWindow.GetWindowHeight());

		// TEXTURE

		Salt::Sprite fish;
		fish.LoadImage("C:/Users/Anonymous/Downloads/Game Engine/MyGame/Salt/Assets/Textures/Clown.png");

		while (true)
		{
			Renderer::ClearFrame();

			OnUpdate();

			Renderer::Draw(fish, 100, 50, fish.GetWidth(), fish.GetHeight(), myShader);

			mGameWindow.SwapBuffers();
			mGameWindow.PollEvents();
		}

		Renderer::ShutDown();
	}
	void SaltApp::OnUpdate()
	{}

	SaltApp::SaltApp()
	{}

};
