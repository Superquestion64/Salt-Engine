#pragma once

// Implements the shader class, by default will use OpenGL

#include "pch.h"
#include "SaltUtils.h"
#include "ShaderImplementation.h"

namespace Salt 
{
	class SALT_API Shader
	{
	public:
		// Default constructor sets mShader to an OpenGL shader
		Shader();
		// Will load the given vertex and fragment files provided as parameters
		void Load(const std::string& vertexFile, const std::string& fragmentFile);
		// Creates the game screen when given the width and height
		void SetVec2IntUniform(const std::string& unifName, int width, int height);
		// Calls the use function of the implementation class
		void Use();
		// Returns the width of the window
		int GetWindowWidth() const;
		// Returns the height of the window
		int GetWindowHeight() const;

	private:
		// Any ShaderImplementation class is valid for implementing mShader
		std::unique_ptr<ShaderImplementation> mShader;
	};
}


