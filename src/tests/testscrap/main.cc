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
#include "util/map.h"
#include "rand.h"
#include <iostream>
#include <vector>
#include <map>
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

class NoDefaultConstructor
{
	NoDefaultConstructor(int32 i) {};
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
		__DEFAULT(Foo);
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
		uint32 index = 1000000 / 2;
		if (dict.Contains(index))
		{
			String foo = dict[index];
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
	printf("Dynamic realloc and sort per element insert took: %f\n", timer->Time());

	std::cin.get();
	return 0;
}
