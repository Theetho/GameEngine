#include "EnginePch.h"
#include "ConfigFile.h"

namespace Engine
{
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
		std::string line = "";
		std::ifstream file(config_file, std::ios::in, std::ios::binary);
		while (std::getline(file, line))
		{
			if (line.size() == 0 || (line[0] == '/' && line[1] == '/'))
				continue;

			std::string key = "";
			std::string value = "";

			auto double_dot = line.find_first_of(':');
			
			if (double_dot == std::string::npos)
				continue; 
				
			line = line.erase(double_dot, 1);

			std::istringstream file_to_string(line);

			file_to_string >> key >> value;
			mFields[key]    = value;
			mIndex[index++] = value;
		}
	}
}