#pragma once

/* Format:
 *		For example to describe a window :
 *
 *		width: 1280\n
 *		height: 720\n
 *		title: GameEngine\n
 *		...
 *		attribute: value\n
 *
 */

namespace Engine
{

	/* 
	 *  The value for each field is stored as a string.
	 *  To retrieve the correct data type, the user has 
	 *  to know it in advance and call the method GetValueAt
	 *  with the right template parameter.
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
	private:
		std::map<std::string, std::string> mFields;
		std::map<unsigned int, std::string> mIndex;
	};
}

