#include "EnginePch.h"
#include "Log.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace Engine
{
	Ref<spdlog::logger> Log::sEngineLogger;
	Ref<spdlog::logger> Log::sApplicationLogger;

	void Log::Initialize()
	{
		spdlog::set_pattern("[%H:%M:%S] [%n] : %v%$");

		sEngineLogger = spdlog::stdout_color_mt("ENGINE");
		sEngineLogger->set_level(spdlog::level::trace);

		sApplicationLogger = spdlog::stdout_color_mt("APP");
		sApplicationLogger->set_level(spdlog::level::trace);

	}

	Ref<spdlog::logger>& Log::GetEngineLogger()
	{
		return sEngineLogger;
	}

	Ref<spdlog::logger>& Log::GetApplicationLogger()
	{
		return sApplicationLogger;
	}
}