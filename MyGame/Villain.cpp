/*
Author: Charles Vega
Last Modified: December 17, 2021
This is the implementation file for the Villain class
The Villain will randomly teleport across the map to avoid the hero
As time passes the Villain will evolve and become harder for the hero to defeat
At its final form the Villain automatically wins the game
*/
#include "Villain.h"

Villain::Villain() : mPosX(0), mPosY(0)
{
}

Villain::Villain(const std::string& VillainPicture) : mPosX(0), mPosY(0)
{
	mVillainPicture = VillainPicture;
	mVillain.LoadImage(VillainPicture);
}

Villain::~Villain()
{
	UnitDelete();
}

bool Villain::Update(int windowWidth, int windowHeight)
{
	Teleport(windowWidth, windowHeight);
	return EvolveVillain();
}

int Villain::GetUnitWidth() const
{
	return mVillain.GetWidth();
}

int Villain::GetUnitHeight() const
{
	return mVillain.GetHeight();
}

void Villain::SetPosX(int newX)
{
	mPosX = newX;
}

void Villain::SetPosY(int newY)
{
	mPosY = newY;
}

int Villain::GetPosX() const
{
	return mPosX;
}

int Villain::GetPosY() const
{
	return mPosY;
}

void Villain::Draw(Salt::Shader& shader)
{
	Salt::Renderer::Draw(mVillain, mPosX, mPosY,
		mVillain.GetWidth(), mVillain.GetHeight(), shader);
}

void Villain::SetVillain(const std::string& VillainPicture)
{
	mVillainPicture = VillainPicture;
	mVillain.LoadImage(VillainPicture);
}

void Villain::Teleport(int windowWidth, int windowHeight)
{
	// Determine a spot for the villain to teleport
	int newX{ rand() % (windowWidth - 100) };
	int newY{ rand() % (windowHeight - 100) };
	SetPosX(newX);
	SetPosY(newY);
}

void Villain::UnitDelete()
{
	mVillain.SpriteDelete();
}

bool Villain::EvolveVillain()
{
	if (mVillainPicture[26] < '9')
	{
		mVillainPicture[26]++;
		SetVillain(mVillainPicture);
		return false;
	}
	// Victory Condition: The odd villain reaches its final stage
	else
	{
		SetVillain("Assets/Textures/FinalVillain.png");
		return true;
	}
}

