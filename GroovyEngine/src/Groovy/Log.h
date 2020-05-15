#pragma once
#include "Core.h"
#include "spdlog/spdlog.h"
#include <memory>

namespace GroovyEngine {

	//We provide a logging API that hides complicated logging usage under the hood for users
	class GE_API Log {

	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;

	};

}


//Wrapper macros to simplify logging
//Core Logging
#define GE_CORE_TRACE(...) ::GroovyEngine::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define GE_CORE_INFO(...)  ::GroovyEngine::Log::GetCoreLogger()->info(__VA_ARGS__)
#define GE_CORE_WARN(...)  ::GroovyEngine::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define GE_CORE_ERROR(...) ::GroovyEngine::Log::GetCoreLogger()->error(__VA_ARGS__)
#define GE_CORE_FATAL(...) ::GroovyEngine::Log::GetCoreLogger()->fatal(__VA_ARGS__)

//Client Logging
#define GE_TRACE(...)      ::GroovyEngine::Log::GetClientLogger()->trace(__VA_ARGS__)
#define GE_INFO(...)       ::GroovyEngine::Log::GetClientLogger()->info(__VA_ARGS__)
#define GE_WARN(...)       ::GroovyEngine::Log::GetClientLogger()->warn(__VA_ARGS__)
#define GE_ERROR(...)      ::GroovyEngine::Log::GetClientLogger()->error(__VA_ARGS__)
#define GE_FATAL(...)      ::GroovyEngine::Log::GetClientLogger()->fatal(__VA_ARGS__)