#pragma once
//------------------------------------------------------------------------------
/**
	@class JARVIS::Core::Function
	
    Encapsulates an std function bind into a ref counted object
    so that it may be added and removed from lists without losing validity.
    
	This wraps an std::function but without having to use another 
	template do describe itself as containing a function, which results in a cleaner
	initialization of the class.

	Instead of writing Function<std::function<void()>> we can instead just write Function<void()>
	and get it as a refcounted function container. 
	
	Instantiate this class by using the std::function syntax, and using Create to feed it a lambda function.
	Example:
		Ptr<Function<void()>> func = Function<void()>::Create([]() { printf("Reference counted lambda function!"); });
		func->Call();
	
	(C) 2015 See the LICENSE file.
 */
//------------------------------------------------------------------------------
#include <functional>
namespace JARVIS {
namespace Core
{
template <class>
class Function;

template<class RET, class... PARAMS> 
class Function<RET(PARAMS...)> : public Ref
{
	__ClassDecl(Function);
public:
    /// default constructor
    Function();
	/// constructor from function
	template <class FUNC> Function(FUNC rhs);
	/// destructor
	virtual ~Function();
    
    /// assignment operator from function
    template <class FUNC> void operator=(FUNC rhs);
    /// move operator from function
    template <class FUNC> void operator=(FUNC&& rhs);

	/// call function
	template <class... ARGS> void Call(ARGS&&... args) const;

private:
	std::function<RET(PARAMS...)> func;
};

//------------------------------------------------------------------------------
/**
*/
template<class RET, class... PARAMS>
Function<RET(PARAMS...)>::Function()
{
    // empty
}

//------------------------------------------------------------------------------
/**
*/
template<class RET, class... PARAMS>
template<class FUNC>
Function<RET(PARAMS...)>::Function(FUNC rhs)
{
    this->func = rhs;
}

//------------------------------------------------------------------------------
/**
*/
template<class RET, class... PARAMS>
Function<RET(PARAMS...)>::~Function()
{
    // empty
}

//------------------------------------------------------------------------------
/**
*/
template<class RET, class... PARAMS>
template<class FUNC>
void
Function<RET(PARAMS...)>::operator=(FUNC rhs)
{
    this->func = rhs;
}

//------------------------------------------------------------------------------
/**
*/
template<class RET, class... PARAMS>
template<class FUNC>
void
Function<RET(PARAMS...)>::operator=(FUNC&& rhs)
{
    this->func = rhs;
    rhs = nullptr;
}

//------------------------------------------------------------------------------
/**
*/
template<class RET, class... PARAMS>
template <class... ARGS>
void
Function<RET(PARAMS...)>::Call(ARGS&&... args) const
{
	this->func(args...);
}

}} // namespace JARVIS::Core