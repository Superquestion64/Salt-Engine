#include "Unit.h"

Unit::Unit(const std::string& imageFile, int xPos, int yPos, int speed)
	: mPosX(xPos), mPosY(yPos), mSpeed(speed), mDirection(Direction::None)
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

void Unit::SetDirection(Unit::Direction newDirection)
{
	mDirection = newDirection;
}

int Unit::GetPosX() const
{
	return mPosX;
}

int Unit::GetPosY() const
{
	return mPosY;
}

int Unit::GetSpeed() const
{
	return mSpeed;
}

Unit::Direction Unit::GetDirection() const
{
	return mDirection;
}

// Determines when the hero collides with the villain
bool Unit::CollideWith(const Unit& villain) const
{
	// Left side of villain
	int villainXleft{ villain.GetPosX() };
	// Right side of villain
	int villainXright{ villain.GetPosX() + villain.GetUnitWidth() };
	// Bottom of villain
	int villainYbottom{ villain.GetPosY() };
	// Top of villain
	int villainYtop{ villain.GetPosY() + villain.GetUnitHeight() };

	// When intersecting based on the x axis
	bool intersectOnX{
		(mPosX <= villainXleft && villainXleft <= mPosX + GetUnitWidth()) ||
		(mPosX <= villainXright && villainXright <= mPosX + GetUnitWidth())
	};

	// When intersecting based on the y axis
	bool intersectOnY{
		(mPosY <= villainYbottom && villainYbottom <= mPosY + GetUnitHeight()) ||
		(mPosY <= villainYtop && villainYtop <= mPosY + GetUnitHeight())
	};

	return intersectOnX && intersectOnY;
}

void Unit::Draw(Salt::Shader& shader)
{
	Salt::Renderer::Draw(mImage, mPosX, mPosY, 
		mImage.GetWidth(), mImage.GetHeight(), shader);
}

void Unit::UpdatePosition(int windowWidth, int windowHeight)
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
	case Direction::Left:
		if (IsPositionPossible(mPosX - mSpeed, mPosY, windowWidth, windowHeight))
			mPosX -= mSpeed;
		break;
	case Direction::Right:
		if (IsPositionPossible(mPosX + mSpeed, mPosY, windowWidth, windowHeight))
			mPosX += mSpeed;
		break;
	}
}

bool Unit::IsPositionPossible(int newX, int newY, int& windowWidth, int& windowHeight) const
{
	if (newX < 0 ||
		newY < 0 ||
		newX + mImage.GetWidth() > windowWidth ||
		newY + mImage.GetHeight() > windowHeight) return false;
	else
		return true;
}
