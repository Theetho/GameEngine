#pragma once

#include "spdlog/spdlog.h"

namespace Engine
{

	class Log
	{
	public:
		static void Initialize();

		static Ref<spdlog::logger>& GetEngineLogger();
		static Ref<spdlog::logger>& GetApplicationLogger();
	private:
		static Ref<spdlog::logger> sEngineLogger;
		static Ref<spdlog::logger> sApplicationLogger;
	};

}

#ifdef ENGINE_FILES
	#define ENGINE_LOG_INFO(...) ::Engine::Log::GetEngineLogger()->info(__VA_ARGS__)
	#define ENGINE_LOG_TRACE(...) ::Engine::Log::GetEngineLogger()->trace(__VA_ARGS__)
	#define ENGINE_LOG_DEBUG(...) ::Engine::Log::GetEngineLogger()->debug(__VA_ARGS__)
	#define ENGINE_LOG_WARN(...) ::Engine::Log::GetEngineLogger()->warn(__VA_ARGS__)
	#define ENGINE_LOG_ERROR(...) ::Engine::Log::GetEngineLogger()->error(__VA_ARGS__)
	#define ENGINE_LOG_CRITICAL(...) ::Engine::Log::GetEngineLogger()->critical(__VA_ARGS__)
	#define ENGINE_LOG_VEC3(vec) ENGINE_LOG_INFO("{0} {1} {2}", vec.x, vec.y, vec.z) 	
#endif

#define APP_LOG_INFO(...) ::Engine::Log::GetApplicationLogger()->info(__VA_ARGS__)
#define APP_LOG_TRACE(...) ::Engine::Log::GetApplicationLogger()->trace(__VA_ARGS__)
#define APP_LOG_DEBUG(...) ::Engine::Log::GetApplicationLogger()->debug(__VA_ARGS__)
#define APP_LOG_WARN(...) ::Engine::Log::GetApplicationLogger()->warn(__VA_ARGS__)
#define APP_LOG_ERROR(...) ::Engine::Log::GetApplicationLogger()->error(__VA_ARGS__)
#define APP_LOG_CRITICAL(...) ::Engine::Log::GetApplicationLogger()->critical(__VA_ARGS__)
#define APP_LOG_VEC3(vec) APP_LOG_INFO("{0} {1} {2}", vec.x, vec.y, vec.z) 