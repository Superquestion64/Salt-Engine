#include "MyGameApp.h"

MyGameApp::MyGameApp() : mHero("Assets/Textures/TrueHero1.png", 0, 0, 10), mFrameCounter(0)
{
	mShader.Load("Assets/Shader/myVertexShader.glsl",
		"Assets/Shader/myFragmentShader.glsl");
	mShader.SetVec2IntUniform("screenSize", 800, 800);
	windowWidth = mShader.GetWindowWidth();
	windowHeight = mShader.GetWindowHeight();
}

void MyGameApp::OnUpdate()
{
	mHero.UpdatePosition(windowWidth, windowHeight);
	// Spawn a new villains every second
	if (mFrameCounter % FRAMES_PER_SECOND == 0 && mVillains.size() < 1)
	{
		int newX{ rand() % (windowWidth - 100) };
		int newY{ rand() % (windowHeight - 100) };
		Unit::Direction newDir;
		int dirVal{ rand() % 4 };
		switch (dirVal)
		{
		case 0:
			newDir = Unit::Direction::Down;
			break;
		case 1:
			newDir = Unit::Direction::Up;
			break;
		case 2:
			newDir = Unit::Direction::Left;
			break;
		default:
			newDir = Unit::Direction::Right;
			break;
		}
		mVillains.push_back(Unit{ "Assets/Textures/OddVillain1.png", newX, newY, 10 });
		mVillains.back().SetDirection(newDir);
	}

	// Check collisions
	auto it = mVillains.begin();
	while (it != mVillains.end())
	{
		if (mHero.CollideWith(*it))
			it = mVillains.erase(it);
		else
			it++;
	}
	// Update existing villains
	for (auto& villain : mVillains)
	{
		villain.UpdatePosition(windowWidth, windowHeight);
		villain.Draw(mShader);
	}

	mHero.Draw(mShader);

	mFrameCounter++;
}

void MyGameApp::OnKeyPressed(Salt::KeyPressedEvent& event)
{
	switch (event.GetKeyCode())
	{
	case SALT_KEY_LEFT:
		mHero.SetDirection(Unit::Direction::Left);
		break;
	case SALT_KEY_RIGHT:
		mHero.SetDirection(Unit::Direction::Right);
		break;
	case SALT_KEY_DOWN:
		mHero.SetDirection(Unit::Direction::Down);
		break;
	case SALT_KEY_UP:
		mHero.SetDirection(Unit::Direction::Up);
		break;
	}
}
