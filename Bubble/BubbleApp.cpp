#include "pch.h"

#include "BubbleApp.h"

namespace Bubble
{
	// This will run the game
	void BubbleApp::Run()
	{
		std::cout << "Bubble running..." << std::endl;
		while (true)
		{
			OnUpdate();
		}
	}
	void BubbleApp::OnUpdate()
	{}

	BubbleApp::BubbleApp()
	{}

};
