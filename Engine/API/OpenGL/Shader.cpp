#include "EnginePch.h"
#include "Shader.h"

namespace Engine
{
	namespace OpenGL
	{
		Shader::Shader(const std::string& file_path, const std::string& name, bool use_folder_path)
			: Engine::Shader(file_path, name, use_folder_path)
			, mId(0)
		{
			// Retrieve the source code of every shaders
			auto shader_sources = use_folder_path ? ReadFile(sFolderPath + file_path) : ReadFile(file_path);

			std::vector<unsigned int> ids;

			// Then compile the shaders
			for (auto pair : shader_sources)
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

			// Fetch all the uniform location from the GPU 
			RetrieveAllUniformLocation();
		}

		Shader::~Shader()
		{
			glDeleteProgram(mId);
		}

		void Shader::Bind() const
		{
			glUseProgram(mId);
		}

		void Shader::Unbind() const
		{
			glUseProgram(0);
		}

		void Shader::UploadUniform(const std::string& uniform_name, int value)
		{
			glUniform1i(GetUniformLocation(uniform_name.c_str()), value);
		}

		void Shader::UploadUniform(const std::string& uniform_name, float value)
		{
			glUniform1f(GetUniformLocation(uniform_name.c_str()), value);
		}

		void Shader::UploadUniform(const std::string& uniform_name, const Vec2& vector)
		{
			glUniform2f(GetUniformLocation(uniform_name.c_str()), vector.x, vector.y);
		}

		void Shader::UploadUniform(const std::string& uniform_name, const Vec3& vector)
		{
			glUniform3f(GetUniformLocation(uniform_name.c_str()), vector.x, vector.y, vector.z);
		}

		void Shader::UploadUniform(const std::string& uniform_name, const Vec4& vector)
		{
			glUniform4f(GetUniformLocation(uniform_name.c_str()), vector.x, vector.y, vector.z, vector.w);
		}

		void Shader::UploadUniform(const std::string& uniform_name, const Mat3& matrix)
		{
			glUniformMatrix3fv(GetUniformLocation(uniform_name.c_str()), 1, GL_FALSE, glm::value_ptr(matrix));
		}

		void Shader::UploadUniform(const std::string& uniform_name, const Mat4& matrix)
		{
			glUniformMatrix4fv(GetUniformLocation(uniform_name.c_str()), 1, GL_FALSE, glm::value_ptr(matrix));
		}

		unsigned int Shader::Compile(const std::string& source_file, GLenum shader_type)
		{
			// Create an empty shader handle
			unsigned int shader = glCreateShader(shader_type);

			// Send the shader source code to GL
			const char* source = source_file.c_str();
			glShaderSource(shader, 1, &source, 0);

			// Compile the shader
			glCompileShader(shader);

			int is_compiled = 0;
			glGetShaderiv(shader, GL_COMPILE_STATUS, &is_compiled);
			if (is_compiled == GL_FALSE)
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

		void Shader::RetrieveAllUniformLocation()
		{
			for (auto uniform : mUniformLocations)
			{
				mUniformLocations[uniform.first] = glGetUniformLocation(mId, uniform.first.c_str());
			}
		}

		void Shader::AddUniformLocation(const std::string& uniform_name)
		{
			mUniformLocations[uniform_name.c_str()] = -1;
		}

		int Shader::GetUniformLocation(const std::string& name)
		{
			if (!mUniformLocations.count(name))
			{
				mUniformLocations[name] = glGetUniformLocation(mId, name.c_str());
			}
			return mUniformLocations.at(name);
		}

		void Shader::Link(const std::vector<unsigned int>& ids)
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

		std::unordered_map<GLenum, std::string> Shader::ReadFile(const std::string& file_path)
		{
			std::unordered_map<GLenum, std::string> shader_sources;
			GLenum type = 0;
			std::string source = "";
			std::ifstream file(file_path.c_str(), std::ios::in, std::ios::binary);


			if (file.is_open())
			{
				std::string line;
				while (std::getline(file, line))
				{
					// When the shader type changes, the previous
					// one is pushed in the shader source code map
					auto comment = line.find("//");
					if (comment != std::string::npos)
					{
						line = line.erase(comment, line.size());
					}

					if (!line.size())
						continue;

					if (line == "#type vertex")
					{
						if (type && source != "")
						{
							shader_sources[type] = source;
							source = "";
						}
						type = GL_VERTEX_SHADER;
					}
					else if (line == "#type fragment")
					{
						if (type && source != "")
						{
							shader_sources[type] = source;
							source = "";
						}
						type = GL_FRAGMENT_SHADER;
					}
					else if (line == "#type geometry")
					{
						if (type && source != "")
						{
							shader_sources[type] = source;
							source = "";
						}
						type = GL_GEOMETRY_SHADER;
					}
					else if (line == "#type tesselation control")
					{
						if (type && source != "")
						{
							shader_sources[type] = source;
							source = "";
						}
						type = GL_TESS_CONTROL_SHADER;
					}
					else if (line == "#type tesselation evalution")
					{
						if (type && source != "")
						{
							shader_sources[type] = source;
							source = "";
						}
						type = GL_TESS_EVALUATION_SHADER;
					}
					else
					{
						source += line + '\n';
						if (line.find("uniform") != std::string::npos)
						{
							// e.g : "uniform float uValue;" gives "uValue;"
							auto uniform_name = line.substr(line.find_last_of(' ') + 1);
							
							// Skip uniform arrays
							auto square_bracket = uniform_name.find_first_of('[');
							if (square_bracket != std::string::npos)
								continue;
							
							// Remove ';' at the end
							uniform_name = uniform_name.erase(uniform_name.size() - 1);
							// Add it to the locations
							AddUniformLocation(uniform_name);
						}
					}
				}
				// Push the last shader source code
				if (type && source != "")
				{
					shader_sources[type] = source;
				}

				file.close();
				return shader_sources;
			}
			else
			{
				ENGINE_LOG_ERROR("Can't open the file : {0}", file_path);
				ENGINE_ASSERT(file, "Can't find the shader file");
			}
		}
	}
}