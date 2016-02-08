#pragma once
//------------------------------------------------------------------------------
/**
	@class JARVIS::Core::Assigns
	
    Holds a static list of assigns which is used to resolve relative paths.
	
	(C) 2015 See the LICENSE file.
*/
//------------------------------------------------------------------------------
#include "util/string.h"
namespace JARVIS {
namespace Core
{
class Assigns
{
public:
    /// constructor
    Assigns();
    /// destructor
    virtual ~Assigns();
    
    /// register assignment, replaces any old assignments made
    static void NewAssignment(const Core::String& key, const Core::String& value);
    /// request assignment, returns original if none is found
    static const Core::String& Resolve(const Core::String& key);
    
private:
    static Core::Map<Core::String, Core::String> assignRegistry;
};

//

//------------------------------------------------------------------------------
/**
*/
inline void
Assigns::NewAssignment(const Core::String& key, const Core::String& value)
{
    if (Assigns::assignRegistry.Contains(key)) Assigns::assignRegistry.Remove(key);
    Assigns::assignRegistry.Insert(key, value);
}

//------------------------------------------------------------------------------
/**
*/
inline const Core::String&
Assigns::Resolve(const Core::String &key)
{
    if (!Assigns::assignRegistry.Contains(key)) return key;
    else
    {
        return Assigns::assignRegistry[key];
    }
}

}} // namespace JARVIS::Core