#pragma once
//------------------------------------------------------------------------------
/**
	@class JARVIS::Core::Function
	
    Encapsulates an std function bind into a ref counted object
    so that it may be added and removed from lists without losing validity.
    
    Since std::function doesn't have a copy constructor,
    this container class will handle reference counting explicitly.
	
	(C) 2015 See the LICENSE file.
 */
//------------------------------------------------------------------------------
#include <functional>
namespace JARVIS {
namespace Core
{
template<class FUNC>
class Function : public Ref
{
    __ClassDecl(Function);
public:
    /// constructor
    Function(const FUNC& func);
    /// destructor
    virtual ~Function();
    
    /// call function
    template <class... PARAMS> void Call(PARAMS&&... args) const;
    
    /// run function
    void operator()();
    
private:
    FUNC function;
};

//------------------------------------------------------------------------------
/**
*/
template <class FUNC>
Function<FUNC>::Function(const FUNC& func)
{
    this->function = func;
}

//------------------------------------------------------------------------------
/**
*/
template <class FUNC>
Function<FUNC>::~Function()
{
    // empty
}

//------------------------------------------------------------------------------
/**
*/
template <class FUNC>
template <class... PARAMS>
void
Function<FUNC>::Call(PARAMS&&... args) const
{
    this->function(args...);
}

//------------------------------------------------------------------------------
/**
*/
template <class FUNC>
void
Function<FUNC>::operator()()
{
    this->function();
}

}} // namespace JARVIS::Core