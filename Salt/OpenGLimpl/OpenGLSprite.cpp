#include "pch.h"
#include "OpenGLSprite.h"

#include "GLFW/glfw3.h"
#include "stb_image.h"

namespace Salt
{
	OpenGLSprite::OpenGLSprite()
	{
	}
	OpenGLSprite::OpenGLSprite(const std::string& pictureFile)
	{
		LoadImage(pictureFile);
	}
	OpenGLSprite::~OpenGLSprite()
	{
		if (mTexture != 0)
			glDeleteTextures(1, &mTexture);
	}
	// Loads new sprite textures while deleting previous ones
	void OpenGLSprite::LoadImage(const std::string& pictureFile)
	{
		if (mTexture != 0)
			glDeleteTextures(1, &mTexture);
		unsigned char* image{ nullptr };
		int numChannels{ 0 };
		stbi_set_flip_vertically_on_load(true);
		image = stbi_load(pictureFile.c_str(), &mWidth, &mHeight, &numChannels, 0);
		assert(image != nullptr);
		// Texture
		glGenTextures(1, &mTexture);
		glBindTexture(GL_TEXTURE_2D, mTexture);
		// set the texture wrapping parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		// set texture filtering parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		// load image, create texture and generate mipmaps
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, mWidth, mHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
		
		glGenerateMipmap(GL_TEXTURE_2D);

		stbi_image_free(image);
	}
	int OpenGLSprite::GetWidth() const
	{
		return mWidth;
	}
	int OpenGLSprite::GetHeight() const
	{
		return mHeight;
	}
	void OpenGLSprite::Bind()
	{
		glBindTexture(GL_TEXTURE_2D, mTexture);
	}
	void OpenGLSprite::DeleteTexture()
	{
		if (mTexture != 0)
			glDeleteTextures(1, &mTexture);
	}
}