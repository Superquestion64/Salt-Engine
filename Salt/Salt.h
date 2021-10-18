#pragma once

#include "SaltUtils.h"
#include "SaltApp.h"
#include "GameWindow.h"

#define START_SALT_GAME(classname)\
int main()\
{\
	classname _salt_game;\
	_salt_game.Run();\
}