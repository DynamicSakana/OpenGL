#include "Timer.h"
bool Timer::msAsUnit;

// -------------------------------------------------
// Timer
Timer::Timer() = default; // default constructor must be provided, the constructor of a sub-class will call the constructor of base first
Timer::Timer(const std::string &name) : m_name(name)
{
	auto startTime = std::chrono::high_resolution_clock::now();
	start = std::chrono::time_point_cast<std::chrono::microseconds>(startTime).time_since_epoch().count();
	msAsUnit = true;
}

void Timer::SetUnit(bool unit)
{
	msAsUnit = unit;
}

inline void Timer::Stop()
{
	auto endTime = std::chrono::high_resolution_clock::now();
	end = std::chrono::time_point_cast<std::chrono::microseconds>(endTime).time_since_epoch().count();

	duration_us = end - start;
	duration_ms = duration_us * 0.001;
}

Timer::~Timer() { }

// -------------------------------------------------
// FuncTimer
FuncTimer::FuncTimer(const std::string &name) : Timer(name) { }

FuncTimer::~FuncTimer()
{
	Stop();
	if (msAsUnit)
	{
		std::cout << "  Func " << m_name << " took " << duration_ms << " ms.\n";
	}
	else
	{
		std::cout << "  Func " << m_name << " took " << duration_us << " us.\n";
	}
}

// -------------------------------------------------
// ScopeTimer
ScopeTimer::ScopeTimer(const std::string &name) : Timer(name) { }

ScopeTimer::~ScopeTimer()
{
	Stop();
	if (msAsUnit)
	{
		std::cout << "  Scope " << m_name << " took " << duration_ms << " ms.\n";
	}
	else
	{
		std::cout << "  Scope" << m_name << " took " << duration_us << " us.\n";
	}
}