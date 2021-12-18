#pragma once
/* 
Author: Charles Vega
Last Modified: December 17, 2021
This is the header class for a game created through the Salt engine
In the game the hero must consume salt to evolve
The villain rapidly evolves with time and teleports around the map
When the hero is powerful enough they can eat the villain and win
If the villain reaches its final form it becomes game over
*/
#include "Salt.h"
#include "Hero.h"
#include "Background.h"
#include "SaltSpawner.h"
#include "Villain.h"
#include "DemoUnit.h"
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
	// mHero is playable, mVillain will be the villain
	// The current stage of the hero is at index 24
	Hero mHero{ "Assets/Textures/TrueHero1.png", 0, 0, 10 };
	// The current stage of the villain is at index 26
	Villain mVillain{ "Assets/Textures/OddVillain1.png" };
	// BG is the background, we initilaize it with intro part 1
	Background BG{ "Assets/Textures/Intro1.png" };
	// The demo character can be the hero or the villain depending on the ending
	// The demo character is always the hero for the intro
	DemoUnit mDemoCharacter{ "Assets/Textures/TrueHero1.png", 400, 600, 10 };
	// The objects in mSalt are meant to be eaten by the hero
	std::vector<SaltSpawner> mSalt;
	// Checks if an ending has been reached
	bool mEndFlag{ false };
	// Will be set to false when the intro is finished
	bool mPlayIntroFlag{ true };
	// Will be set to true when it should intro part 2 should play
	bool mSetIntro2Flag{ false };
	// Counts the number of frames that have passed
	size_t mFrameCounter;
	// Shader object for drawing
	Salt::Shader mShader;
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
	// Will set up the ending sequence for the villain's victory
	void VillainVictorySetUp();
	// Will set up the ending sequence for the hero's victory
	void HeroVictorySetUp();
	// Will Draw all the salt on the map
	void DrawSalt();
};
