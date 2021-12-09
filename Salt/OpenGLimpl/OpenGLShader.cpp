#include "pch.h"
#include "OpenGLShader.h"
#include "glad/glad.h"


namespace Salt
{
	void OpenGLShader::Load(const std::string& vertexFile, const std::string& fragmentFile)
	{
		// Convert vertex file to c string
		std::ifstream vertexFileStream{ vertexFile };
		if (!vertexFileStream.is_open())
			std::cout << "ERROR: failed to open vertex shader file!" << std::endl;
		std::stringstream vertexStringStream;
		vertexStringStream << vertexFileStream.rdbuf();
		std::string vertexCode{ vertexStringStream.str() };
		const char* cVertexCode{ vertexCode.c_str() };
		vertexFileStream.close();
		// Vertex shader
		unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &cVertexCode, NULL);
		glCompileShader(vertexShader);
		// Check for shader compile errors
		int success;
		char infoLog[512];
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		}

		// Convert fragment file to c string
		std::ifstream fragmentFileStream{ fragmentFile };
		if (!fragmentFileStream.is_open())
			std::cout << "ERROR: failed to open vertex shader file!" << std::endl;
		std::stringstream fragmentStringStream;
		fragmentStringStream << fragmentFileStream.rdbuf();
		std::string fragmentCode{ fragmentStringStream.str() };
		const char* cFragmentCode{ fragmentCode.c_str() };
		fragmentFileStream.close();
		// Fragment shader
		unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &cFragmentCode, NULL);
		glCompileShader(fragmentShader);
		// Check for shader compile errors
		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
		}
		if (mShaderProgram != 0)
			glDeleteProgram(mShaderProgram);
		// Link shaders
		mShaderProgram = glCreateProgram();
		glAttachShader(mShaderProgram, vertexShader);
		glAttachShader(mShaderProgram, fragmentShader);
		glLinkProgram(mShaderProgram);
		// Check for linking errors
		glGetProgramiv(mShaderProgram, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(mShaderProgram, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
		}
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

	}
	void OpenGLShader::SetVec2IntUniform(const std::string& unifName, int first, int second)
	{
		assert(mShaderProgram);

		glUseProgram(mShaderProgram);
		int location{ glGetUniformLocation(mShaderProgram, unifName.c_str()) };
		glUniform2i(location, first, second);
	}
	void OpenGLShader::Use()
	{
		glUseProgram(mShaderProgram);
	}
}