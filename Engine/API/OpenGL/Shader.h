#pragma once

#include "Renderer/Shader.h"

namespace Engine
{
	namespace OpenGL
	{
		class Shader : public Engine::Shader
		{
		public:
			Shader(const std::string& file_path);
			virtual ~Shader();

			void Bind() const;
			void Unbind() const;

			void UploadUniform(const std::string& uniform_name, int value) override;
			void UploadUniform(const std::string& uniform_name, float value) override;
			void UploadUniform(const std::string& uniform_name, int* value, uint count) override;
			void UploadUniform(const std::string& uniform_name, const Vec2& vector) override;
			void UploadUniform(const std::string& uniform_name, const Vec3& vector) override;
			void UploadUniform(const std::string& uniform_name, const Vec4& vector) override;
			void UploadUniform(const std::string& uniform_name, const Mat3& matrix) override;
			void UploadUniform(const std::string& uniform_name, const Mat4& matrix) override;
		protected:
			unsigned int mId;
			std::unordered_map<std::string, int> mUniformLocations;

			int	 GetUniformLocation(const std::string& name);
			void RetrieveAllUniformLocation();
			void AddUniformLocation(const std::string& name);
			void Link(const std::vector<unsigned int>& ids);
			uint Compile(const std::string& source_file, GLenum shader_type);
			
			std::unordered_map<GLenum, std::string> ReadFile(const std::string& file_path) override;
		};
	}
}

