#pragma once

#include "Salt.h"
#include "Unit.h"

class MyGameApp : public Salt::SaltApp
{
public:
	MyGameApp();
	virtual void OnUpdate() override;
private:
	Unit mHero;
	Salt::Shader mShader;
};
