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
		SALT_LOG("Salt app running...");

		mTimeOfNextFrame = std::chrono::steady_clock::now() + mFrameDuration;

		while (!mGameWindow.WindowShouldClose())
		{
			Renderer::ClearFrame();

			OnUpdate();

			std::this_thread::sleep_until(mTimeOfNextFrame);

			mGameWindow.SwapBuffers();
			mGameWindow.PollEvents();

			mTimeOfNextFrame += mFrameDuration;
		}

		Renderer::ShutDown();
	}
	void SaltApp::OnUpdate()
	{}

	void SaltApp::OnKeyPressed(KeyPressedEvent &event)
	{
		SALT_LOG(event.GetKeyCode());
	}

	int SaltApp::GetGameWindowWidth() const
	{
		return mGameWindow.GetWindowWidth();
	}

	int SaltApp::GetGameWindowHeight() const
	{
		return mGameWindow.GetWindowHeight();
	}

	void SaltApp::Close()
	{
		mGameWindow.Close();
	}

	SaltApp::SaltApp()
	{
		mGameWindow.CreateWindow(800, 800, "Game");

		mGameWindow.SetKeyPressedCallback([this](KeyPressedEvent& event) {
			OnKeyPressed(event);
			});

		Renderer::Init();
	}

};
