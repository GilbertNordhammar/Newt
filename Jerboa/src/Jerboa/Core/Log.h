#pragma once

#include "spdlog/spdlog.h"

namespace Jerboa {
	class Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetAppLogger() { return s_AppLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_AppLogger;
	};
}

#ifndef JERBOA_RELEASE
	#define JERBOA_LOGGING_ENABLED
#endif

#ifdef JERBOA_LOGGING_ENABLED
	#ifdef JERBOA_CORE
		#define JERBOA_LOG_TRACE(...)	Jerboa::Log::GetCoreLogger()->trace(__VA_ARGS__)
		#define JERBOA_LOG_INFO(...)	Jerboa::Log::GetCoreLogger()->info(__VA_ARGS__)
		#define JERBOA_LOG_WARN(...)	Jerboa::Log::GetCoreLogger()->warn(__VA_ARGS__)
		#define JERBOA_LOG_ERROR(...)	Jerboa::Log::GetCoreLogger()->error(__VA_ARGS__)
		#define JERBOA_LOG_FATAL(...)	Jerboa::Log::GetCoreLogger()->critical(__VA_ARGS__)
	#else
		#define JERBOA_LOG_TRACE(...)	Jerboa::Log::GetAppLogger()->trace(__VA_ARGS__)
		#define JERBOA_LOG_INFO(...)	Jerboa::Log::GetAppLogger()->info(__VA_ARGS__)
		#define JERBOA_LOG_WARN(...)	Jerboa::Log::GetAppLogger()->warn(__VA_ARGS__)
		#define JERBOA_LOG_ERROR(...)	Jerboa::Log::GetAppLogger()->error(__VA_ARGS__)
		#define JERBOA_LOG_FATAL(...)	Jerboa::Log::GetAppLogger()->critical(__VA_ARGS__)
	#endif
#else
	#define JERBOA_LOG_TRACE(...)
	#define JERBOA_LOG_INFO(...)
	#define JERBOA_LOG_WARN(...)
	#define JERBOA_LOG_ERROR(...)
	#define JERBOA_LOG_FATAL(...)
#endif


