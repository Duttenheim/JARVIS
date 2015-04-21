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
	this->contexts.Resize(threads);
    
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
ThreadPool::Enqueue(const std::function<void(byte*, byte*, byte*)>& func, byte* inputs, byte* outputs, byte* uniforms)
{
    this->funcs.Append(func);
	this->contexts.Append(ThreadFuncContext{ inputs, outputs, uniforms });
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
		const Ptr<Thread>& thread = this->freeThreads[0];
		const ThreadPoolFunc& func = this->funcs[0];
		const ThreadFuncContext& context = this->contexts[0];
		thread->Start<ThreadPoolFunc>(func, context.inputs, context.outputs, context.uniforms);
		this->funcs.RemoveIndex(0);
		this->freeThreads.RemoveIndex(0);
		this->contexts.RemoveIndex(0);
		this->activeThreads.Append(thread);
	}

	for (i = 0; i < this->activeThreads.Size(); i++)
	{
		const Ptr<Thread>& thread = this->activeThreads[i];

		// stop thread and move to other list if done
		if (!thread->Running())
		{
			thread->Stop();
			this->freeThreads.Append(thread);
			this->activeThreads.RemoveIndex(i);
			i--;
		}
	}
}

}}
