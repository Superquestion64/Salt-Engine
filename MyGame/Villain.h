#pragma once
/*
Author: Charles Vega
Last Modified: December 17, 2021
This is the header file for the Villain class
The Villain will randomly teleport across the map to avoid the hero
As time passes the Villain will evolve and become harder for the hero to defeat
At its final form the Villain automatically wins the game
*/
#include "Salt.h"
#include "Unit.h"
class Villain : public Unit
{
public:
	// Default constructor initializes everything to 0
	Villain();
	// Initializes the image, x position, and y position
	Villain(const std::string& VillainPicture);
	bool Update(int windowWidth, int windowHeight);
	// Returns width of the villain
	virtual int GetUnitWidth() const override;
	// Returns height of the villain
	virtual int GetUnitHeight() const override;
	// Returns the x position of the villain
	virtual int GetPosX() const override;
	// Returns the y position of the villain
	virtual int GetPosY() const override;
	// Draws the villain when given a shader object
	virtual void Draw(Salt::Shader& shader) override;
	// Sets the picture of the villain
	void SetVillain(const std::string& VillainPicture);
	// Sets the x position of the villain
	void SetPosX(int newX);
	// Sets the y position of the villain
	void SetPosY(int newY);
	// Will teleport the villain in a random place on the map. Cannot go out of window boundaries
	void Teleport(int windowWidth, int windowHeight);
	virtual void UnitDelete() override;
private:
	// Sprite object of the villain's image
	Salt::Sprite mVillain;
	// Evolves the villain when appropriate, returns true when it reaches its final form
	bool EvolveVillain();
	// Will contain the address of the villain's picture
	std::string mVillainPicture;
	// The x position of the villain
	int mPosX;
	// The y position of the villain
	int mPosY;
};

