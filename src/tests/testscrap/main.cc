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
	Array<std::function<void()>> arr;
	uint32 foobar = 5;
	std::function<void()> proc = [&]() { printf("Hej! %d", foobar); };
	arr.Append([&]() { printf("Hej! %d", foobar); });
	arr.Append([&]() { printf("Hej då! %d", foobar); });
	arr.RemoveIndex(0);
	arr.RemoveIndex(0);

	std::cin.get();
	return 0;
}
