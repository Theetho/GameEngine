#pragma once

#include <chrono>

namespace Engine
{
	class Benchmark
	{
	public:
		Benchmark();
		~Benchmark();

		void Tick();
	private:
		std::chrono::time_point<std::chrono::high_resolution_clock> mStart;
		std::chrono::time_point<std::chrono::high_resolution_clock> mEnd;
	};
}


