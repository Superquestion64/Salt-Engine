#pragma once

#include "SaltUtils.h"
#include "GameWindow.h"

#define FRAMES_PER_SECOND 30

namespace Salt
{
	class SALT_API SaltApp
	{
	public:
		// This will run the game
		void Run();
		virtual void OnUpdate();
		virtual void OnKeyPressed(KeyPressedEvent &event);
		int GetGameWindowWidth() const;
		int GetGameWindowHeight() const;
	protected:
		// SaltApp object can only be created through inheritance
		SaltApp();
	private:
		GameWindow mGameWindow;
		std::chrono::steady_clock::time_point mTimeOfNextFrame;
		const std::chrono::milliseconds mFrameDuration{ 1000 / FRAMES_PER_SECOND };
	};
};

