#pragma once
//------------------------------------------------------------------------------
/**
	@class JARVIS::Core::Thread
	
	(C) 2015 See the LICENSE file.
 */
//------------------------------------------------------------------------------
#include <thread>
#include "threading.h"
#include "functional/function.h"
namespace JARVIS {
namespace Core
{

class Thread : public Ref
{
    __ClassDecl(Thread);
public:
    /// constructor from lambda function
    Thread();
    /// destructor
    virtual ~Thread();

	/// copy constructor
	Thread(const Thread& rhs);
	/// move constructor
	Thread(Thread&& rhs);

	/// assign operator
	void operator=(const Thread& rhs);
	/// move operator
	void operator=(Thread&& rhs);
    
    /// wait for thread to finish, also deletes the thread
    virtual void Wait();

	/// returns true if thread is running
	const bool Running() const;
    
	/// execute thread given a function and a list of arguments
	template <class THREADPROC, class ...PARAMS> void Start(const THREADPROC& func, PARAMS&& ...args);
    
protected:
    std::atomic<bool> running;
    std::thread* thread;
};

//------------------------------------------------------------------------------
/**
*/
inline const bool
Thread::Running() const
{
	return this->running.load(std::memory_order_relaxed);
}

//------------------------------------------------------------------------------
/**
*/
template <class THREADPROC, class ...PARAMS>
void
Thread::Start(const THREADPROC& func, PARAMS&& ...args)
{
	j_assert(nullptr == this->thread);
	auto threadProc = [&]()
	{
        func->Call(args...);
		this->running.exchange(false);
	};
	this->thread = Memory::New<std::thread>(threadProc);
	this->running.exchange(true);
}

}} // namespace JARVIS::Core