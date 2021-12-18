#pragma once
/*
Author: Charles Vega
Last Modified: December 17, 2021
This is the header file for the Background class
The Background class will provide the background image for the game
It has simple Draw and SetBackground functions for ease of use by MyGameApp.cpp
*/
#include "Salt.h"
class Background
{
public:
	// Initializes the background image
	Background(const std::string& BackgroundPicture);
	// Draws the background when given a shader object
	void Draw(Salt::Shader& shader);
	// Sets the background image
	void SetBackground(const std::string& BackgroundPicture);
private:
	// Sprite object of the background's image
	Salt::Sprite mBackground;
};

