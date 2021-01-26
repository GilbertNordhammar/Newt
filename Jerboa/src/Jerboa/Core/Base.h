#pragma once
namespace Jerboa {
	void InitializeCore();
	void ShutdownCore();
 
	bool DecimalEquals(float first, float second, float deviation);
}

// Workaround for MSVC "bug" https://stackoverflow.com/questions/5134523/msvc-doesnt-expand-va-args-correctly
#define JERBOA_EXPAND_VARGS( x ) x