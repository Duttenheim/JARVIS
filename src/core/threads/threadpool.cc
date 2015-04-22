//------------------------------------------------------------------------------
/**
    @class JARVIS::Core::ThreadPool
 	(C) 2015 See the LICENSE file.
*/
#include "config.h"
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
ThreadPool::Enqueue(const Ptr<Threading::ThreadJobFunc>& func, const Threading::ThreadJobContext& ctx)
{
    this->funcs.Append(func);
    this->contexts.Append(ctx);
}

//------------------------------------------------------------------------------
/**
*/
void
ThreadPool::Update()
{
	uint32 i;
	while (this->freeThreads.Size() > 0 && this->funcs.Size() > 0)
	{
        // aquire thread, function and thread context
		const Ptr<Thread>& thread = this->freeThreads[0];
		const Ptr<Threading::ThreadJobFunc>& func = this->funcs[0];
        const Threading::ThreadJobContext& ctx = this->contexts[0];
        
        // start thread
		thread->Start(func, ctx.inputs, ctx.outputs, ctx.uniforms);
    
		// add currently running thread to the active thread list
		this->activeThreads.Append(thread);

        // remove thread, context and function from the todo-lists
		this->funcs.RemoveIndex(0);
		this->freeThreads.RemoveIndex(0);
    }

	for (i = 0; i < this->activeThreads.Size(); i++)
	{
		const Ptr<Thread>& thread = this->activeThreads[i];

		// stop thread and move to other list if done
		if (!thread->Running())
		{
			thread->Wait();
			this->freeThreads.Append(thread);
			this->activeThreads.RemoveIndex(i);
			i--;
		}
	}
}

}}
