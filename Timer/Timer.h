#pragma once
#include <chrono>
#include <iostream>

#define MILI true
#define MICRO false

// -------------------------------------------------
// Timer
class Timer
{
public:
	int64_t start;
	int64_t end;
	int64_t duration_us;
	double duration_ms;
	static bool msAsUnit;

	std::string m_name;

public:
	Timer();
	Timer(const std::string &);
	static void SetUnit(bool);
	void Stop();
	virtual ~Timer() = 0;
};
#define UNIT_MILI Timer::SetUnit(MILI);
#define UNIT_MICRO Timer::SetUnit(MICRO);

// -------------------------------------------------
// FuncTimer
class FuncTimer : public Timer
{
public:
	FuncTimer(const std::string &);
	~FuncTimer() override;
};
#define TIMER_FUNC(name) FuncTimer timer(name);
#define FUNC_TIMER TIMER_FUNC(__PRETTY_FUNCTION__)

// -------------------------------------------------
// ScopeTimer
class ScopeTimer : public Timer
{
public:
	ScopeTimer(const std::string &);
	~ScopeTimer() override;
};
#define TIMER_SCOPE(name) ScopeTimer timer(name);
#define SCOPE_TIMER ScopeTimer timer("");
