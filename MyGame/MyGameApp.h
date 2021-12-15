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
	Unit mHero;
	std::vector<Unit> mVillains;
	int mFrameCounter;
	Salt::Shader mShader;
	int windowWidth{ 0 };
	int windowHeight{ 0 };
};
