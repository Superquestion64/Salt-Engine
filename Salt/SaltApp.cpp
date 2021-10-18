#include "pch.h"

#include "SaltApp.h"

#include "GLFW/glfw3.h"

namespace Salt
{
	// This will run the game
	void SaltApp::Run()
	{
		std::cout << "Salt is running..." << std::endl;

		mGameWindow.CreateWindow(800, 600, "Test");

		while (true)
		{
			OnUpdate();
			mGameWindow.SwapBuffers();
			mGameWindow.PollEvents();
		}
	}
	void SaltApp::OnUpdate()
	{}

	SaltApp::SaltApp()
	{
	}

};
