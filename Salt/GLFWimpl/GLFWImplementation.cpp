#include "pch.h"
#include "GLFWImplementation.h"

namespace Salt
{
	void GlfwImplementation::Init()
	{
		if (glfwInit() == GL_FALSE)
		{
			std::cout << "ERROR: GLFW failed to init" << std::endl;
		}
	}
	void GlfwImplementation::CreateWindow(int width, int height, const std::string& name)
	{
		mWindow = glfwCreateWindow(width, height, name.c_str(), NULL, NULL);
		glfwMakeContextCurrent(mWindow);
	}
	void GlfwImplementation::SwapBuffers()
	{
		glfwSwapBuffers(mWindow);
	}
	void GlfwImplementation::PollEvents()
	{
		glfwPollEvents();
	}
	int GlfwImplementation::GetWindowWidth() const
	{
		int width{ 0 };
		int height{ 0 };
		glfwGetWindowSize(mWindow, &width, &height);
		return width;
	}
	int GlfwImplementation::GetWindowHeight() const
	{
		int width{ 0 };
		int height{ 0 };
		glfwGetWindowSize(mWindow, &width, &height);
		return height;
	}
}