/*
Author: Charles Vega
Last Modified: December 17, 2021
This is the header file for the DemoUnit class
The DemoUnit class is used for introduction and ending purposes
A DemoUnit will be guided by MyGameApp.cpp to demonstrate the intro and end
*/
#include "DemoUnit.h"

DemoUnit::DemoUnit(const std::string& DemoPicture, int xPos, int yPos, int speed)
	: mPosX(xPos), mPosY(yPos), mSpeed(speed), mDirection(Direction::Right)
{
	mDemo.LoadImage(DemoPicture);
}

void DemoUnit::Draw(Salt::Shader& shader)
{
	Salt::Renderer::Draw(mDemo, mPosX, mPosY,
		mDemo.GetWidth(), mDemo.GetHeight(), shader);
}

int DemoUnit::GetPosX() const
{
	return mPosX;
}

int DemoUnit::GetPosY() const
{
	return mPosY;
}

void DemoUnit::SetPosX(int newX)
{
	mPosX = newX;
}

void DemoUnit::SetPosY(int newY)
{
	mPosY = newY;
}

void DemoUnit::UpdatePosition(int windowWidth, int windowHeight)
{
	switch (mDirection)
	{
	case Direction::Down:
		if (IsPositionPossible(mPosX, mPosY - mSpeed, windowWidth, windowHeight))
			mPosY -= mSpeed;
		break;
	case Direction::Up:
		if (IsPositionPossible(mPosX, mPosY + mSpeed, windowWidth, windowHeight))
			mPosY += mSpeed;
		break;
	case Direction::Right:
		if (IsPositionPossible(mPosX + mSpeed, mPosY, windowWidth, windowHeight))
			mPosX += mSpeed;
		break;
	case Direction::None:
		break;
	default:
		break;
	}
}

void DemoUnit::SetDemo(const std::string& DemoPicture)
{
	mDemo.LoadImage(DemoPicture);
}

void DemoUnit::SetDirection(DemoUnit::Direction newDirection)
{
	mDirection = newDirection;
}

DemoUnit::Direction DemoUnit::GetDirection() const
{
	return mDirection;
}

bool DemoUnit::IsPositionPossible(int newX, int newY, int& windowWidth, int& windowHeight) const
{
	if (newX < 0 ||
		newY < 0 ||
		newX + mDemo.GetWidth() > windowWidth ||
		newY + mDemo.GetHeight() > windowHeight) return false;
	else
		return true;
}
