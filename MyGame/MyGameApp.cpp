#include "MyGameApp.h"
#include "Unit.h"

MyGameApp::MyGameApp() : mFrameCounter(0)
{
	// The current stage of the hero is at index 24
	mHeroPicture = "Assets/Textures/TrueHero1.png";
	// The current stage of the villain is at index 26
	mVillainPicture = "Assets/Textures/OddVillain1.png";
	mHero = Unit{ mHeroPicture, 0, 0, 10 };
	mVillain = Unit{ mVillainPicture, 0, 0, 0 };
	mShader.Load("Assets/Shader/myVertexShader.glsl",
		"Assets/Shader/myFragmentShader.glsl");
	mShader.SetVec2IntUniform("screenSize", 1280, 1280);
	mWindowWidth = mShader.GetWindowWidth();
	mWindowHeight = mShader.GetWindowHeight();
}

void MyGameApp::OnUpdate()
{
	// Spawn salt every second
	if (mFrameCounter % FRAMES_PER_SECOND == 0)
	{
		// Determine the position for the new salt
		int newX{ rand() % (mWindowWidth - 100) };
		int newY{ rand() % (mWindowHeight - 100) };
		mSalt.push_back(Unit{ "Assets/Textures/Salt.png", newX, newY, 0 });
	}
	// Teleport the villain after a certain interval
	if (!mEndFlag && mFrameCounter % (FRAMES_PER_SECOND * 3) == 0)
	{
		// After enough time passes increase the stage of the villain
		if (mFrameCounter > FRAMES_PER_SECOND * 10)
		{
			if (mVillainPicture[26] < '9')
			{
				mVillainPicture[26]++;
			}
			else
			{
				mEndFlag = true;
				mVillainPicture = "Assets/Textures/FinalVillain.png";
			}
		}
		// Determine a spot for the villain to teleport
		int newX{ rand() % (mWindowWidth - 100) };
		int newY{ rand() % (mWindowHeight - 100) };
		// Create a new villain based on current values

		mVillain = Unit{ mVillainPicture, newX, newY, 0 };
	}

	// Check collisions
	if (!mEndFlag && mHero.CollideWith(mVillain))
	{
		// The hero needs to be more powerful than the villain to win
		if (mFinalHeroFlag || mHero.GetUnitWidth() > mVillain.GetUnitWidth())
		{
			mEndFlag = true;
			mVillain = Unit{ "Assets/Textures/TrueHero1.png" , 0, 0, 0 };
			mHero = Unit{ "Assets/Textures/FinalHero.png", mHero.GetPosX(), mHero.GetPosY(), 10 };
		}
	}
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
	for (auto& salt : mSalt)
	{
		salt.Draw(mShader);
	}
	if (!mFinalHeroFlag && !mEndFlag && mSaltConsumed >= 3)
	{
		if (mHeroPicture[24] < '9')
		{
			mSaltConsumed -= 3;
			mHeroPicture[24]++;
			mHero = Unit{ mHeroPicture, mHero.GetPosX(), mHero.GetPosY(), 10 };
		}
		else
		{
			mHero = Unit{ "Assets/Textures/FinalHero.png", mHero.GetPosX(), mHero.GetPosY(), 10 };
			mFinalHeroFlag = true;
		}
	}
	mVillain.UpdatePosition(mWindowWidth, mWindowHeight);
	mVillain.Draw(mShader);
	mHero.UpdatePosition(mWindowWidth, mWindowHeight);
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
	case SALT_KEY_SPACE:
	#ifdef GAME_DEBUG
		int newX{ rand() % (mWindowWidth - 100) };
		int newY{ rand() % (mWindowHeight - 100) };
		mSalt.push_back(Unit{ "Assets/Textures/Salt.png", newX, newY, 0 });
	#endif
		break;
	}
}
