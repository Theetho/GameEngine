#include "EnginePch.h"
#include "Benchmark.h"

namespace Engine
{
	Benchmark::Benchmark()
		: m_start(std::chrono::high_resolution_clock::now())
	{
	}
	Benchmark::~Benchmark()
	{
	}

	void Benchmark::tick()
	{
		m_end = std::chrono::high_resolution_clock::now();

		auto start = std::chrono::time_point_cast<std::chrono::microseconds>(m_start).time_since_epoch().count();
		auto end = std::chrono::time_point_cast<std::chrono::microseconds>(m_end).time_since_epoch().count();
	
		auto duration = end - start;

		std::cout << duration << "us (" << duration * 0.001 << " ms)\n";

		m_start = m_end;
	}
}