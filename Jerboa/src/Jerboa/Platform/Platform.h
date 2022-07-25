#pragma once

#if defined(JERBOA_PLATFORM_WINDOWS)
	#define JERBOA_RENDER_API_OPENGL
#endif

namespace Jerboa {
	enum class RenderAPI {
		None, OpenGL
	};

	class Platform {
	public:
		static void SetRenderAPI(RenderAPI api) { mRenderApi = api; };
		static RenderAPI GetRenderApi() { return mRenderApi; }
	private:
		static RenderAPI mRenderApi;
	};
}