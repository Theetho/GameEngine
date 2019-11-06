#include "EnginePch.h"
#include "Shader.h"
#include "Renderer.h"
#include "Core/Log.h"

namespace Engine
{

/// Abstract base class

	std::string Shader::s_folderPath = "";

	Shader::Shader(
		const std::string& filePath,
		const std::string& name
	)
		: m_name(name)
	{
		// Setting the name of the shader
		if (m_name == "")
		{
			auto lastSlash = filePath.find_last_of("/\\");
			lastSlash = lastSlash == std::string::npos ? 0 : lastSlash + 1;
			auto lastDot = filePath.rfind('.');
			int count = lastDot == std::string::npos ? filePath.size() - lastSlash : lastDot - lastSlash;

			m_name = filePath.substr(lastSlash, count);
		}
	}

	Ref<Shader> Shader::create(
		const std::string& filePath,
		const std::string& name
	)
	{
		ENGINE_ASSERT(s_folderSrc != "", "No folder for the shader files");
		switch (Renderer::getAPI())
		{
		case Engine::API::None:
			ENGINE_ASSERT(false, "Api not supported");
		case Engine::API::OpenGL:
			return std::make_shared<OpenGLShader>(filePath, name);
		}

		return nullptr;
	}

/// OpenGL shader

	OpenGLShader::OpenGLShader(
		const std::string& filePath,
		const std::string& name
	)
		: Shader(filePath, name)
		, m_id(0)
	{
		// Retrieve the source code of every shaders
		readFile(s_folderPath + filePath);
		
		std::vector<unsigned int> ids;

		// Then compile the shaders
		for (auto pair : m_shaderSources)
		{
			ids.push_back(compile(pair.second, pair.first));
		}
		
		/// From https://www.khronos.org/opengl/wiki/Shader_Compilation

		m_id = glCreateProgram();

		// Attach the shaders to our program
		for (auto id : ids)
		{
			glAttachShader(m_id, id);
		}

		link(ids);

		// Always detach shaders after a successful link.
		for (auto id : ids)
		{
			glDeleteShader(id);
		}
	}

	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(m_id);
	}
	unsigned int OpenGLShader::compile(
		const std::string& src,
		const GLenum& shaderType
	)
	{
		// Create an empty vertexSrc shader handle
		unsigned int shader = glCreateShader(shaderType);

		// Send the vertexSrc shader source code to GL
		// Note that std::string's .c_str is NULL character terminated.
		const char* source = (const char*)src.c_str();
		glShaderSource(shader, 1, &source, 0);

		// Compile the vertexSrc shader
		glCompileShader(shader);

		int isCompiled = 0;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			int maxLength = 0;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<char> infoLog(maxLength);
			glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

			// We don't need the shader anymore.
			glDeleteShader(shader);

			// Use the infoLog as you see fit.
			ENGINE_LOG_ERROR("Shader : {0}", infoLog.data());
			ENGINE_ASSERT(false, "Shader compilation failure");

			// In this simple program, we'll just leave
			return 0;
		}
		
		return shader;
	}

	void OpenGLShader::link(
		const std::vector<unsigned int>& ids
	)
	{
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
			for (auto id : ids)
			{
				glDeleteShader(id);
			}

			// Use the infoLog as you see fit.
			ENGINE_LOG_ERROR("{0}", infoLog.data());
			ENGINE_ASSERT(false, "Shader link failure");

			// In this simple program, we'll just leave
			return;
		}
	}

	void OpenGLShader::readFile(
		const std::string& filePath
	)
	{
		GLenum type = 0;
		std::string source = "";
		std::ifstream file(filePath.c_str(), std::ios::in, std::ios::binary );

		
		if (file.is_open())
		{
			std::string line;
			while (std::getline(file, line))
			{
				// When the shader type changes, the previous
				// one is pushed in the shader source code map
				if (line == "#type vertex")
				{
					if (type && source != "")
					{
						m_shaderSources[type] = source;
						source = "";
					}
					type = GL_VERTEX_SHADER;
				}
				else if (line == "#type fragment")
				{
					if (type && source != "")
					{
						m_shaderSources[type] = source;
						source = "";
					}
					type = GL_FRAGMENT_SHADER;
				}
				else
				{
					source += line + '\n';
				}
			}
			// Push the last shader source code
			if (type && source != "")
			{
				m_shaderSources[type] = source;
			}
			
			file.close();
		}
		else
		{
			ENGINE_LOG_ERROR("Can't open the file : {0}", filePath);
			ENGINE_ASSERT(file, "Can't find the shader file");
		}
	}
}