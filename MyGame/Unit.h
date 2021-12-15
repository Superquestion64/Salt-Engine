#pragma once

#include "Salt.h"
class Unit
{
public:
	Unit() = delete;
	Unit(const std::string& imageFile, int xPos, int yPos, int speed);
	enum class Direction {
		None,
		Up,
		Down,
		Left,
		Right
	};
	int GetUnitWidth() const;
	int GetUnitHeight() const;
	int GetPosX() const;
	int GetPosY() const;
	int GetSpeed() const;
	Unit::Direction GetDirection() const;
	void SetPosX(int newX);
	void SetPosY(int newY);
	void SetDirection(Unit::Direction newDirection);
	// CollideWith returns true if units collide
	bool CollideWith(const Unit &other) const;
	void Draw(Salt::Shader& shader);
	void UpdatePosition(int windowWidth, int windowHeight);
private:
	bool IsPositionPossible(int newX, int newY, int& windowWidth, int& windowHeight) const;

	Salt::Sprite mImage;
	int mPosX;
	int mPosY;
	int mSpeed;
	Direction mDirection;
};

