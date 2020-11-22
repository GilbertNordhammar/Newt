#include "jerboa-pch.h"
#include "Base.h"
#include "Log.h"

#define HAZEL_BUILD_ID "v0.1a"

namespace Jerboa {

	void InitializeCore()
	{
		Log::Init();

		JERBOA_LOG_TRACE("Jerboa Engine {}", HAZEL_BUILD_ID);
		JERBOA_LOG_TRACE("Initializing...");
	}

	void ShutdownCore()
	{
		JERBOA_LOG_TRACE("Shutting down...");
	}
}