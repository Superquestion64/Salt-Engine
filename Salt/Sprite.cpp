#include "pch.h"
#include "Sprite.h"
#include "OpenGLimpl/OpenGLSprite.h"

namespace Salt
{
	// Default constructor checks if OpenGL is defined
	Sprite::Sprite()
	{
#ifdef SALT_OPENGL
		mSpriteImplementation = std::unique_ptr<SpriteImplementation>{ new OpenGLSprite };
#else
		#only_openGL_is_supported_so_far
#endif
	}

	// Loads the image based on the given address provided in pictureFile using OpenGL
	void Sprite::LoadImage(const std::string& pictureFile)
	{
		mSpriteImplementation.reset(new OpenGLSprite);
		mSpriteImplementation->LoadImage(pictureFile);
	}

	// Returns the width of the sprite
	int Sprite::GetWidth() const
	{
		return mSpriteImplementation->GetWidth();
	}

	// Returns the height of the sprite
	int Sprite::GetHeight() const
	{
		return mSpriteImplementation->GetHeight();
	}

	// Binds the image to the sprite object
	void Sprite::Bind()
	{
		mSpriteImplementation->Bind();
	}
}

