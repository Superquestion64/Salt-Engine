#pragma once

#include "pch.h"
#include "SaltUtils.h"
#include "SpriteImplementation.h"

namespace Salt
{
	class SALT_API Sprite
	{
	public:
		Sprite();
		void LoadImage(const std::string& pictureFile);
		int GetWidth() const;
		int GetHeight() const;
		void Bind();

	private:
		std::unique_ptr<SpriteImplementation> mSpriteImplementation;
	};
}


