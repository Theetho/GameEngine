#include "EnginePch.h"
#include "OpenGLShader.h"
#include "Core/Log.h"

namespace Engine
{
	OpenGLShader::OpenGLShader(const std::string& file_path, const std::string& name, bool use_folder_path)
		: Shader(file_path, name, use_folder_path)
		, mId(0)
	{
		// Retrieve the source code of every shaders
		use_folder_path ? ReadFile(sFolderPath + file_path) : ReadFile(file_path);

		std::vector<unsigned int> ids;

		// Then compile the shaders
		for (auto pair : mShaderSources)
		{
			ids.push_back(Compile(pair.second, pair.first));
		}
		
		/// From https://www.khronos.org/opengl/wiki/Shader_Compilation

		mId = glCreateProgram();

		// Attach the shaders to our program
		for (auto id : ids)
		{
			glAttachShader(mId, id);
		}

		Link(ids);

		// Always detach shaders after a successful link.
		for (auto id : ids)
		{
			glDeleteShader(id);
		}
	}

	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(mId);
	}

	unsigned int OpenGLShader::Compile(const std::string& source_file, GLenum shader_type)
	{
		// Create an empty vertexSrc shader handle
		unsigned int shader = glCreateShader(shader_type);

		// Send the vertexSrc shader source code to GL
		// Note that std::string's .c_str is NULL character terminated.
		const char* source = (const char*)source_file.c_str();
		glShaderSource(shader, 1, &source, 0);

		// Compile the vertexSrc shader
		glCompileShader(shader);

		int isCompiled = 0;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			int max_length = 0;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &max_length);

			// The max_length includes the NULL character
			std::vector<char> info_log(max_length);
			glGetShaderInfoLog(shader, max_length, &max_length, &info_log[0]);

			// We don't need the shader anymore.
			glDeleteShader(shader);

			// Use the info_log as you see fit.
			ENGINE_LOG_ERROR("Shader : {0}", info_log.data());
			ENGINE_ASSERT(false, "Shader compilation failure");

			// In this simple program, we'll just leave
			return 0;
		}
		
		return shader;
	}

	void OpenGLShader::Link(
		const std::vector<unsigned int>& ids
	)
	{
		// Link our program
		glLinkProgram(mId);
		
		// Note the different functions here: glGetProgram* instead of glGetShader*.
		int is_linked = 0;
		glGetProgramiv(mId, GL_LINK_STATUS, (int*)&is_linked);
		if (is_linked == GL_FALSE)
		{
			int max_length = 0;
			glGetProgramiv(mId, GL_INFO_LOG_LENGTH, &max_length);

			// The max_length includes the NULL character
			std::vector<char> info_log(max_length);
			glGetProgramInfoLog(mId, max_length, &max_length, &info_log[0]);

			// We don't need the program anymore.
			glDeleteProgram(mId);
			// Don't leak shaders either.
			for (auto id : ids)
			{
				glDeleteShader(id);
			}

			// Use the info_log as you see fit.
			ENGINE_LOG_ERROR("{0}", info_log.data());
			ENGINE_ASSERT(false, "Shader link failure");

			// In this simple program, we'll just leave
			return;
		}
	}

	void OpenGLShader::ReadFile(
		const std::string& file_path
	)
	{
		GLenum type = 0;
		std::string source = "";
		std::ifstream file(file_path.c_str(), std::ios::in, std::ios::binary );

		
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
						mShaderSources[type] = source;
						source = "";
					}
					type = GL_VERTEX_SHADER;
				}
				else if (line == "#type fragment")
				{
					if (type && source != "")
					{
						mShaderSources[type] = source;
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
				mShaderSources[type] = source;
			}
			
			file.close();
		}
		else
		{
			ENGINE_LOG_ERROR("Can't open the file : {0}", file_path);
			ENGINE_ASSERT(file, "Can't find the shader file");
		}
	}
}