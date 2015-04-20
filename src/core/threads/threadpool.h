#pragma once
//------------------------------------------------------------------------------
/**
	@class JARVIS::Core::ThreadPool
	
    Implements a pool of threads which can be executed without having to explicitly create a thread.
    Thread functions must be a lambda function which returns void, but has three parameters,
        inputs, outputs and runtime constants (uniforms)
        
    The thread pool is always running, but enqueues functions whenever a thread is free.
	
	(C) 2015 See the LICENSE file.
 */
//------------------------------------------------------------------------------
#include <functional>
#include "util/array.h"
#include "thread.h"
namespace JARVIS {
namespace Core
{
class ThreadPool : public Ref
{
    __ClassDecl(ThreadPool);
public:
    /// constructor
    ThreadPool(uint32 threads);
    /// destructor
    virtual ~ThreadPool();
    
    /// enqueue thread function
    void Enqueue(const std::function<void(byte*, byte*, byte*)>& func);
    /// update thread pool, this causes the threads to update their status, and finished threads to attain new tasks
    void Update();
private:
    Array<Ptr<Thread>> activeThreads;
    Array<Ptr<Thread>> freeThreads;
    Array<std::function<void(byte*, byte*, byte*)>> funcs;
};

}} // namespace JARVIS::Core