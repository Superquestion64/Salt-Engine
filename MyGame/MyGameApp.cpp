/*
Author: Charles Vega
Last Modified: December 16, 2021
This is the implementation class for a game created through the Salt engine
In the game the hero must consume salt to evolve
The villain rapidly evolves with time and teleports around the map
When the hero is powerful enough they can eat the villain and win
If the villain reaches its final stage it becomes game over
*/

#include "MyGameApp.h"
#include "Unit.h"

// Constructor sets up the environment so the first part of the intro can be played
MyGameApp::MyGameApp() : mFrameCounter(0)
{
	// Start background with Intro1
	mBackground = Unit{ "Assets/Textures/Intro1.png", 0, 0, 0};
	// The current stage of the hero is at index 24
	mHeroPicture = "Assets/Textures/TrueHero1.png";
	// The current stage of the villain is at index 26
	mVillainPicture = "Assets/Textures/OddVillain1.png";
	mHero = Unit{ mHeroPicture, 0, 0, 10 };
	mShader.Load("Assets/Shader/myVertexShader.glsl",
		"Assets/Shader/myFragmentShader.glsl");
	mShader.SetVec2IntUniform("screenSize", 1280, 1280);
	mWindowWidth = mShader.GetWindowWidth();
	mWindowHeight = mShader.GetWindowHeight();
	// Fill in dummy salt for the intro
	for (int i = 0; i < 10; i++)
	{
		mSalt.push_back(Unit{ "Assets/Textures/Salt.png", 700 + i, 600 + i, 0 });
	}
}

// This function runs on every frame of the game
void MyGameApp::OnUpdate()
{
	// Background must be drawn first
	mBackground.Draw(mShader);
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
		// Teleport the villain during set intervals
		TeleportVillain();
		// Check if the hero should eat salt and or the villain
		EatVillain();
		EatSalt();
		// Draw all the current salt
		DrawSalt();
		// Evolve the hero if appropriate
		EvolveHero();
		// Update the positions of the villain and hero, then draw
		mVillain.UpdatePosition(mWindowWidth, mWindowHeight);
		mVillain.Draw(mShader);
		mHero.UpdatePosition(mWindowWidth, mWindowHeight);
		mHero.Draw(mShader);
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
		mDemoCharacter.SetDirection(Unit::Direction::None);
		// We have a case for 2, 3, and 4 seconds, this will evolve the hero
		switch (mFrameCounter / FRAMES_PER_SECOND)
		{
		case 2:
			mDemoCharacter = Unit{ "Assets/Textures/TrueHero3.png", mDemoCharacter.GetPosX(), mDemoCharacter.GetPosY(), 0 };
			break;
		case 3:
			mDemoCharacter = Unit{ "Assets/Textures/TrueHero5.png", mDemoCharacter.GetPosX(), mDemoCharacter.GetPosY(), 0 };
			break;
		case 4:
			mDemoCharacter = Unit{ "Assets/Textures/TrueHero7.png", mDemoCharacter.GetPosX(), mDemoCharacter.GetPosY(), 0 };
			break;
		default:
			break;
		}
	}
	// When less than a second has passed
	else
	{
		// The hero will keep moving right until it has reached salt, as calculated
		mDemoCharacter.SetDirection(Unit::Direction::Right);
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
		mBackground = Unit{ "Assets/Textures/Intro2.png", 0, 0, 0 };
		mDemoCharacter = Unit{ "Assets/Textures/TrueHero7.png", 300, 600, 10 };
		mVillain = Unit{ "Assets/Textures/OddVillain3.png", 700, 600, 0 };
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
			mDemoCharacter.SetDirection(Unit::Direction::Right);
		}
		else
		{
			mDemoCharacter.SetDirection(Unit::Direction::None);
		}
		if (!VillainEaten)
		{
			mVillain.Draw(mShader);
		}
	}
	// When more than 10 seconds have passed, open the game
	else
	{
		mPlayIntroFlag = false;
		mBackground = Unit{ "Assets/Textures/FightBG.png", 0, 0, 0 };
		// Determine a spot for the villain to spawn
		int X{ rand() % (mWindowWidth - 100) };
		int Y{ rand() % (mWindowHeight - 100) };
		mVillain = Unit{ mVillainPicture, X, Y, 0 };
		// Reset the frame counter and salt eaten
		mFrameCounter = 0;
		mSaltConsumed = 0;
		ClearSalt();
	}
}

// Ending sequence for villain or hero
void MyGameApp::VictorySequence()
{
	bool SecondElapsed{ mFrameCounter % FRAMES_PER_SECOND == 0 };
	switch (mDemoCharacter.GetDirection())
	{
	case Unit::Direction::Down:
		if (SecondElapsed)
			mDemoCharacter.SetDirection(Unit::Direction::Up);
		break;
	case Unit::Direction::Up:
		if (SecondElapsed)
			mDemoCharacter.SetDirection(Unit::Direction::Down);
		break;
	default:
		mDemoCharacter.SetDirection(Unit::Direction::Down);
	}
	mDemoCharacter.UpdatePosition(mWindowWidth, mWindowHeight);
	mDemoCharacter.Draw(mShader);
}


