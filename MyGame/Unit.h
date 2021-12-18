#pragma once
/*
Author: Charles Vega
Last Modified: December 17, 2021
This is a purely virtual class for Units
Any object that inherits from this class is able to be eaten by the hero
This is currently inherited by the Hero, Villain, and SaltSpawner classes
*/
#include "Salt.h"
class Unit
{
public:
	// Draws the unit when given a shader object
	virtual void Draw(Salt::Shader& shader) = 0;
	// Returns the x position of the unit
	virtual int GetPosX() const = 0;
	// Returns the y position of the unit
	virtual int GetPosY() const = 0;
	// Returns the width of the unit
	virtual int GetUnitWidth() const = 0;
	// Returns the height of the unit
	virtual int GetUnitHeight() const = 0;
	virtual void UnitDelete() = 0;
	virtual ~Unit() {};
};

