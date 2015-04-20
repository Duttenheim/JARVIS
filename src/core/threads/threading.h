#pragma once
//------------------------------------------------------------------------------
/**
    @file core/threads/threading.h
 
	(C) 2015 See the LICENSE file.
*/

namespace JARVIS {
namespace Core {
namespace Threading
{

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
Yield()
{
    std::this_thread::yield();
}

}}}