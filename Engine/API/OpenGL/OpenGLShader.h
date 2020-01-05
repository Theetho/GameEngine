#pragma once

#include "Renderer/Shader.h"

namespace Engine
{
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& file_path, const std::string& name, bool use_folder_path);
		~OpenGLShader();

		void Bind() const;
		void Unbind() const;
		
		void UploadUniform(const std::string& name, int value);
		void UploadUniform(const std::string& name, float value);
		void UploadUniform(const std::string& name, const Vec2& vector);
		void UploadUniform(const std::string& name, const Vec3& vector);
		void UploadUniform(const std::string& name, const Vec4& vector);
		void UploadUniform(const std::string& name, const Mat3& matrix);
		void UploadUniform(const std::string& name, const Mat4& matrix);
	private:
		unsigned int mId;
		std::unordered_map<GLenum, std::string> mShaderSources;

		int			 GetLocation(const std::string& name) const;
		void		 Link(const std::vector<unsigned int>& ids);
		void		 ReadFile(const std::string& file_path) override;
		unsigned int Compile(const std::string& source_file, GLenum shader_type);
	};
}

