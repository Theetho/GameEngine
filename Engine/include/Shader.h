#pragma once

namespace Engine
{
	class Shader
	{
	public:
		virtual void bind() const = 0;
		virtual void unbind() const = 0;

		static Shader* create(const std::string& vertex, const std::string& fragment);
	};

	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& vertex, const std::string& fragment);
		~OpenGLShader();

		void bind() const;
		void unbind() const;
	private:
		unsigned int m_id;
	};
}

