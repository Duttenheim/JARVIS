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

namespace JARVIS {
class PoolTest : public Core::Ref
{
    __ClassDeclPool(PoolTest);
    
    /// constructor
    PoolTest(int32 a, int32 b, int32 c) : a(a), b(b), c(c){};
private:
        int32 a, b, c;
};
__Pool(PoolTest);
}

enum Test
{
    A,
    B,
    C,
    D
};

Test SwitchTestString(const char* name)
{
    __SWITCHSTRING(name)
    {
        __FROMSTRING(Test::A);
        __FROMSTRING(Test::B);
        __FROMSTRING(Test::C);
        __FROMSTRING(Test::D);
        __DEFAULT(Test::A);
    }
}

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

    Ptr<JARVIS::PoolTest> p1 = JARVIS::PoolTest::Create(1, 2, 3);
    Ptr<JARVIS::PoolTest> p2 = JARVIS::PoolTest::Create(4, 5, 6);
    Ptr<JARVIS::PoolTest> p3 = JARVIS::PoolTest::Create(1, 2, 3);
    Ptr<JARVIS::PoolTest> p4 = JARVIS::PoolTest::Create(4, 5, 6);
    
    p1 = nullptr;
    p2 = nullptr;
    p3 = nullptr;
    p4 = nullptr;
    
 

	std::cin.get();
	return 0;
}
