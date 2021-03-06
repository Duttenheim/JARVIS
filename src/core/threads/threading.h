#pragma once
//------------------------------------------------------------------------------
/**
    @file core/threads/threading.h
 
	(C) 2015 See the LICENSE file.
*/
#include "function.h"
#include <thread>
namespace JARVIS {
namespace Threading
{

/// typedef a typical thread function
typedef Core::Function<void(byte*, byte*, byte*)> ThreadJobFunc;

/// define struct for common case use of thread jobs
struct ThreadJobContext
{
    byte* inputs;
    byte* outputs;
    byte* uniforms;
};

/// create job context from template
template<class INPUT, class OUTPUT, class UNIFORM>
static ThreadJobContext CreateContext(INPUT inputs, OUTPUT outputs, UNIFORM uniforms)
{
    return ThreadJobContext{(byte*)inputs, (byte*)outputs, (byte*)uniforms};
}
    
//------------------------------------------------------------------------------
/**
    Sleep current thread.
    @param ms The time in milliseconds to sleep this thread.
*/
static inline void
Sleep(uint32 ms)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

//------------------------------------------------------------------------------
/**
    Yield slice for current thread.
*/
static inline void
YieldThread()
{
    std::this_thread::yield();
}

}} // namespace JARVIS::Threading