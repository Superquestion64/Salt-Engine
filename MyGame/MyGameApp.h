#pragma once

#include "Salt.h"
#include "Unit.h"
#include <vector>

class MyGameApp : public Salt::SaltApp
{
public:
	MyGameApp();
	virtual void OnUpdate() override;
	virtual void OnKeyPressed(Salt::KeyPressedEvent& event) override;
private:
	Unit mHero, mVillain;
	std::vector<Unit> mSalt;
	bool mEndFlag{ false };
	bool mFinalHeroFlag{ false };
	size_t mFrameCounter;
	size_t mSaltConsumed;
	Salt::Shader mShader;
	std::string mHeroPicture;
	std::string mVillainPicture;
	int mWindowWidth{ 0 };
	int mWindowHeight{ 0 };
};
