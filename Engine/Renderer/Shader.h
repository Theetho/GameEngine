#pragma once

namespace Engine
{
	class Shader
	{
	public:
		Shader(const std::string& file_path, const std::string& name, bool use_folder_path);
		virtual ~Shader();

		static Ref<Shader> Create(const std::string& file_path, const std::string& name, bool use_folder_path);

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
		
		virtual const std::string& GetName() const;

		static void SetFolder(const std::string& folder_path);
		virtual void SetName(const std::string& name);
	protected:
		static std::string sFolderPath;
		std::string mName;
		
		virtual void ReadFile(const std::string& file_path) = 0;
	};
}

