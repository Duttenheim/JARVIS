//------------------------------------------------------------------------------
/**
    @class JARVIS::Core::ThreadPool
 	(C) 2015 See the LICENSE file.
*/
#include "threadpool.h"
namespace JARVIS {
namespace Core
{
    
//------------------------------------------------------------------------------
/**
*/
ThreadPool::ThreadPool(uint32 threads)
{
    this->activeThreads.Resize(threads);
    this->freeThreads.Resize(threads);
    
    // setup threads as active
    uint32 i;
    for (i = 0; i < threads; i++)
    {
        this->freeThreads.Append(Thread::Create());
    }
}

//------------------------------------------------------------------------------
/**
*/
ThreadPool::~ThreadPool()
{
    this->activeThreads.Clear();
    this->freeThreads.Clear();
}

//------------------------------------------------------------------------------
/**
*/
void
ThreadPool::Enqueue(const std::function<void(byte*, byte*, byte*)>& func)
{
    this->funcs.Append(func);
}

//------------------------------------------------------------------------------
/**
*/
void
ThreadPool::Update()
{

}

}}
