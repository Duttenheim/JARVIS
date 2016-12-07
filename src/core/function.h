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
        
    One can also create a pointer to a function lambda using the Lambda constructor function.
	
	(C) 2015 See the LICENSE file.
 */
//------------------------------------------------------------------------------
#include <functional>

namespace JARVIS {
namespace Core
{

template <class LAMBDA>
class Function;

template<class RET, class... PARAMS> 
class Function<RET(PARAMS...)> : public Ref
{
	__ClassDecl(Function);
public:
    /// default constructor
    Function();
	/// constructor from function
	Function(const Function<RET(PARAMS...)>& rhs);
    /// constructor from std function
    Function(const std::function<RET(PARAMS...)>& rhs);
	/// destructor
	virtual ~Function();
    
    /// assignment operator from function
    void operator=(const Function<RET(PARAMS...)>& rhs);
    /// move operator from function
    void operator=(Function<RET(PARAMS...)>&& rhs);
    
    /// compare if function is null pointer
    const bool operator==(std::nullptr_t ptr) const;
    /// compare if function is not null pointer
    const bool operator!=(std::nullptr_t ptr) const;

	/// call function
	template <class... ARGS> void Call(ARGS&&... args) const;
    /// call operator
    template <class... ARGS> void operator()(ARGS&&... args) const;

private:
	std::function<RET(PARAMS...)> func;
};


namespace Functional
{

// use templates to extract lambda signature
template<typename T>
struct __function_traits : __function_traits<decltype(&T::operator())>
{
};

// used if we create lambdas from existing functions
template<class RET, class... ARGS>
struct __function_traits<RET(*)(ARGS...)>
{
    typedef Core::Function<RET(ARGS...)> type;
};

// this one for lambdas who are members of classes with constant members
template<class CLASS, class RET, class... ARGS>
struct __function_traits<RET(CLASS::*)(ARGS...) const>
{
    typedef Core::Function<RET(ARGS...)> type;
};

// this one for lambdas who are members of classes with non-constant members
template<class CLASS, class RET, class... ARGS>
struct __function_traits<RET(CLASS::*)(ARGS...)>
{
    typedef Core::Function<RET(ARGS...)> type;
};

//------------------------------------------------------------------------------
/**
    Create a lambda function using our refcounted Function object 
    by using an alias to save the type and use it to run the constructor.
    
    This allows us to create a smart pointer to a function object by just calling this
    static constructor. For example:
    
    auto func = Core::Functional::Lambda([]()
    {
 
    });

    func is now a Ptr<Core::Function<void()>>.
    
    Booyah.
*/
template<class LAMBDA>
Ptr<typename __function_traits<LAMBDA>::type> Lambda(LAMBDA func)
{
    using ty = typename __function_traits<LAMBDA>::type;
    return ty::Create(func);
}

} // namespace Functional

//------------------------------------------------------------------------------
/**
*/
template<class RET, class... PARAMS>
inline
Function<RET(PARAMS...)>::Function()
{
    // empty
}

//------------------------------------------------------------------------------
/**
*/
template<class RET, class... PARAMS>
inline
Function<RET(PARAMS...)>::Function(const Function<RET(PARAMS...)>& rhs)
{
    this->func = rhs.func;
}

//------------------------------------------------------------------------------
/**
*/
template<class RET, class... PARAMS>
inline
Function<RET(PARAMS...)>::Function(const std::function<RET(PARAMS...)>& rhs)
{
    this->func = rhs;
}

//------------------------------------------------------------------------------
/**
*/
template<class RET, class... PARAMS>
inline
Function<RET(PARAMS...)>::~Function()
{
    this->func = nullptr;
}

//------------------------------------------------------------------------------
/**
*/
template<class RET, class... PARAMS>
inline void
Function<RET(PARAMS...)>::operator=(const Function<RET(PARAMS...)>& rhs)
{
    this->func = rhs;
}

//------------------------------------------------------------------------------
/**
*/
template<class RET, class... PARAMS>
inline void
Function<RET(PARAMS...)>::operator=(Function<RET(PARAMS...)>&& rhs)
{
    this->func = rhs;
    rhs = nullptr;
}

//------------------------------------------------------------------------------
/**
*/
template<class RET, class... PARAMS>
inline const bool
Function<RET(PARAMS...)>::operator==(std::nullptr_t ptr) const
{
    return this->func == nullptr;
}

//------------------------------------------------------------------------------
/**
*/
template<class RET, class... PARAMS>
inline const bool
Function<RET(PARAMS...)>::operator!=(std::nullptr_t ptr) const
{
    return this->func != nullptr;
}

//------------------------------------------------------------------------------
/**
*/
template<class RET, class... PARAMS>
template <class... ARGS>
inline void
Function<RET(PARAMS...)>::Call(ARGS&&... args) const
{
	this->func(args...);
}


//------------------------------------------------------------------------------
/**
*/
template<class RET, class... PARAMS>
template <class... ARGS>
inline void
Function<RET(PARAMS...)>::operator()(ARGS&&... args) const
{
	this->func(args...);
}

}} // namespace JARVIS::Core