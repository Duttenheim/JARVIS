#pragma once
#include <atomic>
//------------------------------------------------------------------------------
/**
	@class JARVIS::Core::Ref
	
	Implements a class with reference counting.
	This serves as a base class for every class which should be used as a pointer.
	
	(C) 2015 See the LICENSE file.
*/
//------------------------------------------------------------------------------
namespace JARVIS { 
namespace Core
{
class Ref
{
public:
	/// constructor
	Ref();

	/// bump ref count
	void Retain();
	/// decrease ref count
	void Release();
    
protected:
    /// destructor
	virtual ~Ref();
    
    /// destroy reference
    virtual void Destroy();
private:
	std::atomic<uint32> ref{0};
};

//------------------------------------------------------------------------------
/**
*/
inline
Ref::Ref()
{
	// empty
}

//------------------------------------------------------------------------------
/**
*/
inline 
Ref::~Ref()
{
	j_assert(this->ref.load(std::memory_order_relaxed) == 0);
}

//------------------------------------------------------------------------------
/**
*/
inline void
Ref::Retain()
{
	this->ref.fetch_add(1, std::memory_order_relaxed);
}

//------------------------------------------------------------------------------
/**
*/
inline void
Ref::Release()
{
	if (1 == this->ref.fetch_sub(1, std::memory_order_relaxed)) this->Destroy();
}

//------------------------------------------------------------------------------
/**
*/
inline void
Ref::Destroy()
{
    this->~Ref();
    Core::Memory::Free(this);
}

}} // namespace JARVIS::Core