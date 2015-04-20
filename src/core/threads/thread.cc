//------------------------------------------------------------------------------
/**
    @class JARVIS::Core::Thread
 	(C) 2015 See the LICENSE file.
*/
#include "thread.h"
#include "mem.h"
namespace JARVIS {
namespace Core
{
    
//------------------------------------------------------------------------------
/**
*/
Thread::Thread() :
    stop({0}),
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
    this->Stop();
}

//------------------------------------------------------------------------------
/**
*/
void
Thread::Stop()
{
    j_assert(nullptr != this->thread);
    Memory::Free(this->thread);
}

//------------------------------------------------------------------------------
/**
*/
void
Thread::Wait()
{
    j_assert(nullptr != this->thread);
    this->thread->join();
    Memory::Free(this->thread);
}

//------------------------------------------------------------------------------
/**
*/
void
Thread::Start(const std::function<void()> &func)
{
    j_assert(nullptr == this->thread);
    this->thread = Memory::New<std::thread>(func);
}

}} // namespace JARVIS::Core
