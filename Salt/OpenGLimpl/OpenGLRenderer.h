#pragma once

#include "RendererImplementation.h"
#include "Sprite.h"
#include "Shader.h"

namespace Salt
{
	class OpenGLRenderer : public RendererImplementation
	{
	public:
		OpenGLRenderer();
		virtual void Draw(Sprite& sprite,
			int xPos, int yPos, // Bottom left corner
			int width, int height,
			Shader& shader) override;
		virtual void ClearFrame() override;
	};
}
