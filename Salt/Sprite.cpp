#include "pch.h"
#include "Sprite.h"
#include "OpenGLimpl/OpenGLSprite.h"

namespace Salt
{
	Sprite::Sprite()
	{
#ifdef SALT_OPENGL
		mSpriteImplementation = std::unique_ptr<SpriteImplementation>{ new OpenGLSprite };
#else
		#only_openGL_is_supported_so_far
#endif
	}
	void Sprite::LoadImage(const std::string& pictureFile)
	{
		mSpriteImplementation->LoadImage(pictureFile);
	}

	int Sprite::GetWidth() const
	{
		return mSpriteImplementation->GetWidth();
	}

	int Sprite::GetHeight() const
	{
		return mSpriteImplementation->GetHeight();
	}
	void Sprite::Bind()
	{
		mSpriteImplementation->Bind();
	}
}

