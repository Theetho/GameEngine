#include "EnginePch.h"
#include "Shader.h"
#include "Renderer.h"
#include "Core/Log.h"

namespace Engine
{

/// Abstract base class

	std::string Shader::s_folderPath = "";

	Shader* Shader::create(
		const std::string& vertexSrc,
		const std::string& fragmentSrc
	)
	{
		ENGINE_ASSERT(s_folderSrc != "", "No folder was given");
		switch (Renderer::getAPI())
		{
		case Engine::API::None:
			ENGINE_ASSERT(false, "Api not supported");
		case Engine::API::OpenGL:
			return new OpenGLShader(vertexSrc, fragmentSrc);
		}

		return nullptr;
	}

	std::string Shader::getSrc(const std::string& filePath)
	{
		std::string result;
		std::ifstream file(filePath.c_str());
		
		if (file.is_open())
		{
			std::string line;
			while (std::getline(file, line))
			{
				result += line + '\n';
			}
			file.close();
		}
		else
		{
			ENGINE_LOG_ERROR("Can't open the file : {0}", filePath.c_str());
		}

		return result;
	}

/// OpenGL shader

	OpenGLShader::OpenGLShader(
		const std::string& vertexPath, 
		const std::string& fragmentPath
	)
		: m_id(0)
	{
		/// From https://www.khronos.org/opengl/wiki/Shader_Compilation

		// Create an empty vertexSrc shader handle
		unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);

		std::string vertexSrc = getSrc(s_folderPath + vertexPath);

		// Send the vertexSrc shader source code to GL
		// Note that std::string's .c_str is NULL character terminated.
		const char* source = (const char*)vertexSrc.c_str();
		glShaderSource(vertexShader, 1, &source, 0);

		// Compile the vertexSrc shader
		glCompileShader(vertexShader);

		int isCompiled = 0;
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			int maxLength = 0;
			glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<char> infoLog(maxLength);
			glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);

			// We don't need the shader anymore.
			glDeleteShader(vertexShader);

			// Use the infoLog as you see fit.
			ENGINE_LOG_ERROR("Vertex : {0}", infoLog.data());
			ENGINE_ASSERT(false, "vertexSrc shader compilation failure");

			// In this simple program, we'll just leave
			return;
		}

		// Create an empty fragmentSrc shader handle
		unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

		std::string fragmentSrc = getSrc(s_folderPath + fragmentPath);

		// Send the fragmentSrc shader source code to GL
		// Note that std::string's .c_str is NULL character terminated.
		source = (const char*)fragmentSrc.c_str();
		glShaderSource(fragmentShader, 1, &source, 0);

		// Compile the fragmentSrc shader
		glCompileShader(fragmentShader);

		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			int maxLength = 0;
			glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<char> infoLog(maxLength);
			glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);

			// We don't need the shader anymore.
			glDeleteShader(fragmentShader);
			// Either of them. Don't leak shaders.
			glDeleteShader(vertexShader);

			// Use the infoLog as you see fit.
			ENGINE_LOG_ERROR("Fragment : {0}", infoLog.data());
			ENGINE_ASSERT(false, "fragmentSrc shader compilation failure");

			// In this simple program, we'll just leave
			return;
		}

		// vertexSrc and fragmentSrc shaders are successfully compiled.
		// Now time to link them together into a program.
		// Get a program object.
		m_id = glCreateProgram();

		// Attach our shaders to our program
		glAttachShader(m_id, vertexShader);
		glAttachShader(m_id, fragmentShader);

		// Link our program
		glLinkProgram(m_id);

		// Note the different functions here: glGetProgram* instead of glGetShader*.
		int isLinked = 0;
		glGetProgramiv(m_id, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			int maxLength = 0;
			glGetProgramiv(m_id, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<char> infoLog(maxLength);
			glGetProgramInfoLog(m_id, maxLength, &maxLength, &infoLog[0]);

			// We don't need the program anymore.
			glDeleteProgram(m_id);
			// Don't leak shaders either.
			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);

			// Use the infoLog as you see fit.
			ENGINE_LOG_ERROR("{0}", infoLog.data());
			ENGINE_ASSERT(false, "Shader link failure");

			// In this simple program, we'll just leave
			return;
		}
		// Always detach shaders after a successful link.
		glDetachShader(m_id, vertexShader);
		glDetachShader(m_id, fragmentShader);
	}

	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(m_id);
	}
}