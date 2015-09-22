//------------------------------------------------------------------------------
/**
    @file testscrap/main.cc
    
	Main entry point for scrap test.
	
	(C) 2015 See the LICENSE file.
*/
#include "config.h"
#include "functional/function.h"
#include "util/array.h"
#include "util/string.h"
#include "threads/thread.h"
#include "threads/persistentthread.h"
#include "threads/threadpool.h"
#include "application.h"
#include <iostream>

using namespace JARVIS::Core;


JARVIS_MAIN
{    
    Ptr<Thread> thread = Thread::Create();
    auto threadProc = Functional::Lambda([]()
    {
        printf("Hej!\n");
    });
    thread->Start(threadProc);
    thread->Wait();

	byte* inputs = (byte*)String("Inputs").CharPtr();
	byte* outputs = (byte*)String("Outputs").CharPtr();
	byte* uniforms = (byte*)String("Uniforms").CharPtr();
   
    /*
    Ptr<Threading::ThreadJobFunc> specialThreadProc =
	Threading::ThreadJobFunc::Create([](byte* input, byte* output, byte* uniform) -> void
	{
        printf("Hej från specialfunktion!\n");
    });
    */
    auto f = Function<void(byte* input, byte* output, byte* uniform)>::Create([](byte* input, byte* output, byte* uniform){});

    auto specialThreadProc = Functional::Lambda([](byte* input, byte* output, byte* uniform) -> void
	{
        printf("Hej från specialfunktion!\n");
    });
    
    // create a persistent thread which will be a lightweight workhorse
    auto ctx = Threading::ThreadJobContext{inputs, outputs, uniforms};
    Ptr<PersistentThread> pthread = PersistentThread::Create();
    pthread->Start();
    pthread->Enqueue(specialThreadProc, ctx);
    pthread->Enqueue(specialThreadProc, ctx);
    pthread->Enqueue(specialThreadProc, ctx);
    pthread->Enqueue(specialThreadProc, ctx);
    while (pthread->Working());

    // create a pool of 16 threads which can all be enqueued.
    // threads will quit when the job is done.
	Ptr<ThreadPool> pool = ThreadPool::Create(16);
	uint32 i;
	for (i = 0; i < 16; i++)
	{
		// create bogus job
		auto poolProc1 = Threading::ThreadJobFunc::Create([=](byte* input, byte* output, byte* uniform)
		{
			printf("Pool job #%d\n", i);
		});
		pool->Enqueue(poolProc1, ctx);
	}
	pool->Update();
    printf("Färdig!\n");

	std::cin.get();
	return 0;
}
