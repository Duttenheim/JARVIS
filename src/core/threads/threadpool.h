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

	/// typedef a typical thread function
	typedef std::function<void(byte*, byte*, byte*)> ThreadPoolFunc;

    /// constructor
    ThreadPool(uint32 threads);
    /// destructor
    virtual ~ThreadPool();
    
    /// enqueue thread function
	void Enqueue(const ThreadPoolFunc& func, byte* inputs, byte* outputs, byte* uniforms);
    /// update thread pool, this causes the threads to update their status, and finished threads to attain new tasks
    void Update();
private:

	struct ThreadFuncContext
	{
		byte* inputs;
		byte* outputs;
		byte* uniforms;
	};

    Array<Ptr<Thread>> activeThreads;
    Array<Ptr<Thread>> freeThreads;
	Array<ThreadPoolFunc> funcs;
	Array<ThreadFuncContext> contexts;
};

}} // namespace JARVIS::Core