//------------------------------------------------------------------------------
/**
    @class JARVIS::Core::PersistentThread
 	(C) 2015 See the LICENSE file.
*/
#include "config.h"
#include "threads/persistentthread.h"
namespace JARVIS {
namespace Core
{

//------------------------------------------------------------------------------
/**
*/
PersistentThread::PersistentThread() :
    running({false}),
    working({false}),
	thread(nullptr)
{
	// empty
}

//------------------------------------------------------------------------------
/**
*/
PersistentThread::~PersistentThread()
{
    if (nullptr != this->thread) this->Stop();
    this->thread = nullptr;
}

//------------------------------------------------------------------------------
/**
*/
void
PersistentThread::Enqueue(const Core::Ptr<Threading::ThreadJobFunc>& func, const Threading::ThreadJobContext& context)
{
	this->working.exchange(true);
    this->funcs.AppendThreadSafe(func);
    this->contexts.AppendThreadSafe(context);
}

//------------------------------------------------------------------------------
/**
*/
void
PersistentThread::Start()
{
    j_assert(nullptr == this->thread);
    auto proc = [this]()
    {
        while (this->running.load())
        {
            while (this->funcs.Size() > 0)
            {
				const Core::Ptr<Threading::ThreadJobFunc>& func = this->funcs[0];
                const Threading::ThreadJobContext& ctx = this->contexts[0];
                func->Call(ctx.inputs, ctx.outputs, ctx.uniforms);
                this->funcs.RemoveIndexThreadSafe(0);
            }
            this->working.exchange(false);
            
            // sleep thread a little
            Threading::Sleep(1);
        }
        
        // flip running status
        this->running.exchange(false);
    };
    
	this->running.exchange(true);
    this->thread = Memory::New<std::thread>(proc);
}

//------------------------------------------------------------------------------
/**
*/
void
PersistentThread::Stop()
{
    j_assert(nullptr != this->thread);
    this->running.exchange(false);
    this->thread->join();
    delete this->thread;
    this->thread = nullptr;
}

}}
