#pragma once

#include "Include/Maths.h"
#include "Renderer/Shader.h"

namespace Engine
{
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& file_path, const std::string& name, bool use_folder_path);
		~OpenGLShader();

		void Bind() const
		{
			glUseProgram(mId);
		}
		void Unbind() const
		{
			glUseProgram(0);
		}
		
		void UploadUniform(const std::string& name, int value)
		{
			glUniform1i(
				GetLocation(name),
				value
			);
		}
		void UploadUniform(const std::string& name, float value)
		{
			glUniform1f(
				GetLocation(name),
				value
			);
		}
		void UploadUniform(const std::string& name, const Vec2& vector)
		{
			glUniform2f(
				GetLocation(name),
				vector.x,
				vector.y
			);
		}
		void UploadUniform(const std::string& name, const Vec3& vector)
		{
			glUniform3f(
				GetLocation(name),
				vector.x,
				vector.y,
				vector.z
			);
		}
		void UploadUniform(const std::string& name, const Vec4& vector)
		{
			glUniform4f(
				GetLocation(name),
				vector.x,
				vector.y,
				vector.z,
				vector.w
			);
		}
		void UploadUniform(const std::string& name, const Mat3& matrix)
		{
			glUniformMatrix3fv(
				GetLocation(name),
				1,
				GL_FALSE,
				glm::value_ptr(matrix)
			);
		}
		void UploadUniform(const std::string& name, const Mat4& matrix)
		{
			glUniformMatrix4fv(
				GetLocation(name),
				1,
				GL_FALSE,
				glm::value_ptr(matrix)
			);
		}
	private:
		unsigned int mId;
		std::unordered_map<GLenum, std::string> mShaderSources;

		int			 GetLocation(const std::string& name) const
		{
			return glGetUniformLocation(mId, name.c_str());
		}
		void		 Link(const std::vector<unsigned int>& ids);
		void		 ReadFile(const std::string& file_path) override;
		unsigned int Compile(const std::string& source_file, GLenum shader_type);
	};
}

