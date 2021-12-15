#include "Unit.h"

Unit::Unit(const std::string& imageFile, int xPos, int yPos)
	: mPosX(xPos), mPosY(yPos)
{
	mImage.LoadImage(imageFile);
}

int Unit::GetUnitWidth() const
{
	return mImage.GetWidth();
}

int Unit::GetUnitHeight() const
{
	return mImage.GetHeight();
}

void Unit::SetPosX(int newX)
{
	mPosX = newX;
}

void Unit::SetPosY(int newY)
{
	mPosY = newY;
}

int Unit::GetPosX() const
{
	return mPosX;
}

int Unit::GetPosY() const
{
	return mPosY;
}

bool Unit::CollideWith(const Unit& other) const
{
	int oXleft{ other.GetPosX() };
	int oXright{ other.GetPosX() + other.GetUnitWidth() };
	int oYbottom{ other.GetPosY() };
	int oYtop{ other.GetPosY() + other.GetUnitHeight() };

	// When intersecting based on the x axis
	bool intersectOnX{
		(mPosX <= oXleft && oXleft <= mPosX + GetUnitWidth()) ||
		(mPosX <= oXright && oXright <= mPosX + GetUnitWidth()) 
	};

	// When intersecting based on the y axis
	bool intersectOnY{
		(mPosY <= oYbottom && oYbottom <= mPosY + GetUnitHeight()) ||
		(mPosY <= oYtop && oYtop <= mPosY + GetUnitHeight())
	};

	return intersectOnX && intersectOnY;
}

void Unit::Draw(Salt::Shader& shader)
{
	Salt::Renderer::Draw(mImage, mPosX, mPosY, 
		mImage.GetWidth(), mImage.GetHeight(), shader);
}
