#pragma once

// This class implements a Sprite object which by default uses OpenGL

#include "pch.h"
#include "SaltUtils.h"
#include "SpriteImplementation.h"

namespace Salt
{
	class SALT_API Sprite
	{
	public:
		// Default constructor checks if OpenGL is defined
		Sprite();
		// Loads the image based on the given address provided in pictureFile
		void LoadImage(const std::string& pictureFile);
		// Returns the width of the sprite
		int GetWidth() const;
		// Returns the height of the sprite
		int GetHeight() const;
		// Binds the image to the sprite object
		void Bind();
		void SpriteDelete();

	private:
		// Any SpriteImplementation class is valid for creating a Sprite
		std::unique_ptr<SpriteImplementation> mSpriteImplementation;
	};
}


