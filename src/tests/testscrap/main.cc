//------------------------------------------------------------------------------
/**
    @file testscrap/main.cc
    
	Main entry point for scrap test.
	
	(C) 2015 See the LICENSE file.
*/
#include "config.h"
#include "ptr.h"
#include "functional/function.h"
#include "util/array.h"
#include "util/string.h"
#include "util/map.h"
#include "threads/thread.h"
#include "threads/persistentthread.h"
#include "rand.h"
#include <iostream>
#include <vector>
#include <map>
#include "enum.h"
#include "util/timer.h"
#include "threads/threadpool.h"

using namespace JARVIS::Core;

int __cdecl
main(int argc, const char** argv)
{
	Ptr<Timer> timer = Timer::Create();
	uint32 i;

	/*
	Array<uint32> perfArr;
	timer->Start();
	for (i = 0; i < 1000000; i++)
	{
		perfArr.Append(j_randis(0, 65535, i));
	}
	timer->Stop();
	printf("Time taken for custom array: %f\n", timer->Time());
	*/
	Map<uint32, String> dict;

	printf("--- Custom dictionary ---\n");
	timer->Start();
	for (i = 0; i < 1000000; i++)
	{
		dict.Insert(i, "Foobar");
	}
	timer->Stop();
	printf("Dynamic realloc and sort per element insert took: %f\n", timer->Time());

	// clear
	dict.Clear();

	timer->Start();
	dict.Resize(1000000);
	for (i = 0; i < 1000000; i++)
	{
		dict.Insert(i, "Foobar");
	}
	timer->Stop();
	printf("Static alloc and sort per element insert took: %f\n", timer->Time());

	dict.Clear();

	timer->Start();
	dict.BeginMassInsertion();
	for (i = 0; i < 1000000; i++)
	{
		dict.InsertUnordered(i, "Foobar");
	}
	dict.EndMassInsertion();
	timer->Stop();
	printf("Dynamic realloc and mass insertion took: %f\n", timer->Time());

	dict.Clear();

	timer->Start();
	dict.Resize(1000000);
	dict.BeginMassInsertion();
	for (i = 0; i < 1000000; i++)
	{
		dict.InsertUnordered(i, "Foobar");
	}
	dict.EndMassInsertion();
	timer->Stop();
	printf("Static alloc and mass insertion took: %f\n", timer->Time());

	timer->Start();
	for (i = 0; i < 1000000; i++)
	{
		if (dict.Contains(i))
		{
			String foo = dict[i];
		}
	}
	timer->Stop();
	printf("Lookups took: %f\n", timer->Time());

	printf("\n\n");

	std::map<uint32, String> map;
	printf("--- std dictionary ---\n");
	timer->Start();
	for (i = 0; i < 1000000; i++)
	{
		map[i] = "Foobar";
	}
	timer->Stop();
	printf("Insertions took: %f\n", timer->Time());
    
    timer->Start();
    for (i = 0; i < 1000000; i++)
    {
        if (map.find(i) != map.end())
        {
            String foo = map[i];
        }
    }
    timer->Stop();
    printf("Lookups took: %f\n", timer->Time());
    
    Ptr<Thread> thread = Thread::Create();
    Ptr<Function<void()>> threadProc = Function<void()>::Create([]()
    {
        printf("Hej!\n");
    });
    thread->Start(threadProc);
    thread->Wait();
	//while (thread->Running());
	//thread->Stop();


	byte* inputs = (byte*)String("Inputs").CharPtr();
	byte* outputs = (byte*)String("Outputs").CharPtr();
	byte* uniforms = (byte*)String("Uniforms").CharPtr();
   
    Ptr<Threading::ThreadJobFunc> specialThreadProc =
	Threading::ThreadJobFunc::Create([](byte* input, byte* output, byte* uniform) -> void
	{
        printf("Hej från specialfunktion!\n");
    });
    
    auto ctx = Threading::ThreadJobContext{inputs, outputs, uniforms};
	thread->Start(specialThreadProc, inputs, outputs, uniforms);
    
    Ptr<PersistentThread> pthread = PersistentThread::Create();
    pthread->Start();
    pthread->Enqueue(specialThreadProc, ctx);
    pthread->Enqueue(specialThreadProc, ctx);
    pthread->Enqueue(specialThreadProc, ctx);
    pthread->Enqueue(specialThreadProc, ctx);
    while (pthread->Working());
    printf("Färdig!\n");

	std::cin.get();
	return 0;
}
