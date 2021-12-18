/*
Author: Charles Vega
Last Modified: December 17, 2021
This is the implementation file for the Hero class
The Hero is a playable character by the user, their key inputs will affect this object
It inherits from the Unit class however is not intended to be eaten, it will eat other Units
Has logic in EatVillain() that determines when the hero wins
*/
#include "Hero.h"

Hero::Hero() : mPosX(0), mPosY(0), mSpeed(10), mDirection(Direction::None)
{
}

Hero::Hero(const std::string& HeroPicture, int xPos, int yPos, int speed)
	: mPosX(xPos), mPosY(yPos), mSpeed(speed), mDirection(Direction::None)
{
	mHeroPicture = HeroPicture;
	mHero.LoadImage(HeroPicture);
}

Hero::~Hero()
{
	UnitDelete();
}



bool Hero::Update(Unit& Villain, std::vector<SaltSpawner>& mSalt)
{
	bool end = EatVillain(Villain);
	EatSalt(mSalt);
	EvolveHero();
	return end;
}

int Hero::GetUnitWidth() const
{
	return mHero.GetWidth();
}

int Hero::GetUnitHeight() const
{
	return mHero.GetHeight();
}

void Hero::SetPosX(int newX)
{
	mPosX = newX;
}

void Hero::SetPosY(int newY)
{
	mPosY = newY;
}

void Hero::SetDirection(Hero::Direction newDirection)
{
	mDirection = newDirection;
}

int Hero::GetPosX() const
{
	return mPosX;
}

int Hero::GetPosY() const
{
	return mPosY;
}

int Hero::GetSpeed() const
{
	return mSpeed;
}

Hero::Direction Hero::GetDirection() const
{
	return mDirection;
}

// Determines when the hero collides with a unit
bool Hero::CollideWith(const Unit& unit) const
{
	// Left side of unit
	int unitXleft{ unit.GetPosX() };
	// Right side of unit
	int unitXright{ unit.GetPosX() + unit.GetUnitWidth() };
	// Bottom of unit
	int unitYbottom{ unit.GetPosY() };
	// Top of unit
	int unitYtop{ unit.GetPosY() + unit.GetUnitHeight() };

	// When intersecting based on the x axis
	bool intersectOnX{
		(mPosX <= unitXleft && unitXleft <= mPosX + GetUnitWidth()) ||
		(mPosX <= unitXright && unitXright <= mPosX + GetUnitWidth()) ||
		(unitXleft <= mPosX && mPosX + GetUnitWidth() <= unitXright)
	};

	// When intersecting based on the y axis
	bool intersectOnY{
		(mPosY <= unitYbottom && unitYbottom <= mPosY + GetUnitHeight()) ||
		(mPosY <= unitYtop && unitYtop <= mPosY + GetUnitHeight()) ||
		(unitYbottom <= mPosY && mPosY + GetUnitHeight() <= unitYtop)
	};

	return intersectOnX && intersectOnY;
}

void Hero::Draw(Salt::Shader& shader)
{
	Salt::Renderer::Draw(mHero, mPosX, mPosY,
		mHero.GetWidth(), mHero.GetHeight(), shader);
}

void Hero::SetHero(const std::string& HeroPicture)
{
	mHero.LoadImage(HeroPicture);
}

void Hero::UpdatePosition(int windowWidth, int windowHeight)
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

Hero::Direction Hero::NewDirection() const
{
	Hero::Direction newDir;
	int dirVal{ rand() % 4 };
	switch (dirVal)
	{
	case 0:
		newDir = Hero::Direction::Down;
		break;
	case 1:
		newDir = Hero::Direction::Up;
		break;
	case 2:
		newDir = Hero::Direction::Left;
		break;
	default:
		newDir = Hero::Direction::Right;
		break;
	}
	return newDir;
}

void Hero::UnitDelete()
{
	mHero.SpriteDelete();
}

bool Hero::IsPositionPossible(int newX, int newY, int& windowWidth, int& windowHeight) const
{
	if (newX < 0 ||
		newY < 0 ||
		newX + mHero.GetWidth() > windowWidth ||
		newY + mHero.GetHeight() > windowHeight) return false;
	else
		return true;
}

bool Hero::EatVillain(Unit& Villain)
{
	if (CollideWith(Villain))
	{
		if (GetUnitWidth() > Villain.GetUnitWidth() || mFinalHeroFlag)
		{
			SetHero("Assets/Textures/FinalHero.png");
			mFinalHeroFlag = true;
			return true;
		}
	}
	return false;
}

void Hero::EatSalt(std::vector<SaltSpawner>& mSalt)
{
	auto it = mSalt.begin();
	while (it != mSalt.end())
	{
		if (CollideWith(*it))
		{
			it->UnitDelete();
			it = mSalt.erase(it);
			mSaltConsumed++;
		}
		else
			it++;
	}
}

void Hero::EvolveHero()
{
	// When the hero consumes at least 3 pieces of salt it will evolve
	if (!mFinalHeroFlag && mSaltConsumed >= 3)
	{
		if (mHeroPicture[24] < '9')
		{
			mSaltConsumed -= 3;
			mHeroPicture[24]++;
			SetHero(mHeroPicture);
		}
		// We need a special case for the hero to reach form 10
		else if (mHeroPicture[24] == '9')
		{
			mSaltConsumed -= 3;
			mHeroPicture = "Assets/Textures/FinalHero.png";
			SetHero("Assets/Textures/TrueHero10.png");
		}
		// At the final stage of the hero, it becomes FinalHero
		else
		{
			SetHero("Assets/Textures/FinalHero.png");
			mFinalHeroFlag = true;
		}
	}
}

