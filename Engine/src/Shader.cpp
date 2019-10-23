#include "EnginePch.h"
#include "Shader.h"
#include "Log.h"

namespace Engine
{
	Shader* Shader::create(const std::string& vertex, const std::string& fragment)
	{
#ifdef ENGINE_WINDOWS
		return new OpenGLShader(vertex, fragment);
#endif // ENGINE_WINDOWS
	}

/// OpenGL shader

	OpenGLShader::OpenGLShader(const std::string& vertex, const std::string& fragment)
		: m_id(0)
	{
		/// From https://www.khronos.org/opengl/wiki/Shader_Compilation

			// Create an empty vertex shader handle
		unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);

		// Send the vertex shader source code to GL
		// Note that std::string's .c_str is NULL character terminated.
		const char* source = (const char*)vertex.c_str();
		glShaderSource(vertexShader, 1, &source, 0);

		// Compile the vertex shader
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
			ENGINE_LOG_ERROR("{0}", infoLog.data());
			ENGINE_ASSERT(false, "Vertex shader compilation failure");

			// In this simple program, we'll just leave
			return;
		}

		// Create an empty fragment shader handle
		unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

		// Send the fragment shader source code to GL
		// Note that std::string's .c_str is NULL character terminated.
		source = (const char*)fragment.c_str();
		glShaderSource(fragmentShader, 1, &source, 0);

		// Compile the fragment shader
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
			ENGINE_LOG_ERROR("{0}", infoLog.data());
			ENGINE_ASSERT(false, "Fragment shader compilation failure");

			// In this simple program, we'll just leave
			return;
		}

		// Vertex and fragment shaders are successfully compiled.
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
	void OpenGLShader::bind() const
	{
		glUseProgram(m_id);
	}
	void OpenGLShader::unbind() const
	{
		glUseProgram(0);
	}
}