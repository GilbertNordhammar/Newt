#pragma once

namespace Jerboa {
	namespace TimeInternals {
		void Update();
	}

	class Time
	{
		friend void TimeInternals::Update();
	public:
		// Returns current time in seconds
		static float GetTime();
		// Returns time since last frame in seconds
		static float GetDeltaTime();
	};
}


