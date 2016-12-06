#pragma once
//------------------------------------------------------------------------------
/**
    @file core/class.h
    
	Class macros.
    
    --------------------- __ClassDecl ---------------------
    To generate a class which can be used with smart pointers, use the __ClassDecl macro in the class header.
    
    --------------------- __ClassPoolDecl ---------------------
    Equivalent with __ClassDecl, except it implements a pool based allocator which is then used to instanciate
    objects through Create or CreateBase. Requires the __Pool macro to be used in order to instanciate 
    a pool allocator for said class.

    --------------------- __Ptr ---------------------
    For convenience, one can also use the __Ptr macro to define a smart pointer to said type to be <type>Ptr.
    This is just to avoid having to type Ptr<type>, which is nice if a class gets used frequently. Example:
    
    Ptr<Window> can be expressed as WindowPtr.
 
    --------------------- __RTTI ---------------------
    To generate a class which has a dynamic RTTI lookup, and which can be created using a
    hashed class name, use the __RTTI macro in the class definition file (.cc). This will
    enable the serialization and construction of a class based on an uint32, although
    it also requires the object to have a default constructor.
    
    Recommended to have support for constexpr, which allows the type info stuff to be
    generated at compile time.
 
    --------------------- __Pool ---------------------
    Required for pool allocated objects. Put a __Pool declaration in the compile unit corresponding
    to the class for which a pool should be used.
 
	(C) 2015 See the LICENSE file.
*/
#include "ref.h"
#include "typeinfo.h"

namespace JARVIS {
namespace Core {
template<class FIRST, class SECOND>
CONST_EXPR bool IsDerived()
{
    return std::is_base_of<SECOND, FIRST>::value;
}
}}

#define __Ptr(type) \
    using type##Ptr = Ptr<type>; \

#define __InheritanceCompare(type) \
    template<class OTHER> \
    static CONST_EXPR bool IsDerived() \
    { \
        return std::is_base_of<OTHER, type>::value; \
    } \
    template<class OTHER> \
    static CONST_EXPR bool IsBase() \
    { \
        return std::is_base_of<type, OTHER>::value; \
    }

#define __ClassDecl(type) \
	public: \
	template<class... ARGS> \
	static type* Create(ARGS&&... args) \
	{ \
		return new type(args...); \
	} \
    template<class... ARGS> \
    static Core::Ref* CreateBase(ARGS&&... args) \
    { \
        return new type(args...); \
    } \
    protected: \
    virtual void Destroy() \
    { \
        this->~type(); \
        Core::Memory::Free(this); \
    } \
    public: \
    static Core::TypeInfo RTTI; \
    static CONST_EXPR uint32 Hash() \
    { \
        return JARVIS::Core::__StringHash(#type);\
    } \
    __InheritanceCompare(type)

#define __ClassDeclPool(type) \
    private: \
    static Core::PoolAlloc<type, 256, 256> __pool; \
	public: \
	template<class... ARGS> \
	static type* Create(ARGS&&... args) \
	{ \
		return __pool.Create(std::forward<ARGS>(args)...); \
	} \
    template<class... ARGS> \
    static Core::Ref* CreateBase(ARGS&&... args) \
    { \
		return __pool.Create(std::forward<ARGS>(args)...); \
    } \
    protected: \
    virtual void Destroy() override\
    { \
       __pool.Destroy(this); \
    } \
    public: \
    static Core::TypeInfo RTTI; \
    static CONST_EXPR uint32 Hash() \
    { \
        return JARVIS::Core::__StringHash(#type);\
    } \
    __InheritanceCompare(type)

#define __RTTI(type) \
    Core::TypeInfo type::RTTI(#type, __StringHash(#type), type::CreateBase); \
    static const bool type_registered = Core::TypeInfo::RegisterClass(__StringHash(#type), &type::RTTI); \

#define __Pool(type) \
    Core::PoolAlloc<type, 256, 256> type::__pool; \
    