#pragma once
#include "pch.h"
#include "Events.h"

namespace Salt
{
	class WindowImplementation
	{
	public:
		virtual void Init() = 0;
		virtual void CreateWindow(int width, int height, const std::string& name) = 0;
		virtual void SwapBuffers() = 0;
		virtual void PollEvents() = 0;
		virtual int GetWindowWidth() const = 0;
		virtual int GetWindowHeight() const = 0;
		virtual ~WindowImplementation() {};
		virtual void SetKeyPressedCallback(std::function<void(KeyPressedEvent&)> func) = 0;
	};
}