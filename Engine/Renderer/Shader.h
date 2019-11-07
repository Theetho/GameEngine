#pragma once

#include "Maths.h"

namespace Engine
{

/// Abstract base class

	class Shader
	{
	public:
		Shader(
			const std::string& filePath,
			const std::string& name = ""
		);

		virtual ~Shader() 
		{
		}

		virtual void bind() const = 0;

		virtual void unbind() const = 0;

		static Ref<Shader> Create(
			const std::string& filePath,
			const std::string& name = ""
		);

		static void setFolder(
			const std::string& folderPath
		)
		{
			s_folderPath = folderPath;
		}

		inline virtual void setName(
			const std::string& name
		)
		{
			m_name = name;
		}
		
		inline virtual std::string getName() const
		{
			return m_name;
		}
	
	protected:
		virtual void readFile(
			const std::string& filePath
		) = 0;
		static std::string s_folderPath;
		std::string m_name;
	};

/// OpenGL shader

	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(
			const std::string& filePath,
			const std::string& name
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

		// Int
		inline void uploadUniform(
			const std::string& name,
			const int& value
		)
		{
			glUniform1i(
				getLocation(name),
				value
			);
		}

		// Float
		inline void uploadUniform(
			const std::string& name,
			const float& value
		)
		{
			glUniform1f(
				getLocation(name),
				value
			);
		}

		// Vec2
		inline void uploadUniform(
			const std::string& name,
			const Vec2& vector
		)
		{
			glUniform2f(
				getLocation(name),
				vector.x,
				vector.y
			);
		}

		// Vec3
		inline void uploadUniform(
			const std::string& name,
			const Vec3& vector
		)
		{
			glUniform3f(
				getLocation(name),
				vector.x,
				vector.y,
				vector.z
			);
		}

		// Vec4
		inline void uploadUniform(
			const std::string& name,
			const Vec4& vector
		)
		{
			glUniform4f(
				getLocation(name),
				vector.x,
				vector.y,
				vector.z,
				vector.w
			);
		}

		// Mat3
		inline void uploadUniform(
			const std::string& name,
			const Mat3& matrix
		)
		{
			glUniformMatrix3fv(
				getLocation(name),
				1,
				GL_FALSE,
				glm::value_ptr(matrix)
			);
		}

		// Mat4
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
		unsigned int compile(
			const std::string& src,
			const GLenum& shaderType
		);

		void link(
			const std::vector<unsigned int>& ids
		);

	private:
		unsigned int m_id;
		std::unordered_map<GLenum, std::string> m_shaderSources;
		
		void readFile(
			const std::string& filePath
		) override;
		inline int getLocation(const std::string& name) const
		{
			return glGetUniformLocation(m_id, name.c_str());
		}
	};
}

