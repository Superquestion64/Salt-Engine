#pragma once
#include "RendererImplementation.h"
#include "Shader.h"
#include "Sprite.h"
#include "pch.h"
#include "SaltUtils.h"

namespace Salt
{
	class SALT_API Renderer
	{
	public:
		static void Init();
		static void Draw(Sprite& sprite, 
			int xPos, int yPos, // Bottom left corner
			int width, int height, 
			Shader& shader);
		static void ClearFrame();
		static void ShutDown();
	private:
		Renderer();
		inline static Renderer* mInstance{ nullptr };
		inline static std::unique_ptr<RendererImplementation> mImplementation;
	};

}


