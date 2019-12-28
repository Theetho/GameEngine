#include "EnginePch.h"
#include "ConfigFile.h"

namespace Engine
{
	enum class PARSING 
	{
		KEY,
		VALUE 
	};

	ConfigFile::ConfigFile(const std::string& config_file)
		: mFields()
	{
		this->Parse(config_file);
	}
	
	ConfigFile::~ConfigFile()
	{}
	
	void ConfigFile::Parse(const std::string& config_file)
	{
		unsigned int index = 0;
		std::string key = "";
		std::string value = "";
		PARSING state = PARSING::KEY;
		for (auto& iterator : config_file)
		{
			if (iterator == ':')
			{
				state = PARSING::VALUE;
			}
			else if (iterator == '\n')
			{
				state = PARSING::KEY;
				mFields[key] = value;
				mIndex[index++] = key;
				key = "";
				value = "";
			}
			else if (iterator != ' ')
			{
				switch (state)
				{
				case PARSING::KEY:		key += iterator;	break;
				case PARSING::VALUE:	value += iterator;	break;
				default:									break;
				}
			}
		}
	}

	int ConfigFile::GetInt(const std::string& field) const
	{
		return std::atoi(this->mFields.at(field).c_str());
	}

	char ConfigFile::GetChar(const std::string& field) const
	{
		return this->mFields.at(field)[0];
	}

	float ConfigFile::GetFloat(const std::string& field) const
	{
		return static_cast<float>(this->GetDouble(field));
	}

	double ConfigFile::GetDouble(const std::string& field) const
	{
		return std::atof(this->mFields.at(field).c_str());
	}
	
	std::string ConfigFile::GetString(const std::string& field) const
	{
		return this->mFields.at(field);
	}
	
	int ConfigFile::GetInt(unsigned int field_index) const
	{
		return std::atoi(this->mFields.at(mIndex.at(field_index)).c_str());
	}

	char ConfigFile::GetChar(unsigned int field_index) const
	{
		return this->mFields.at(mIndex.at(field_index))[0];
	}
	
	float ConfigFile::GetFloat(unsigned int field_index) const
	{
		return static_cast<float>(this->GetDouble(mIndex.at(field_index)));
	}

	double ConfigFile::GetDouble(unsigned int field_index) const
	{
		return std::atof(this->mFields.at(mIndex.at(field_index)).c_str());
	}

	std::string ConfigFile::GetString(unsigned int field_index) const
	{
		return this->mFields.at(mIndex.at(field_index));
	}
}