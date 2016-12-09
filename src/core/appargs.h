#pragma once
//------------------------------------------------------------------------------
/**
	@class JARVIS::Core::AppArgs
	
    Implements a class which wraps default command line arguments into an easy to use dictionary.
	
	(C) 2016 See the LICENSE file.
*/
//------------------------------------------------------------------------------
#include "config.h"
namespace JARVIS {
namespace Core
{
class AppArgs
{
public:
    /// set args
    void Set(const char** argv, const uint32 argc);
    
    /// get flag value
    const String& Value(const String& key);
    /// get flag (returns true if it exists)
    bool Flag(const String& key);
    
private:
    Map<String, String> values;
};

//------------------------------------------------------------------------------
/**
    Reads argv and argc from standard C main functions and turns into a dictionary.
    Skips the first argument.
    @param argv The argument list passed to the function.
    @param argc The number of arguments
*/
inline void
AppArgs::Set(const char** argv, const uint32 argc)
{
    uint32 i;
    for (i = 1; i < argc; i++)
    {
        if (argv[i][0] == '-' && (i+1) < argc && argv[i+1][0] != '-')
        {
            this->values.Insert(argv[i], argv[i+1]);
            i++;
        }
        else
        {
            // this just becomes a flag
            this->values.Insert(argv[i], nullptr);
        }
    }
}

//------------------------------------------------------------------------------
/**
*/
inline const String&
AppArgs::Value(const String& key)
{
    j_assert(this->values.Contains(key));
    return this->values[key];
}

//------------------------------------------------------------------------------
/**
*/
inline bool
AppArgs::Flag(const String& key)
{
    return this->values.Contains(key);
}

}} // namespace JARVIS::Core