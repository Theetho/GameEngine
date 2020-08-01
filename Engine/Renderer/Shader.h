#pragma once

namespace Engine
{
	class Shader
	{
	public:
		Shader(const std::string& file_path);
		virtual ~Shader();

		static Ref<Shader> Create(const std::string& file_path);

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
		
		virtual void UploadUniform(const std::string& uniform_name, int value) = 0;
		virtual void UploadUniform(const std::string& uniform_name, int* value, uint count) = 0;
		virtual void UploadUniform(const std::string& uniform_name, float value) = 0;
		virtual void UploadUniform(const std::string& uniform_name, const Vec2& vector) = 0;
		virtual void UploadUniform(const std::string& uniform_name, const Vec3& vector) = 0;
		virtual void UploadUniform(const std::string& uniform_name, const Vec4& vector) = 0;
		virtual void UploadUniform(const std::string& uniform_name, const Mat3& matrix) = 0;
		virtual void UploadUniform(const std::string& uniform_name, const Mat4& matrix) = 0;
	protected:
		virtual std::unordered_map<unsigned int, std::string> ReadFile(const std::string& file_path) = 0;
	};
}

