#include "Unit.h"

Unit::Unit() : mPosX(0), mPosY(0), mSpeed(0), mDirection(Direction::None)
{
}

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
		(mPosX <= villainXright && villainXright <= mPosX + GetUnitWidth()) ||
		(villainXleft <= mPosX && mPosX <= villainXright) ||
		(villainXleft <= mPosX + GetUnitWidth() && mPosX + GetUnitWidth() <= villainXright)
	};

	// When intersecting based on the y axis
	bool intersectOnY{
		(mPosY <= villainYbottom && villainYbottom <= mPosY + GetUnitHeight()) ||
		(mPosY <= villainYtop && villainYtop <= mPosY + GetUnitHeight()) ||
		(villainYbottom <= mPosY && mPosY <= villainYtop) ||
		(villainYbottom <= mPosY + GetUnitHeight() && mPosY + GetUnitHeight() <= villainYtop)
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
	case Direction::None:
		break;
	default:
		break;
	}
}

Unit::Direction Unit::NewDirection() const
{
	Unit::Direction newDir;
	int dirVal{ rand() % 4 };
	switch (dirVal)
	{
	case 0:
		newDir = Unit::Direction::Down;
		break;
	case 1:
		newDir = Unit::Direction::Up;
		break;
	case 2:
		newDir = Unit::Direction::Left;
		break;
	default:
		newDir = Unit::Direction::Right;
		break;
	}
	return newDir;
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
