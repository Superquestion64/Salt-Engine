#pragma once
/*
Author: Charles Vega
Last Modified: December 17, 2021
This is the header file for the SaltSpawner class
The SaltSpawner class inherits from the virtual Unit class, therfore the hero can eat this object
SaltSpawner will define a Salt object that can be eaten by the hero
The hero will have to eat from a vector of salt objects provided by MyGameApp.cpp
*/
#include "Salt.h"
#include "Unit.h"
class SaltSpawner : public Unit
{
public:
	// Initializes the salt's image
	SaltSpawner(const std::string& SaltPicture, int xPos, int yPos);

	// Draws the salt when given a shader object
	virtual void Draw(Salt::Shader& shader) override;
	// Returns the x position of the salt
	virtual int GetPosX() const override;
	// Returns the y position of the salt
	virtual int GetPosY() const override;
	// Returns the width of the salt
	virtual int GetUnitWidth() const override;
	// Returns the height of the salt
	virtual int GetUnitHeight() const override;
	// Deletes the salt texture when we don't need it
	virtual void UnitDelete() override;
private:
	// Sprite object of the salt's image
	Salt::Sprite mSalt;
	// The x position of the salt
	int mPosX;
	// The y position of the salt
	int mPosY;
};

