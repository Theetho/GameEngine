#include "EnginePch.h"
#include "Benchmark.h"

namespace Engine
{
	Benchmark::Benchmark()
		: mStart(std::chrono::high_resolution_clock::now())
	{}

	Benchmark::~Benchmark()
	{
		Tick();
	}

	void Benchmark::Tick()
	{
		mEnd = std::chrono::high_resolution_clock::now();

		auto start = std::chrono::time_point_cast<std::chrono::microseconds>(mStart).time_since_epoch().count();
		auto end = std::chrono::time_point_cast<std::chrono::microseconds>(mEnd).time_since_epoch().count();
	
		auto duration = end - start;

		std::cout << duration << "us (" << duration * 0.001 << " ms)\n";

		mStart = mEnd;
	}
}