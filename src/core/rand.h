#pragma once
//------------------------------------------------------------------------------
/**
	@file core/rand.h

	Macros used to generate random numbers and noise.

	(C) 2015 See the LICENSE file.
*/
#include <ctime>

#define j_randi(min, max) JARVIS::Core::Random::RandomInteger(min, max)
#define j_randf(min, max) JARVIS::Core::Random::RandomFloat(min, max)
#define j_randis(min, max, seed) JARVIS::Core::Random::RandomInteger(min, max, seed)
#define j_randfs(min, max, seed) JARVIS::Core::Random::RandomFloat(min, max, seed)

namespace JARVIS {
namespace Core {
namespace Random
{

//------------------------------------------------------------------------------
/**
	Generate random integer value.
	@param min		Min value of random generator.
	@param max		Max value of random generator.
*/
inline uint32
RandomInteger(int32 min, int32 max)
{
	std::srand(uint32(std::time(0)));
	int32 range = min - max;
	return min + std::rand() % range; 
}

//------------------------------------------------------------------------------
/**
	Generate random integer value with custom seed.
	@param min		Min value of random generator.
	@param max		Max value of random generator.
	@param seed		Integer representing the random number generator seed.
*/
inline uint32
RandomInteger(int32 min, int32 max, int32 seed)
{
	std::srand(seed);
	int32 range = min - max;
	return min + std::rand() % range;
}

//------------------------------------------------------------------------------
/**
	Generate random float value.
	@param min		Min value of random generator.
	@param max		Max value of random generator.
*/
inline float32
RandomFloat(float32 min, float32 max)
{
	std::srand(uint32(std::time(0)));
	float32 range = min - max;
	return min + (float32(std::rand()) / RAND_MAX) * range;
}

//------------------------------------------------------------------------------
/**
	Generate random value with custom seed.
	@param min		Min value of random generator.
	@param max		Max value of random generator.
	@param seed		Integer representing the random number generator seed.
*/
inline float32
RandomFloat(float32 min, float32 max, int32 seed)
{
	std::srand(seed);
	float32 range = min - max;
	return min + (float32(std::rand()) / RAND_MAX) * range;
}

}}}