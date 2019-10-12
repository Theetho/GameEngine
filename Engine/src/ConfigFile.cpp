#include "../include/ConfigFile.h"

namespace Engine
{
	enum class PARSING { KEY, VALUE };

	ConfigFile::ConfigFile(const std::string& cf)
		: m_fields()
	{
		this->parse(cf);
	}
	ConfigFile::~ConfigFile()
	{
	}
	void ConfigFile::parse(const std::string& cf)
	{
		unsigned int index = 0;
		for (auto& it : cf)
		{
			std::string key = "";
			std::string value = "";
			PARSING state = PARSING::KEY;

			if (it == ':')
			{
				state = PARSING::VALUE;
			}
			else if (it == '\n')
			{
				state = PARSING::KEY;
				m_fields[key] = value;
				m_index[index++] = key;
				key = "";
				value = "";
			}
			else
			{
				switch (state)
				{
				case PARSING::KEY:		key += it;		break;
				case PARSING::VALUE:	value += it;	break;
				default:								break;
				}
			}
		}
	}
}