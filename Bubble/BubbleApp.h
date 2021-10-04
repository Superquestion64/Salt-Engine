#pragma once

#include "BubbleUtils.h"

namespace Bubble
{
	class BUBBLE_API BubbleApp
	{
	public:
		// This will run the game
		void Run();
		virtual void OnUpdate();
	protected:
		// BubbleApp object can only be created through inheritance
		BubbleApp();

	private:

	};
};

