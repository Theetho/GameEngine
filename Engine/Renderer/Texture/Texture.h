#pragma once

namespace Engine
{
	class Texture
	{
	public:
		Texture(const std::string& file_path, const std::string& name = "", bool use_folder_path = true);
		virtual ~Texture();

		virtual void Bind(unsigned int slot = 0) const = 0;  
		virtual void Unbind() const = 0;
	
		virtual const std::string& GetName() const;
	
		static void  SetFolder(const std::string& folder);
		virtual void SetName(const std::string& name);
	protected:
		static std::string sFolder;
		std::string mName;
	};
}

