#pragma once

#include "Log.h"

#ifdef JERBOA_DEBUG
	#define JERBOA_ASSERTS_ENABLED
#endif

// TODO: __debugbreak() is specific to MSVC, so change it depending on platform
#ifdef JERBOA_ASSERTS_ENABLED
	#define JERBOA_ASSERT(condition, message) { \
		if(!(condition)) { \
			JERBOA_LOG_ERROR("Assertion Failed: {0}", message); \
			__debugbreak(); } \
	}
#else
	#define JERBOA_ASSERT(...)
#endif