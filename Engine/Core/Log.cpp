#include "EnginePch.h"
#include "Log.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace Engine
{

	std::shared_ptr<spdlog::logger> Log::s_engineLogger;
	std::shared_ptr<spdlog::logger> Log::s_appLogger;

	void Log::init()
	{
		spdlog::set_pattern("[%H:%M:%S] [%n] : %v%$");

		s_engineLogger = spdlog::stdout_color_mt("ENGINE");
		s_engineLogger->set_level(spdlog::level::trace);

		s_appLogger = spdlog::stdout_color_mt("APP");
		s_appLogger->set_level(spdlog::level::trace);

	}

}