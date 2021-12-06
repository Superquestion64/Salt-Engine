#pragma once
#include "Sprite.h"
#include "Shader.h"

namespace Salt
{
	class RendererImplementation
	{
	public:
		virtual void Draw(Sprite& sprite,
			int xPos, int yPos, // Bottom left corner
			int width, int height,
			Shader& shader) = 0;
		virtual void ClearFrame() = 0;
		virtual ~RendererImplementation() {};
	};
}