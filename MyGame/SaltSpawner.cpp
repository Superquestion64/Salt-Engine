/*
Author: Charles Vega
Last Modified: December 17, 2021
This is the implementation file for the SaltSpawner class
The SaltSpawner class inherits from the virtual Unit class, therfore the hero can eat this object
SaltSpawner will define a Salt object that can be eaten by the hero
The hero will have to eat from a vector of salt objects provided by MyGameApp.cpp
*/
#include "SaltSpawner.h"

SaltSpawner::SaltSpawner(const std::string& SaltPicture, int xPos, int yPos)
	: mPosX(xPos), mPosY(yPos)
{
	mSalt.LoadImage(SaltPicture);
}

void SaltSpawner::Draw(Salt::Shader& shader)
{
	Salt::Renderer::Draw(mSalt, mPosX, mPosY,
		mSalt.GetWidth(), mSalt.GetHeight(), shader);
}

int SaltSpawner::GetPosX() const
{
	return mPosX;
}

int SaltSpawner::GetPosY() const
{
	return mPosY;
}

int SaltSpawner::GetUnitWidth() const
{
	return mSalt.GetWidth();
}

int SaltSpawner::GetUnitHeight() const
{
	return mSalt.GetHeight();
}

void SaltSpawner::UnitDelete()
{
	mSalt.SpriteDelete();
}
