#pragma once

#include "Salt.h"
class Unit
{
public:
	Unit() = delete;
	Unit(const std::string& imageFile, int xPos, int yPos);
	int GetUnitWidth() const;
	int GetUnitHeight() const;
	void SetPosX(int newX);
	void SetPosY(int newY);
	int GetPosX() const;
	int GetPosY() const;
	// CollideWith returns true if units collide
	bool CollideWith(const Unit &other) const;

	void Draw(Salt::Shader& shader);
private:
	Salt::Sprite mImage;
	int mPosX;
	int mPosY;
};

