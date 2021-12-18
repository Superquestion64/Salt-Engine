/*
Author: Charles Vega
Last Modified: December 17, 2021
This is the implementation class for a game created through the Salt engine
In the game the hero must consume salt to evolve
The villain rapidly evolves with time and teleports around the map
When the hero is powerful enough they can eat the villain and win
If the villain reaches its final form it becomes game over
*/
#include "MyGameApp.h"
// Constructor sets up the environment so the first part of the intro can be played
MyGameApp::MyGameApp() : mFrameCounter(0)
{
	mShader.Load("Assets/Shader/myVertexShader.glsl",
		"Assets/Shader/myFragmentShader.glsl");
	mShader.SetVec2IntUniform("screenSize", 1280, 1280);
	mWindowWidth = mShader.GetWindowWidth();
	mWindowHeight = mShader.GetWindowHeight();
	// Fill in dummy salt for the intro
	for (int i = 0; i < 10; i++)
	{
		mSalt.push_back(SaltSpawner{ "Assets/Textures/Salt.png", 700 + i, 600 + i });
	}
	// Teleport the villain to a random location to start
	mVillain.Teleport(mWindowWidth, mWindowHeight);
}

// This function runs on every frame of the game
void MyGameApp::OnUpdate()
{
	// Background must be drawn first
	BG.Draw(mShader);
	// Check if an ending has occured
	if (mEndFlag)
	{
		VictorySequence();
	}
	// The game starts after the intro is finished
	else if (!mPlayIntroFlag)
	{
		// Spawn salt every second
		if (mFrameCounter % FRAMES_PER_SECOND == 0)
		{
			SpawnSalt();
		}
		// After enough time passes increase the stage of the villain
		if (mFrameCounter % int(FRAMES_PER_SECOND * 4) == 0)
			mEndFlag = mVillain.Update(mWindowWidth, mWindowHeight);
		// Draw all the current salt
		DrawSalt();
		mVillain.Draw(mShader);
		// Update the position of the hero then draw
		mHero.UpdatePosition(mWindowWidth, mWindowHeight);
		mHero.Draw(mShader);
		// If the villain has reached their final form
		if (mEndFlag)
			VillainVictorySetUp();
		else
		{
			mEndFlag = mHero.Update(mVillain, mSalt);
			if (mEndFlag)
				HeroVictorySetUp();
		}
	}
	else
	{
		// Play the intros
		IntroSequence();
	}
	mFrameCounter++;
}

// Plays the intros
void MyGameApp::IntroSequence()
{
	// Play the first intro if less than 5 seconds have passed
	if (mFrameCounter <= FRAMES_PER_SECOND * 5)
	{
		PlayIntro1();
	}
	// After 5 seconds have passed
	else
	{
		PlayIntro2();
	}
	// We always have to draw the hero for the intro
	mDemoCharacter.UpdatePosition(mWindowWidth, mWindowHeight);
	mDemoCharacter.Draw(mShader);
}

// Performs intro part 1
void MyGameApp::PlayIntro1()
{
	// After 1 second start evolving the hero as a demonstration
	if (mFrameCounter >= FRAMES_PER_SECOND)
	{
		mDemoCharacter.SetDirection(DemoUnit::Direction::None);
		// We have a case for 2, 3, and 4 seconds, this will evolve the hero
		switch (mFrameCounter / FRAMES_PER_SECOND)
		{
		case 2:
			mDemoCharacter.SetDemo("Assets/Textures/TrueHero3.png");
			break;
		case 3:
			mDemoCharacter.SetDemo("Assets/Textures/TrueHero5.png");
			break;
		case 4:
			mDemoCharacter.SetDemo("Assets/Textures/TrueHero7.png");
			break;
		default:
			break;
		}
	}
	// When less than a second has passed
	else
	{
		// The hero will keep moving right until it has reached salt, as calculated
		mDemoCharacter.SetDirection(DemoUnit::Direction::Right);
		// We only want to draw salt when the hero is moving towards it
		DrawSalt();
	}
}

