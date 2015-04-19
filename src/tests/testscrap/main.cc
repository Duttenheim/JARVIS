//------------------------------------------------------------------------------
/**
    @file testscrap/main.cc
    
	Main entry point for scrap test.
	
	(C) 2015 See the LICENSE file.
*/
#include "ptr.h"
#include "ref.h"
#include "config.h"
#include "util/array.h"
#include "util/string.h"
#include "rand.h"
#include <iostream>
#include <vector>
#include "enum.h"
#include "util/timer.h"

using namespace JARVIS::Core;

class Foobar : public Ref
{
	__ClassDecl(Foobar);

public:
	Foobar(uint32 i) : var(i) {};

private:
	uint32 var;
};

class Blorf : public Ref
{
	__SingletonDecl(Blorf);

	Blorf() { __SingletonCtor(); }
	~Blorf() { __SingletonDtor(); }
public:
	void Test() { printf("Hej!\n");  }
};

enum EnumTest
{
    Foo,
    Bar,
    Foob,
    Boof
};


EnumTest EnumTestFromString(const String& str)
{
    __SWITCHSTRING(str)
    {
        __FROMSTRING(Foo);
        __FROMSTRING(Bar);
        __FROMSTRING(Foob);
        __FROMSTRING(Boof);
    }
}


__SingletonDef(Blorf);

int __cdecl
main(int argc, const char** argv)
{
	Array<Ptr<Foobar>> arr;

	Ptr<Foobar> test1 = Foobar::Create(10);
	Ptr<Foobar> test2 = Foobar::Create(15);
	Ptr<Foobar> test3 = Foobar::Create(20);
	arr.Append(test1);
	arr.Append(test2);
	arr.Append(test3);

	j_assert(arr.Search(test1) >= 0);
	j_assert(arr.Search(test2) >= 0);
	j_assert(arr.Search(test3) >= 0);
	arr.Remove(arr.Search(test2));
	arr.Append(test2);

	auto sorter = [](const uint32& lhs, const uint32& rhs) -> bool { return lhs > rhs; };
	Ptr<Timer> timer = Timer::Create();
	uint32 i;

	Array<uint32> perfArr;
	timer->Start();
	perfArr.Resize(1000000);
	for (i = 0; i < 1000000; i++)
	{
		perfArr.Append(j_randis(0, 65535, i));
	}
	//std::sort(perfArr.Start(), perfArr.End(), sorter);
	perfArr.Sort(sorter);
	timer->Stop();
	printf("Time taken for custom array: %f\n", timer->Time());

	String str("Test");
	String blorf = (String)("Foobar - " + str + " - rabooF");
    
    EnumTest first = EnumTestFromString("Boof");

	std::cin.get();
	return 0;
}
