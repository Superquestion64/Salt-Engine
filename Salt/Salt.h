#pragma once

#include "SaltUtils.h"
#include "SaltApp.h"
#include "GameWindow.h"
#include "Sprite.h"
#include "Shader.h"
#include "Renderer.h"

#define START_SALT_GAME(classname)\
int main()\
{\
	classname _salt_game;\
	_salt_game.Run();\
}