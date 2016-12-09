//------------------------------------------------------------------------------
//  @class JARVIS::Core::ThreadPool
// 	(C) 2015 See the LICENSE file.
//------------------------------------------------------------------------------
#include "config.h"
#include "threadpool.h"
namespace JARVIS {
namespace Threading
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
Ptr<ThreadPool::ThreadPoolJob>
ThreadPool::Enqueue(const Ptr<Threading::ThreadJobFunc>& func, const Threading::ThreadJobContext& ctx)
{
    Ptr<ThreadPoolJob> job = ThreadPoolJob::Create();
    job->func = func;
    job->ctx = ctx;
    job->idx = -1;
    this->pendingJobs.Append(job);
    return job;
}

//------------------------------------------------------------------------------
/**
    Call once per frame to update the entire thread pool.
    This will cause all pending jobs to be put on a thread if there are enough threads available.
    Jobs returned by Enqueue will have a thread index which is -1 before this function gets executed, and if
    the job gets fired this index will be valid.
*/
void
ThreadPool::Update()
{
	uint32 i;
    
	while (this->freeThreads.Size() > 0 && this->pendingJobs.Size() > 0)
	{
        // aquire thread, function and thread context
		const Ptr<Thread>& thread = this->freeThreads[0];
        Ptr<ThreadPoolJob> job = this->pendingJobs[0];
		const Ptr<Threading::ThreadJobFunc>& func = job->func;
        const Threading::ThreadJobContext& ctx = job->ctx;
        
        // start thread
		thread->Start(func, ctx.inputs, ctx.outputs, ctx.uniforms);
        job->idx = this->activeJobs.Size();
    
		// add currently running thread to the active thread list
		this->activeThreads.Append(thread);
        this->activeJobs.Append(job);

        // remove thread, context and function from the todo-lists
		this->pendingJobs.RemoveIndex(0);
		this->freeThreads.RemoveIndex(0);
    }
    
    // go through active threads and free up the ones for whom the job is done
	for (i = 0; i < this->activeThreads.Size(); i++)
	{
        if (this->__Wait(i, false)) i--;
	}
}

//------------------------------------------------------------------------------
/**
    Locks the caller thread until the particular job is done.
*/
void
ThreadPool::Wait(const Ptr<ThreadPoolJob>& job)
{
    if (job->idx >= 0)
    {
        this->__Wait(job->idx, true);
    }
}

//------------------------------------------------------------------------------
/**
*/
bool
ThreadPool::Running(const Ptr<ThreadPoolJob>& job)
{
    if (job->idx >= 0)
    {
        return this->activeThreads[job->idx]->Running();
    }
    return false;
}

//------------------------------------------------------------------------------
/**
*/
void
ThreadPool::Sync()
{
    while (this->pendingJobs.Size() > 0 || this->Working())
    {
        this->Update();
    }
}

//------------------------------------------------------------------------------
/**
    Helper function for waiting for a thread to finish.
    Joins the thread if it's running and kill is true.
*/
bool
ThreadPool::__Wait(const uint32 idx, bool kill)
{
    const Ptr<Thread>& thread = this->activeThreads[idx];
    if (kill || !thread->Running())
    {
        thread->Wait();
        this->freeThreads.Append(thread);
        this->activeThreads.RemoveIndex(idx);
        
        this->activeJobs[idx]->idx = -1;
        this->activeJobs.RemoveIndex(idx);
        return true;
    }
    return false;
}

}} // namespace JARVIS::Threading
