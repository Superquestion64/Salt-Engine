#pragma once

#include "Salt.h"
class Unit
{
public:
	// Default constructor initializes everything to 0 and sets direction to None
	Unit();
	// Initializes the image, x position, y position, and speed of the unit
	Unit(const std::string& imageFile, int xPos, int yPos, int speed);
	// Defines the directions a unit can have
	enum class Direction {
		None,
		Up,
		Down,
		Left,
		Right
	};
	// Returns width of the unit
	int GetUnitWidth() const;
	// Returns height of the unit
	int GetUnitHeight() const;
	// Returns the x position of the unit
	int GetPosX() const;
	// Returns the y position of the unit
	int GetPosY() const;
	// Returns the speed of the unit
	int GetSpeed() const;
	// Returns the current direction of the unit
	Unit::Direction GetDirection() const;
	// Sets the x position of the unit
	void SetPosX(int newX);
	// Sets the y position of the unit
	void SetPosY(int newY);
	// Sets the current direction of the unit
	void SetDirection(Unit::Direction newDirection);
	// CollideWith returns true if units collide
	bool CollideWith(const Unit &other) const;
	// Draws the unit when given a shader object
	void Draw(Salt::Shader& shader);
	// Will calculate the next position of the unit based on its speed. Cannot go out of window boundaries
	void UpdatePosition(int windowWidth, int windowHeight);
	// Function to get a random direction
	Unit::Direction NewDirection() const;
private:
	// Helper function calculates if a new position would put the unit outside of the window boundaries
	bool IsPositionPossible(int newX, int newY, int& windowWidth, int& windowHeight) const;
	// Sprite object of the unit's image
	Salt::Sprite mImage;
	// The x position of the unit
	int mPosX;
	// The y position of the unit
	int mPosY;
	// The speed of the unit
	int mSpeed;
	// The current direction of the unit
	Direction mDirection;
};

