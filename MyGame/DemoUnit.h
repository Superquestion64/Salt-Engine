#pragma once
/*
Author: Charles Vega
Last Modified: December 17, 2021
This is the header file for the DemoUnit class
The DemoUnit class is used for introduction and ending purposes
A DemoUnit will be guided by MyGameApp.cpp to demonstrate the intro and end
*/
#include "Salt.h"
class DemoUnit
{
public:
	DemoUnit(const std::string& DemoPicture, int xPos, int yPos, int speed);
	// Draws the demo unit when given a shader object
	void Draw(Salt::Shader& shader);
	enum class Direction {
		None,
		Up,
		Down,
		Right
	};
	// Returns the x position of the demo unit
	int GetPosX() const;
	// Returns the y position of the demo unit
	int GetPosY() const;
	// Sets the x position of the demo unit
	void SetPosX(int newX);
	// Sets the y position of the demo unit
	void SetPosY(int newY);
	// Will calculate the next position of the demo unit based on its speed
	void UpdatePosition(int windowWidth, int windowHeight);
	// Sets the image of the demo unit
	void SetDemo(const std::string& DemoPicture);
	// Sets the current direction of the demo unit
	void SetDirection(DemoUnit::Direction newDirection);
	// Returns the current direction of the Hero
	DemoUnit::Direction GetDirection() const;
	// Deletes the demo texture when we don't need it
	void UnitDelete();
private:
	// Sprite object of the demo unit's image
	Salt::Sprite mDemo;
	// The x position of the demo unit
	int mPosX;
	// The y position of the demo unit
	int mPosY;
	// The speed of the demo unit
	int mSpeed;
	// The current direction of the demo unit
	Direction mDirection;
	// Helper function calculates if a new position would put the demo unit outside of the window boundaries
	bool IsPositionPossible(int newX, int newY, int& windowWidth, int& windowHeight) const;
};

