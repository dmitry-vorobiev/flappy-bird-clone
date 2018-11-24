#include "system_clock.h"

uint64_t utils::SystemClock::millisec()
{
	using namespace std::chrono;

	return duration_cast<milliseconds>(time()).count();
}

uint64_t utils::SystemClock::nanosec()
{
	using namespace std::chrono;

	return duration_cast<nanoseconds>(time()).count();
}