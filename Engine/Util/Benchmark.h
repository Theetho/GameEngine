#pragma once
#include <chrono>

namespace Engine
{
	class Benchmark
	{
	public:
		Benchmark();
		~Benchmark();

		void tick();
	private:
		std::chrono::time_point<std::chrono::high_resolution_clock> m_start;
		std::chrono::time_point<std::chrono::high_resolution_clock> m_end;
	};
}


