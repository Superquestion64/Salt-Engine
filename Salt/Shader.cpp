// Implements the shader class, by default will use OpenGL

#include "pch.h"
#include "Shader.h"
#include "OpenGLimpl/OpenGLShader.h"

namespace Salt
{
	// Default constructor sets mShader to an OpenGL shader
	Shader::Shader()
	{
#ifdef SALT_OPENGL
		mShader = std::unique_ptr<ShaderImplementation>{ new OpenGLShader };
#else
		#only_OpenGL_is_implemented_at_the_moment
#endif
	}
	// Will load the given vertex and fragment files provided as parameters
	void Shader::Load(const std::string& vertexFile, const std::string& fragmentFile)
	{
		mShader->Load(vertexFile, fragmentFile);
	}
	// Creates the game screen when given the width and height
	void Shader::SetVec2IntUniform(const std::string& unifName, int width, int height)
	{
		mShader->SetVec2IntUniform(unifName, width, height);
	}
	// Calls the use function of the implementation class
	void Shader::Use()
	{
		mShader->Use();
	}
	// Returns the width of the window
	int Shader::GetWindowWidth() const
	{
		return mShader->GetWindowWidth();
	}
	// Returns the height of the window
	int Shader::GetWindowHeight() const
	{
		return mShader->GetWindowHeight();
	}
}
