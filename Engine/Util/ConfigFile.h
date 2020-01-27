#pragma once

/* Format:
 *		For example to describe a window :
 *
 *		width: 1280\n
 *		height: 720\n
 *		title: GameEngine\n
 *		...
 *		attibute: value\n
 *
 */

namespace Engine
{

	/* 
	 *  The value for each field is store as a string.
	 *  To retrieve the correct data type, the user has 
	 *  to know the real type of data.
	 *  For example, to retrieve the width of the window,
	 *  you have to call GetInt("width"). If you call
	 *  GetInt() on a string, like GetInt("title"), it
	 *  will not work.
	 */
	 class ConfigFile
	{
	public:
		ConfigFile(const std::string& config_file);
		~ConfigFile();

		void Parse(const std::string& config_file);
		template<class T>
		T GetValueAt(const std::string& field)
		{
			std::istringstream caster(mFields.at(field));
			T result;

			caster >> result;
			
			return result;
		}
		template<class T>
		T GetValueAt(unsigned int index)
		{
			std::istringstream caster(mIndex.at(index));
			T result;

			caster >> result;

			return result;
		}
		// Access the value directly through the key
		int			GetInt(const std::string& field) const;
		char		GetChar(const std::string& field) const;
		float		GetFloat(const std::string& field) const;
		double		GetDouble(const std::string& field) const;
		std::string GetString(const std::string& field) const;
		// Access the value through the index of the key in the original string ("config_file") 
		int			GetInt(unsigned int field_index) const;
		char		GetChar(unsigned int field_index) const;
		float		GetFloat(unsigned int field_index) const;
		double		GetDouble(unsigned int field_index) const;
		std::string GetString(unsigned int field_index) const;
	private:
		std::map<std::string, std::string> mFields;
		std::map<unsigned int, std::string> mIndex;
	};
}

