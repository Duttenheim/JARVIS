#pragma once
//------------------------------------------------------------------------------
/**
	@class JARVIS::Core::Timer
	
	High precision timer used to do profiling.
	
	(C) 2015 See the LICENSE file.
*/
//------------------------------------------------------------------------------
#include <chrono>
#include "ref.h"
namespace JARVIS { 
namespace Core
{
class Timer : public Ref
{
	__ClassDecl(Timer);
public:
	/// constructor
	Timer();
	/// destructor
	virtual ~Timer();

	/// start timer
	void Start();
	/// stop timer
	void Stop();
	/// get time between start and stop
	float Time();

private:
	std::chrono::time_point<std::chrono::high_resolution_clock> start;
	float duration;
};

//------------------------------------------------------------------------------
/**
*/
inline
Timer::Timer() :
	duration(0)
{
	// empty
}

//------------------------------------------------------------------------------
/**
*/
inline
Timer::~Timer()
{
	// empty
}

//------------------------------------------------------------------------------
/**
*/
inline void
Timer::Start()
{
	this->start = std::chrono::high_resolution_clock::now();
	this->duration = 0.0f;
}

//------------------------------------------------------------------------------
/**
*/
inline void
Timer::Stop()
{
	auto dur = std::chrono::high_resolution_clock::now() - this->start;
	this->duration = std::chrono::duration_cast<std::chrono::nanoseconds>(dur).count() / 1000000000.0f;
}

//------------------------------------------------------------------------------
/**
	Return time as seconds
*/
inline float
Timer::Time()
{
	return this->duration;
}

}} // namespace JARVIS::Core