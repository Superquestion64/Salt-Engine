#pragma once

#include "SaltUtils.h"
#include "GameWindow.h"

namespace Salt
{
	class SALT_API SaltApp
	{
	public:
		// This will run the game
		void Run();
		virtual void OnUpdate();
	protected:
		// BubbleApp object can only be created through inheritance
		SaltApp();

	private:
		GameWindow mGameWindow;

	};
};

