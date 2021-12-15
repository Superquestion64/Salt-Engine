#pragma once
/* 
Author: Charles Vega
Last Modified: December 15, 2021
This is the header class for a game created through the Salt engine
In the game the hero must consume salt to evolve
The villain rapidly evolves with time and teleports around the map
When the hero is powerful enough they can eat the villain and win
If the villain reaches its final stage it becomes game over
*/

#include "Salt.h"
#include "Unit.h"
#include <vector>

class MyGameApp : public Salt::SaltApp
{
public:
	// Constructor
	MyGameApp();
	// This function runs on every frame of the game
	virtual void OnUpdate() override;
	// This function detects any key presses that occur
	virtual void OnKeyPressed(Salt::KeyPressedEvent& event) override;

private:
	// mHero is playable, mVillain will be the villain, mBackground is the background
	Unit mHero, mVillain, mBackground;
	// The demo character can be the hero or the villain depending on the ending
	// The demo character is always the hero for the intro
	Unit mDemoCharacter{ "Assets/Textures/TrueHero1.png", 400, 600, 10 };
	// The objects in mSalt are meant to be eaten by the hero
	std::vector<Unit> mSalt;
	// Checks if an ending has been reached
	bool mEndFlag{ false };
	// Will be set to false when the intro is finished
	bool mPlayIntroFlag{ true };
	// Will be set to true when it should play
	bool mSetIntro2Flag{ false };
	// Will be set to true if the hero reaches final form
	bool mFinalHeroFlag{ false };
	// Counts the number of frames that have passed
	size_t mFrameCounter;
	// Keeps track of the amount of salt eaten by the hero
	size_t mSaltConsumed;
	// Shader object for drawing
	Salt::Shader mShader;
	// Will contain the address of the hero's picture
	std::string mHeroPicture;
	// Will contain the address of the villain's picture
	std::string mVillainPicture;
	// Stores the width and height of the window
	int mWindowWidth{ 0 };
	int mWindowHeight{ 0 };
	// Clear all the salt
	void ClearSalt();
	// Play the intros
	void IntroSequence();
	// Performs intro part 1
	void PlayIntro1();
	// Performs intro part 2
	void PlayIntro2();
	// Ending sequence for villain or hero
	void VictorySequence();
	// Will spawn salt randomly on the map
	void SpawnSalt();
	// Teleports and evolves the villain
	void TeleportVillain();
	// Evolves the villain when appropriate
	void EvolveVillain();
	// Evolves the hero when appropriate
	void EvolveHero();
	// Always returns true and will cause the villain's victory to play
	bool VillainVictoryCondition();
	// Always returns true and will cause the Hero's victory to play
	bool HeroVictoryCondition();
	// Determines if the villain should be eaten by the hero
	void EatVillain();
	// Determines if salt should be eaten by the hero
	void EatSalt();
	// Will draw all the current salt
	void DrawSalt();
};
