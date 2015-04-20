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
    
    /// start thread
    void Start(const std::function<void()>& func);
private:
    std::atomic<bool> stop;
    std::thread* thread;
};

}} // namespace JARVIS::Core