// Spawn salt at a random location in the map
void MyGameApp::SpawnSalt()
{
	// Determine the position for the new salt
	int newX{ rand() % (mWindowWidth - 100) };
	int newY{ rand() % (mWindowHeight - 100) };
	mSalt.push_back(Unit{ "Assets/Textures/Salt.png", newX, newY, 0 });
}

// Teleports the villain to a random location and checks if it should evolve
void MyGameApp::TeleportVillain()
{
	// Teleport the villain after a certain interval
	if (!mEndFlag && mFrameCounter % (FRAMES_PER_SECOND * 3) == 0)
	{
		// Check if the villain should evolve
		EvolveVillain();
		// Determine a spot for the villain to teleport
		int newX{ rand() % (mWindowWidth - 100) };
		int newY{ rand() % (mWindowHeight - 100) };
		// Create a new villain based on current values
		mVillain = Unit{ mVillainPicture, newX, newY, 0 };
	}
}

// This function will evolve the villain when appropriate
void MyGameApp::EvolveVillain()
{
	// After enough time passes increase the stage of the villain
	if (mFrameCounter > FRAMES_PER_SECOND * 10)
	{
		if (mVillainPicture[26] < '9')
		{
			mVillainPicture[26]++;
		}
		// Victory Condition: The odd villain reaches its final stage
		else
		{
			mEndFlag = VillainVictoryCondition();
		}
	}
}

// Evolves the hero when appropriate
void MyGameApp::EvolveHero()
{
	// When the hero consumes at least 3 pieces of salt it will evolve
	if (!mFinalHeroFlag && !mEndFlag && mSaltConsumed >= 3)
	{
		if (mHeroPicture[24] < '9')
		{
			mSaltConsumed -= 3;
			mHeroPicture[24]++;
			mHero = Unit{ mHeroPicture, mHero.GetPosX(), mHero.GetPosY(), 10 };
		}
		// At the final stage of the hero, it becomes FinalHero
		else
		{
			mHero = Unit{ "Assets/Textures/FinalHero.png", mHero.GetPosX(), mHero.GetPosY(), 10 };
			mFinalHeroFlag = true;
		}
	}
}

// Always returns true and will cause the villain's victory to play
bool MyGameApp::VillainVictoryCondition()
{
	mBackground = Unit{ "Assets/Textures/VillainEnd.png", 0, 0, 0 };
	mDemoCharacter = Unit{ "Assets/Textures/FinalVillain.png", mWindowWidth / 4, mWindowHeight / 4, 10 };
	// Reset the frame counter
	mFrameCounter = 0;
	ClearSalt();
	return true;
}

// Will cause the Hero's victory to play when the villain is eaten
bool MyGameApp::HeroVictoryCondition()
{
	// Victory Condition: The hero needs to be more powerful than the villain to win
	if (mFinalHeroFlag || mHero.GetUnitWidth() > mVillain.GetUnitWidth())
	{
		mFinalHeroFlag = true;
		mBackground = Unit{ "Assets/Textures/HeroEnd.png", 0, 0, 0 };
		mDemoCharacter = Unit{ "Assets/Textures/FinalHero.png", mWindowWidth / 3, mWindowHeight / 4, 10 };
		mHero = Unit{ "Assets/Textures/FinalHero.png", mHero.GetPosX(), mHero.GetPosY(), 10 };
		// Reset the frame counter
		mFrameCounter = 0;
		ClearSalt();
		return true;
	}
	return false;
}

// Determines if the villain should be eaten by the hero, this would cause a victory
void MyGameApp::EatVillain()
{
	if (!mEndFlag && mHero.CollideWith(mVillain))
	{
		mEndFlag = HeroVictoryCondition();
	}
}

// Determines if salt should be eaten by the hero
void MyGameApp::EatSalt()
{
	auto it = mSalt.begin();
	while (it != mSalt.end())
	{
		if (mHero.CollideWith(*it))
		{
			it = mSalt.erase(it);
			mSaltConsumed++;
		}
		else
			it++;
	}
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
	mSalt.erase(mSalt.begin(), mSalt.end());
}

// This function detects any key presses that occur
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
	case SALT_KEY_W:
		mHero.SetDirection(Unit::Direction::Up);
		break;
	case SALT_KEY_A:
		mHero.SetDirection(Unit::Direction::Left);
		break;
	case SALT_KEY_S:
		mHero.SetDirection(Unit::Direction::Down);
		break;
	case SALT_KEY_D:
		mHero.SetDirection(Unit::Direction::Right);
		break;
	// Debug mode will allow the user to spawn salt freely using the space key
	case SALT_KEY_SPACE:
#ifdef GAME_DEBUG
		SpawnSalt();
#endif
		break;
	}
}