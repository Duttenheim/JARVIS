//------------------------------------------------------------------------------
/**
    @class JARVIS::Core::PersistentThread
 	(C) 2015 See the LICENSE file.
*/
#include "threads/persistentthread.h"
namespace JARVIS {
namespace Core
{

//------------------------------------------------------------------------------
/**
*/
PersistentThread::PersistentThread() :
    running({false}),
    working({false})
{

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
PersistentThread::Enqueue(const Ptr<Function<Threading::ThreadJobFunc>>& func, const Threading::ThreadFuncContext& context)
{
    this->funcs.AppendThreadSafe(func);
    this->contexts.AppendThreadSafe(context);
    this->working.exchange(true);
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
            while (this->funcs.SizeThreadSafe() > 0)
            {
                const Ptr<Function<Threading::ThreadJobFunc>>& func = this->funcs[0];
                const Threading::ThreadFuncContext& ctx = this->contexts[0];
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
    
    this->thread = Memory::New<std::thread>(proc);
    this->running.exchange(true);
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
