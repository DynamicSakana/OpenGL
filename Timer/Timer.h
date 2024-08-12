/**
 * @file Timer.h
 * @author DynamicSakana (2998959253@qq.com)
 * @brief This is a simple timer to evaluate a scope.
 * @version 0.1
 * @date 2024-08-12
 * 
 * @copyright Copyright (c) 2024 DynamicSakana, all rights served
 * 
 */

#pragma once
#include <chrono>
#include <iostream>

#define MILI true
#define MICRO false

/**
 * @brief To apply this to your program use the macro defined following
 * 
 */

#define UNIT_MILI Timer::SetUnit(MILI);
#define UNIT_MICRO Timer::SetUnit(MICRO);

#define TIMER_FUNC(name) FuncTimer timer(name);
#define FUNC_TIMER TIMER_FUNC(__PRETTY_FUNCTION__)

#define TIMER_SCOPE(name) ScopeTimer timer(name);
#define SCOPE_TIMER ScopeTimer timer("");

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


// -------------------------------------------------
// FuncTimer
class FuncTimer : public Timer
{
public:
	FuncTimer(const std::string &);
	~FuncTimer() override;
};


// -------------------------------------------------
// ScopeTimer
class ScopeTimer : public Timer
{
public:
	ScopeTimer(const std::string &);
	~ScopeTimer() override;
};

