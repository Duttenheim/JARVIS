#pragma once
//------------------------------------------------------------------------------
/**
	@class JARVIS::Core::Thread
	
	(C) 2015 See the LICENSE file.
 */
//------------------------------------------------------------------------------
#include <thread>
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
    
    /// tell the thread to stop
    void Stop();
    /// wait for thread to finish
    void Wait();

	/// returns true if thread is running
	const bool Running() const;
    
    /// start thread
    void Start(const std::function<void()>& func);
	/// start thread with templated function
	template <typename THREADPROC, class... ARGS> void Start(const THREADPROC& functor, ARGS&&... args);
private:
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
template <typename THREADPROC, class... ARGS>
void
Thread::Start(const THREADPROC& functor, ARGS&&... args)
{
	j_assert(nullptr == this->thread);
	auto threadProc = [&]()
	{
		functor(args...);
		this->running.exchange(false);
	};
	this->thread = Memory::New<std::thread>(threadProc);
	this->running.exchange(true);
}

}} // namespace JARVIS::Core