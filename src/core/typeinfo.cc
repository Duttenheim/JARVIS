//------------------------------------------------------------------------------
//  @class JARVIS::Core::TypeInfo
// 	(C) 2015 See the LICENSE file.
//------------------------------------------------------------------------------
#include "config.h"
#include "typeinfo.h"
namespace JARVIS {
namespace Core
{
    
Core::Map<uint32, TypeInfo*> TypeInfo::ClassRegistry;
//------------------------------------------------------------------------------
/**
*/
TypeInfo::TypeInfo(const char* _name, const uint32 _hash, const Constructor _ctor) :
        name(_name),
        hash(_hash),
        ctor(_ctor)
{
    // empty
}

//------------------------------------------------------------------------------
/**
*/
const TypeInfo*
TypeInfo::GetClass(const uint32 hash)
{
    j_assert(TypeInfo::ClassRegistry.Contains(hash));
    return TypeInfo::ClassRegistry[hash];
}

//------------------------------------------------------------------------------
/**
*/
bool
TypeInfo::RegisterClass(const uint32 hash, JARVIS::Core::TypeInfo* type)
{
    j_assert(!TypeInfo::ClassRegistry.Contains(hash));
    TypeInfo::ClassRegistry.Insert(hash, type);
    return true;
}

}}
