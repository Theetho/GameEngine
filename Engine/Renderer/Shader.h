#pragma once

#include "Maths.h"

namespace Engine
{

/// Abstract base class

	class Shader
	{
	public:
		virtual ~Shader() 
		{
		}

		virtual void bind() const = 0;

		virtual void unbind() const = 0;

		static Shader* create(
			const std::string& vertexPath,
			const std::string& fragmentPath
		);

		static void setFolder(
			const std::string& folderPath
		)
		{
			s_folderPath = folderPath;
		}
	protected:
		std::string getSrc(
			const std::string& filePath
		);
		static std::string s_folderPath;
	};

/// OpenGL shader

	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(
			const std::string& vertexPath,
			const std::string& fragmentPath
		);
		
		~OpenGLShader();

		inline void bind() const
		{
			glUseProgram(m_id);
		}
		
		inline void unbind() const
		{
			glUseProgram(0);
		}

		inline void uploadUniform(
			const std::string& name,
			const Mat4& matrix
		)
		{
			glUniformMatrix4fv(
				getLocation(name),
				1,
				GL_FALSE,
				glm::value_ptr(matrix)
			);
		}

	private:
		unsigned int m_id;

		inline int getLocation(const std::string& name) const
		{
			return glGetUniformLocation(m_id, name.c_str());
		}
	};
}

