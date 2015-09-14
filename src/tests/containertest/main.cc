//------------------------------------------------------------------------------
/**
    @file testscrap/main.cc
    
	Main entry point for scrap test.
	
	(C) 2015 See the LICENSE file.
*/
#include "config.h"
#include "util/array.h"
#include "util/string.h"
#include "util/map.h"
#include "enum.h"
#include "util/timer.h"
#include "application.h"
#include "header1.h"
#include <iostream>
#include <vector>
#include <map>

using namespace JARVIS::Core;

JARVIS_MAIN
{
	Ptr<Timer> timer = Timer::Create();
	uint32 i;
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
    
	std::cin.get();
	return 0;
}
