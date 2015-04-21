//------------------------------------------------------------------------------
/**
    @class JARVIS::Core::Thread
 	(C) 2015 See the LICENSE file.
*/
#include "config.h"
#include "thread.h"
#include "mem.h"
namespace JARVIS {
namespace Core
{
    
//------------------------------------------------------------------------------
/**
*/
Thread::Thread() :
    running({false}),
    thread(nullptr)
{
    // empty
}
    
//------------------------------------------------------------------------------
/**
*/
Thread::~Thread()
{
    // forcefully stop the thread, which kills it and results in a call to std::terminate()
    if (nullptr != this->thread) this->Wait();
}

//------------------------------------------------------------------------------
/**
*/
void
Thread::Wait()
{
    j_assert(nullptr != this->thread);
    this->thread->join();
	delete this->thread;
	this->thread = nullptr;
}

//------------------------------------------------------------------------------
/**
*/
void
Thread::Start(const std::function<void()> &func)
{
    j_assert(nullptr == this->thread);
	auto threadProc = [this, &func]()
	{
		func();
		this->running.exchange(false);
	};
	this->thread = Memory::New<std::thread>(threadProc);
	this->running.exchange(true);
}

}} // namespace JARVIS::Core
