//------------------------------------------------------------------------------
/**
    @file testscrap/main.cc
    
	Main entry point for scrap test.
	
	(C) 2015 See the LICENSE file.
*/
#include "config.h"
#include "functional/function.h"
#include "util/array.h"
#include "application.h"
#include <iostream>
#include <vector>
#include <map>

using namespace JARVIS::Core;

JARVIS_MAIN
{
	Array<std::function<void()>> arr;
    Ptr<Function<void()>> blorf = Function<void()>::Create([]() { printf("BLORF\n"); });
    blorf->Call();
    Ptr<Function<void()>> florb = Function<void()>::Create([]() { printf("FLORB\n"); });
    florb->Call();
    blorf = florb;
    blorf->Call();
    florb->Call();
	uint32 foobar = 5;
	std::function<void()> proc = [&]() { printf("Hej! %d", foobar); };
	arr.Append([&]() { printf("Hej! %d", foobar); });
	arr.Append([&]() { printf("Hej då! %d", foobar); });
	arr.RemoveIndex(0);
	arr.RemoveIndex(0);

	std::cin.get();
	return 0;
}
