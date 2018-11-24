#pragma once

#include <chrono>

namespace utils
{
	class SystemClock {
		std::chrono::high_resolution_clock m_clock;

	public:
		uint64_t millisec();
		uint64_t nanosec();

	private:
		std::chrono::steady_clock::duration inline time()
		{
			return m_clock.now().time_since_epoch();
		}
	};
}
