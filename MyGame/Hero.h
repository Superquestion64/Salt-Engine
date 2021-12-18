#pragma once
/*
Author: Charles Vega
Last Modified: December 17, 2021
This is the header file for the Hero class
The Hero is a playable character by the user, their key inputs will affect this object
It inherits from the Unit class however is not intended to be eaten, it will eat other Units
Has logic in EatVillain() that determines when the hero wins
*/
#include "Salt.h"
#include "Unit.h"
#include "SaltSpawner.h"
#include <vector>

class Hero : public Unit
{
public:
	// Default constructor sets speed to 10 and sets direction to None
	Hero();
	// Initializes the image, x position, y position, and speed of the Hero
	Hero(const std::string& HeroPicture, int xPos, int yPos, int speed);
	// Defines the directions a Hero can have
	enum class Direction {
		None,
		Up,
		Down,
		Left,
		Right
	};
	bool Update(Unit& Villain, std::vector<SaltSpawner>& mSalt);
	// Returns width of the Hero
	virtual int GetUnitWidth() const override;
	// Returns height of the Hero
	virtual int GetUnitHeight() const override;
	// Returns the x position of the Hero
	virtual int GetPosX() const override;
	// Returns the y position of the Hero
	virtual int GetPosY() const override;
	// Draws the Hero when given a shader object
	virtual void Draw(Salt::Shader& shader) override;
	// Sets the image of the hero
	void SetHero(const std::string& HeroPicture);
	// Returns the speed of the Hero
	int GetSpeed() const;
	// Returns the current direction of the Hero
	Hero::Direction GetDirection() const;
	// Sets the x position of the Hero
	void SetPosX(int newX);
	// Sets the y position of the Hero
	void SetPosY(int newY);
	// Sets the current direction of the Hero
	void SetDirection(Hero::Direction newDirection);
	// CollideWith returns true if units collide
	bool CollideWith(const Unit &unit) const;
	// Will calculate the next position of the Hero based on its speed. Cannot go out of window boundaries
	void UpdatePosition(int windowWidth, int windowHeight);
	// Function to get a random direction
	Hero::Direction NewDirection() const;
private:
	// Helper function calculates if a new position would put the Hero outside of the window boundaries
	bool IsPositionPossible(int newX, int newY, int& windowWidth, int& windowHeight) const;
	// Determines if the villain should be eaten by the hero
	bool EatVillain(Unit& Villain);
	// Determines if salt should be eaten by the hero
	void EatSalt(std::vector<SaltSpawner>& mSalt);
	// Evolves the hero when appropriate
	void EvolveHero();
	// Will contain the address of the hero's picture
	std::string mHeroPicture;
	// Keeps track of the amount of salt eaten by the hero
	size_t mSaltConsumed{ 0 };
	// Sprite object of the Hero's image
	Salt::Sprite mHero;
	// The x position of the Hero
	int mPosX;
	// The y position of the Hero
	int mPosY;
	// The speed of the Hero
	int mSpeed;
	// Will be set to true if the hero reaches final form
	bool mFinalHeroFlag{ false };
	// The current direction of the Hero
	Direction mDirection;
};

