/*
Author: Charles Vega
Last Modified: December 17, 2021
This is the implementation file for the Background class
The Background class will provide the background image for the game
It has simple Draw and SetBackground functions for ease of use by MyGameApp.cpp
*/
#include "Background.h"

Background::Background(const std::string& BackgroundPicture)
{
	mBackground.LoadImage(BackgroundPicture);
}

void Background::Draw(Salt::Shader& shader)
{
	Salt::Renderer::Draw(mBackground, 0, 0,
		mBackground.GetWidth(), mBackground.GetHeight(), shader);
}

void Background::SetBackground(const std::string& BackgroundPicture)
{
	mBackground.LoadImage(BackgroundPicture);
}


