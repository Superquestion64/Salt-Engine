#pragma once

#include "pch.h"

namespace Salt
{
	class ShaderImplementation
	{
	public:
		virtual void Load(const std::string& vertexFile, const std::string& fragmentFile) = 0;
		virtual void SetVec2IntUniform(const std::string& unifName, int first, int second) = 0;
		virtual void Use() = 0;
		virtual int GetWindowWidth() const = 0;
		virtual int GetWindowHeight() const = 0;
		virtual ~ShaderImplementation() {};
	};
}