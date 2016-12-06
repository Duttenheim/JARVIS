//------------------------------------------------------------------------------
/**
    @class JARVIS::Core::PersistentThread
 	(C) 2015 See the LICENSE file.
*/
#include "config.h"
#include "threads/persistentthread.h"
namespace JARVIS {
namespace Threading
{

//------------------------------------------------------------------------------
/**
*/
PersistentThread::PersistentThread() :
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
    if (this->thread.Valid()) this->Stop();
    this->thread = nullptr;
}

//------------------------------------------------------------------------------
/**
*/
void
PersistentThread::Enqueue(const Ptr<Threading::ThreadJobFunc>& func, const Threading::ThreadJobContext& context)
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
    j_assert(!this->thread.Valid());
    this->thread = Thread::Create();
    
    auto proc = Core::Functional::Lambda([this]()
    {
        while (this->thread->Running())
        {
            while (this->funcs.Size() > 0)
            {
				const Ptr<Threading::ThreadJobFunc>& func = this->funcs[0];
                const Threading::ThreadJobContext& ctx = this->contexts[0];
                func->Call(ctx.inputs, ctx.outputs, ctx.uniforms);
                this->funcs.RemoveIndexThreadSafe(0);
            }
            this->working.exchange(false);
            
            // sleep thread a little
            Threading::Sleep(1);
        }
    });
    
    // start thread
    this->thread->Start(proc);
}

//------------------------------------------------------------------------------
/**
*/
void
PersistentThread::Stop()
{
    j_assert(this->thread.Valid());
    this->thread = nullptr;
}

}} // namespace JARVIS::Core
