#pragma once
//------------------------------------------------------------------------------
/**
	@class JARVIS::Core::PersistentThread
	
    A persistent thread is not a fire-n-forget thread.
    Instead, a persistent thread is meant to run paralell to the main process,
    and run paralell functions by queueing them.
	
	(C) 2015 See the LICENSE file.
 */
//------------------------------------------------------------------------------
#include <thread>
#include "threadpool.h"
namespace JARVIS {
namespace Core
{
class PersistentThread : public Ref
{
    __ClassDecl(PersistentThread);
public:
    /// constructor
    PersistentThread();
    /// destructor
    virtual ~PersistentThread();
    
    /// enqueue function to run
	void Enqueue(const Core::Ptr<Threading::ThreadJobFunc>& func, const Threading::ThreadJobContext& context);
    
    /// start the thread
    void Start();
    /// stop the thread
    void Stop();
    
    /// returns true if the thread is running
    const bool Running() const;
    /// returns true if it's currently working a job
    const bool Working() const;
    
private:
	Array<Core::Ptr<Threading::ThreadJobFunc>> funcs;
    Array<Threading::ThreadJobContext> contexts;
    std::atomic<bool> running;
    std::atomic<bool> working;
    std::thread* thread;
};

//------------------------------------------------------------------------------
/**
*/
inline const bool
PersistentThread::Running() const
{
    return this->running.load();
}

//------------------------------------------------------------------------------
/**
*/
inline const bool
PersistentThread::Working() const
{
    return this->working.load();
}

}} // namespace JARVIS::Core