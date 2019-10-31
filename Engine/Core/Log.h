#pragma once

#include "spdlog/spdlog.h"

namespace Engine
{

	class Log
	{
	public:
		static void init();

		inline static Ref<spdlog::logger>& getEngineLogger()
		{
			return s_engineLogger;
		}
		
		inline static Ref<spdlog::logger>& getAppLogger()
		{
			return s_appLogger;
		}

	private:
		static Ref<spdlog::logger> s_engineLogger;
		static Ref<spdlog::logger> s_appLogger;
	};

}

#ifdef ENGINE_FILES
	#define ENGINE_LOG_INFO(...) ::Engine::Log::getEngineLogger()->info(__VA_ARGS__)
	#define ENGINE_LOG_TRACE(...) ::Engine::Log::getEngineLogger()->trace(__VA_ARGS__)
	#define ENGINE_LOG_DEBUG(...) ::Engine::Log::getEngineLogger()->debug(__VA_ARGS__)
	#define ENGINE_LOG_WARN(...) ::Engine::Log::getEngineLogger()->warn(__VA_ARGS__)
	#define ENGINE_LOG_ERROR(...) ::Engine::Log::getEngineLogger()->error(__VA_ARGS__)
	#define ENGINE_LOG_CRITICAL(...) ::Engine::Log::getEngineLogger()->critical(__VA_ARGS__)
#endif

#define APP_LOG_INFO(...) ::Engine::Log::getAppLogger()->info(__VA_ARGS__)
#define APP_LOG_TRACE(...) ::Engine::Log::getAppLogger()->trace(__VA_ARGS__)
#define APP_LOG_DEBUG(...) ::Engine::Log::getAppLogger()->debug(__VA_ARGS__)
#define APP_LOG_WARN(...) ::Engine::Log::getAppLogger()->warn(__VA_ARGS__)
#define APP_LOG_ERROR(...) ::Engine::Log::getAppLogger()->error(__VA_ARGS__)
#define APP_LOG_CRITICAL(...) ::Engine::Log::getAppLogger()->critical(__VA_ARGS__)