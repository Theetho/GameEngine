#pragma once

namespace Engine
{
	class Texture
	{
	public:
		Texture(const std::string& file_path);
		virtual ~Texture();

		inline const std::string& GetPath() const {
			return mPath;
		}

		virtual void Bind(unsigned int slot = 0) const = 0;  
		virtual void Unbind() const = 0;

		virtual void NoFilter() const = 0;
		virtual void BilinearFilter() const = 0;
		virtual void TrilinearFilter() const = 0;
	protected:
		// Used for internal texture, that are not stored in any library
		Texture();
		std::string mPath;
	};
}

