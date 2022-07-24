#pragma once

// TODO: Comment back outer define once all opengl calls have been removed from the client
//#if defined(JERBOA_RENDER_API_OPENGL)
	#if defined(JERBOA_PLATFORM_WINDOWS)
		#include "glad/glad.h"
	#endif
//#endif