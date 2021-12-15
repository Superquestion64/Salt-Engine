#pragma once

#include "ShaderImplementation.h"

namespace Salt
{
	class OpenGLShader : public ShaderImplementation
	{
	public:
		virtual void Load(const std::string& vertexFile, const std::string& fragmentFile) override;
		virtual void SetVec2IntUniform(const std::string& unifName, int width, int height) override;
		virtual int GetWindowWidth() const override;
		virtual int GetWindowHeight() const override;
		virtual void Use() override;

	private:
		unsigned int mShaderProgram{ 0 };
		int mWidth{ 0 };
		int mHeight{ 0 };
	};
}