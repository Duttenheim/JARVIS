#pragma once
//------------------------------------------------------------------------------
/**
	@class JARVIS::Core::TypeInfo
	
    Small RTTI-container class used by the JARVIS class system
	
	(C) 2015 See the LICENSE file.
 */
//------------------------------------------------------------------------------
#include "util/map.h"
#include "util/string.h"
namespace JARVIS {
namespace Core
{
struct TypeInfo
{
    typedef Core::Ref* (*Constructor)();
    
    /// constructor
    TypeInfo(const char* _name, const uint32 _hash, Constructor _ctor);
    
    /// retrieve type info struct by using class hash
    static const TypeInfo* GetClass(const uint32 hash);
    /// register class with global lookup table
    static bool RegisterClass(const uint32 hash, TypeInfo* type);
    
    Core::String name;
    uint32 hash;
    Constructor ctor;
    static Core::Map<uint32, TypeInfo*> ClassRegistry;
};

}} // namespace JARVIS::Core