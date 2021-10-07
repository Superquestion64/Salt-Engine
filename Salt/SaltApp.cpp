#include "pch.h"

#include "SaltApp.h"

#include "GLFW/glfw3.h"

namespace Salt
{
	// This will run the game
	void SaltApp::Run()
	{
		std::cout << "Salt running..." << std::endl;

		GLFWwindow* window;
		glfwInit();
		window = glfwCreateWindow(800, 600, "Test", NULL, NULL);

		while (true)
		{
			OnUpdate();

			glfwSwapBuffers(window);
			glfwPollEvents();
		}
	}
	void SaltApp::OnUpdate()
	{}

	SaltApp::SaltApp()
	{}

};
