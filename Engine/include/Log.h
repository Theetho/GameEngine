#pragma once

#include "Export.h"
#include "spdlog/spdlog.h"

namespace Engine
{

	class ENGINE_API Log
	{
	public:
		static void init();

		inline static std::shared_ptr<spdlog::logger>& getEngineLogger()
		{
			return s_engineLogger;
		}
		inline static std::shared_ptr<spdlog::logger>& getAppLogger()
		{
			return s_appLogger;
		}

	private:
		static std::shared_ptr<spdlog::logger> s_engineLogger;
		static std::shared_ptr<spdlog::logger> s_appLogger;
	};

}

#define ENGINE_LOG_INFO(...) ::Engine::Log::getEngineLogger()->info(__VA_ARGS__)
#define ENGINE_LOG_TRACE(...) ::Engine::Log::getEngineLogger()->trace(__VA_ARGS__)
#define ENGINE_LOG_DEBUG(...) ::Engine::Log::getEngineLogger()->debug(__VA_ARGS__)
#define ENGINE_LOG_WARN(...) ::Engine::Log::getEngineLogger()->warn(__VA_ARGS__)
#define ENGINE_LOG_ERROR(...) ::Engine::Log::getEngineLogger()->error(__VA_ARGS__)
#define ENGINE_LOG_CRITICAL(...) ::Engine::Log::getEngineLogger()->critical(__VA_ARGS__)

#define APP_LOG_INFO(...) ::Engine::Log::getAppLogger()->info(__VA_ARGS__)
#define APP_LOG_TRACE(...) ::Engine::Log::getAppLogger()->trace(__VA_ARGS__)
#define APP_LOG_DEBUG(...) ::Engine::Log::getAppLogger()->debug(__VA_ARGS__)
#define APP_LOG_WARN(...) ::Engine::Log::getAppLogger()->warn(__VA_ARGS__)
#define APP_LOG_ERROR(...) ::Engine::Log::getAppLogger()->error(__VA_ARGS__)
#define APP_LOG_CRITICAL(...) ::Engine::Log::getAppLogger()->critical(__VA_ARGS__)