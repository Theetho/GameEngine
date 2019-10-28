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
	 *  you have to call get_int("width"). If you call
	 *  get_int() on a string, like get_int("title"), it
	 *  will not work.
	 */
	 class ConfigFile
	{
	public:
		ConfigFile(
			const std::string& cf
		);
		
		~ConfigFile();

		void parse(
			const std::string& cf
		);

		// Access the value directly through the key
		inline std::string get_str(
			const std::string& field
		) const
		{
			return this->m_fields.at(field);
		}

		inline int get_int(
			const std::string& field
		) const
		{
			return std::atoi(this->m_fields.at(field).c_str());
		}

		inline double get_double(
			const std::string& field
		) const
		{
			return std::atof(this->m_fields.at(field).c_str());
		}

		inline float get_float(
			const std::string& field
		) const
		{
			return static_cast<float>(this->get_double(field));
		}

		inline char get_char(
			const std::string& field
		) const
		{
			return this->m_fields.at(field)[0];
		}

		// Access the value through the index of the key in the original string ("cf") 
		inline std::string get_str(
			const unsigned int& field_index
		) const
		{
			return this->m_fields.at(m_index.at(field_index));
		}

		inline int get_int(
			const unsigned int& field_index
		) const
		{
			return std::atoi(this->m_fields.at(m_index.at(field_index)).c_str());
		}

		inline double get_double(
			const unsigned int& field_index
		) const
		{
			return std::atof(this->m_fields.at(m_index.at(field_index)).c_str());
		}

		inline float get_float(
			const unsigned int& field_index
		) const
		{
			return static_cast<float>(this->get_double(m_index.at(field_index)));
		}

		inline char get_char(
			const unsigned int& field_index
		) const
		{
			return this->m_fields.at(m_index.at(field_index))[0];
		}

	private:
		std::map<std::string, std::string> m_fields;
		std::map<unsigned int, std::string> m_index;
	};
}

