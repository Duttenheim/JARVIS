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
#include "function.h"
#include "thread.h"
#include "threading.h"
namespace JARVIS {
namespace Threading
{
class ThreadPool : public Ref
{
    __ClassDecl(ThreadPool);
public:

    struct ThreadPoolJob : public Ref
    {
        __ClassDecl(ThreadPoolJob);
        Ptr<ThreadJobFunc> func;
        ThreadJobContext ctx;
        int32 idx;
        
        ThreadPoolJob() : func(nullptr), ctx({nullptr, nullptr, nullptr}), idx(-1) {};
        ThreadPoolJob(const ThreadPoolJob& rhs) : func(rhs.func), ctx(rhs.ctx), idx(rhs.idx) {};
        ThreadPoolJob(ThreadPoolJob&& rhs)
        {
            this->func = rhs.func;
            this->idx = rhs.idx;
            this->ctx = rhs.ctx;
            
            rhs.func = nullptr;
            rhs.idx = -1;
            rhs.ctx = {nullptr, nullptr, nullptr};
        }
        virtual ~ThreadPoolJob() { this->func = nullptr; this->idx = -1; }
        void operator=(ThreadPoolJob&& rhs)
        {
            this->func = rhs.func;
            this->idx = rhs.idx;
            this->ctx = rhs.ctx;
            
            rhs.func = nullptr;
            rhs.idx = -1;
            rhs.ctx = {nullptr, nullptr, nullptr};
        }
    };
    
    /// constructor
    ThreadPool(uint32 threads);
    /// destructor
    virtual ~ThreadPool();
    
    /// enqueue thread function and its execution context and returns the job created
	Ptr<ThreadPoolJob> Enqueue(const Ptr<Threading::ThreadJobFunc>& func, const ThreadJobContext& ctx);
    /// update thread pool, this causes the threads to update their status, and finished threads to attain new tasks
    void Update();
    /// waits for thread using index
    void Wait(const Ptr<ThreadPoolJob>& job);
    /// check if thread is running
    bool Running(const Ptr<ThreadPoolJob>& job);
    /// waits for all jobs to finish
    void Sync();

    /// returns false if there are no pending jobs
    const bool Working() const;
private:

    /// helper function to wait for a thread to finish and shuffles it to the free list, returns true if it's done
    bool __Wait(const uint32 idx, bool kill = false);

    Array<Ptr<Thread>> activeThreads;
    Array<Ptr<Thread>> freeThreads;
    
    Array<Ptr<ThreadPoolJob>> pendingJobs;
    Array<Ptr<ThreadPoolJob>> activeJobs;
};

//------------------------------------------------------------------------------
/**
*/
inline const bool
ThreadPool::Working() const
{
    return this->activeThreads.Size() > 0;
}
}} // namespace JARVIS::Core