// Performs intro part 2
void MyGameApp::PlayIntro2()
{
	// Initialize background and demo characters for the first run through
	if (!mSetIntro2Flag)
	{
		BG.SetBackground("Assets/Textures/Intro2.png");
		mDemoCharacter.SetPosX(300);
		mDemoCharacter.SetPosY(600);
		mVillain.SetVillain("Assets/Textures/OddVillain3.png");
		mVillain.SetPosX(700);
		mVillain.SetPosY(600);
		mSetIntro2Flag = true;
	}
	// When less than 10 seconds have passed, play second intro scene
	if (mFrameCounter <= FRAMES_PER_SECOND * 10)
	{
		bool VillainEaten{ !(mFrameCounter <= FRAMES_PER_SECOND * 8) };
		// When more than 7 seconds have passed let the hero eat the odd villain
		if (mFrameCounter >= FRAMES_PER_SECOND * 7 && !VillainEaten)
		{
			// The hero will keep moving right until it has reached the odd villain, as calculated
			mDemoCharacter.SetDirection(DemoUnit::Direction::Right);
		}
		else
			mDemoCharacter.SetDirection(DemoUnit::Direction::None);
		if (!VillainEaten)
			mVillain.Draw(mShader);
	}
	// When more than 10 seconds have passed, open the game
	else
	{
		mPlayIntroFlag = false;
		BG.SetBackground("Assets/Textures/FightBG.png");
		// Determine a spot for the villain to spawn
		int X{ rand() % (mWindowWidth - 100) };
		int Y{ rand() % (mWindowHeight - 100) };
		mVillain.SetVillain("Assets/Textures/OddVillain1.png");
		mVillain.SetPosX(X);
		mVillain.SetPosY(Y);
		// Reset the frame counter and salt eaten
		mFrameCounter = 0;
		mDemoCharacter.UnitDelete();
		ClearSalt();
	}
}

// Ending sequence for villain or hero
void MyGameApp::VictorySequence()
{
	bool SecondElapsed{ mFrameCounter % FRAMES_PER_SECOND == 0 };
	switch (mDemoCharacter.GetDirection())
	{
	case DemoUnit::Direction::Down:
		if (SecondElapsed)
			mDemoCharacter.SetDirection(DemoUnit::Direction::Up);
		break;
	case DemoUnit::Direction::Up:
		if (SecondElapsed)
			mDemoCharacter.SetDirection(DemoUnit::Direction::Down);
		break;
	default:
		mDemoCharacter.SetDirection(DemoUnit::Direction::Down);
	}
	mDemoCharacter.UpdatePosition(mWindowWidth, mWindowHeight);
	mDemoCharacter.Draw(mShader);
}


// Spawn salt at a random location in the map
void MyGameApp::SpawnSalt()
{
	// Determine the position for the new salt
	int X{ rand() % (mWindowWidth - 100) };
	int Y{ rand() % (mWindowHeight - 100) };
	mSalt.push_back(SaltSpawner{ "Assets/Textures/Salt.png", X, Y });
}
// Will set up the ending sequence for the villain's victory
void MyGameApp::VillainVictorySetUp()
{
	BG.SetBackground("Assets/Textures/VillainEnd.png");
	mDemoCharacter.SetDemo("Assets/Textures/FinalVillain.png");
	mDemoCharacter.SetPosX(mWindowWidth / 4);
	mDemoCharacter.SetPosY(mWindowHeight / 4);
	mVillain.UnitDelete();
	mHero.UnitDelete();
	// Reset the frame counter
	mFrameCounter = 0;
	ClearSalt();
}

// Will set up the ending sequence for the hero's victory
void MyGameApp::HeroVictorySetUp()
{
	BG.SetBackground("Assets/Textures/HeroEnd.png");
	mDemoCharacter.SetDemo("Assets/Textures/FinalHero.png");
	mDemoCharacter.SetPosX(mWindowWidth / 3);
	mDemoCharacter.SetPosY(mWindowHeight / 4);
	mHero.SetHero("Assets/Textures/FinalHero.png");
	mVillain.UnitDelete();
	mHero.UnitDelete();
	// Reset the frame counter
	mFrameCounter = 0;
	ClearSalt();
}

// Will draw all the current salt
void MyGameApp::DrawSalt()
{
	for (auto& salt : mSalt)
	{
		salt.Draw(mShader);
	}
}

// Clear all the salt
void MyGameApp::ClearSalt()
{
	auto it = mSalt.begin();
	while (it != mSalt.end())
	{
		it->UnitDelete();
		it = mSalt.erase(it);		
	}
}

// This function detects any key presses that occur
void MyGameApp::OnKeyPressed(Salt::KeyPressedEvent& event)
{
	switch (event.GetKeyCode())
	{
	case SALT_KEY_LEFT:
		mHero.SetDirection(Hero::Direction::Left);
		break;
	case SALT_KEY_RIGHT:
		mHero.SetDirection(Hero::Direction::Right);
		break;
	case SALT_KEY_DOWN:
		mHero.SetDirection(Hero::Direction::Down);
		break;
	case SALT_KEY_UP:
		mHero.SetDirection(Hero::Direction::Up);
		break;
	case SALT_KEY_W:
		mHero.SetDirection(Hero::Direction::Up);
		break;
	case SALT_KEY_A:
		mHero.SetDirection(Hero::Direction::Left);
		break;
	case SALT_KEY_S:
		mHero.SetDirection(Hero::Direction::Down);
		break;
	case SALT_KEY_D:
		mHero.SetDirection(Hero::Direction::Right);
		break;
	// Debug mode will allow the user to spawn salt freely using the space key
	case SALT_KEY_SPACE:
#ifdef GAME_DEBUG
		SpawnSalt();
#endif
		break;
	case SALT_KEY_ESCAPE:
		Salt::SaltApp::Close();
	}
}