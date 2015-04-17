#pragma once
//------------------------------------------------------------------------------
/**
	@class JARVIS::Core::Ptr
	
	Implements a smart pointer which decrease and increase its internal reference count.
	The smart pointer internally keeps track of the total ref count, and if it reaches 0 performs an automatic delete.

	Classes used as a template to Ptr must inherit from Ref in order for it to compile.

	This class is outside the namespace because it will look annyoing 
	
	(C) 2015 See the LICENSE file.
*/
//------------------------------------------------------------------------------
#include "config.h"
template <class TYPE>
class Ptr
{
public:
	/// constructor
	Ptr();
	/// destructor
	virtual ~Ptr();
	/// copy constructor
	Ptr(const Ptr<TYPE>& rhs);
	/// move constructor
	Ptr(const Ptr<TYPE>&& rhs);
	/// copy constructor from raw pointer
	Ptr(TYPE* rhs);

	/// copy constructor from smart pointer of other type
	template<class OTHERTYPE> 
	Ptr(const Ptr<OTHERTYPE>& rhs)
	{
		TYPE* p = static_cast<TYPE*>(rhs.Pointer());
		this->ptr = p;
		if (nullptr != this->ptr) this->ptr->Retain();
	}

	/// copy constructor from c pointer of other type
	template<class OTHERTYPE>
	Ptr(OTHERTYPE* rhs)
	{
		TYPE* p = static_cast<TYPE*>(rhs);
		this->ptr = p;
		if (nullptr != this->ptr) this->ptr->Retain();
	}

	/// move constructor from smart pointer of other type
	template<class OTHERTYPE> 
	Ptr(const Ptr<OTHERTYPE>&& rhs)
	{
		this->ptr = static_cast<TYPE*>(rhs.Pointer());
		rhs.ptr = nullptr;
	}
	
	/// assignment operator
	void operator=(const Ptr<TYPE>& rhs);
	/// assign with nullptr
	void operator=(std::nullptr_t);
	/// assignment operator for c pointer
	void operator=(TYPE* rhs);
	/// test if invalid (against nullptr)
	bool operator==(std::nullptr_t) const;
	/// test if valid (against nullptr)
	bool operator!=(std::nullptr_t) const;

	/// standard equality operator
	bool operator==(const Ptr<TYPE>& rhs);
	/// standard non-equality operator
	bool operator!=(const Ptr<TYPE>& rhs);

	/// assignment operator for smart pointer of other type
	template<class OTHERTYPE> void operator=(const Ptr<OTHERTYPE>& rhs)
	{
		TYPE* p = static_cast<TYPE*>(rhs.Pointer());
		if (p != this->ptr)
		{
			if (0 != this->ptr) this->ptr->Release();
			this->ptr = p;
			if (0 != this->ptr) this->ptr->Retain();
		}
	}

	/// assignment operator for smart pointer of other type
	template<class OTHERTYPE> void operator=(const Ptr<OTHERTYPE>&& rhs)
	{
		TYPE* p = static_cast<TYPE*>(rhs.Pointer());
		if (p != this->ptr)
		{
			if (0 != this->ptr) this->ptr->Release();
			this->ptr = p;
			rhs->ptr = nullptr;
		}
	}

	/// assignment operator for c pointer of other type
	template<class OTHERTYPE> void operator=(OTHERTYPE* rhs)
	{
		TYPE* p = static_cast<TYPE*>(rhs);
		if (p != this->ptr)
		{
			if (0 != this->ptr) this->ptr->Release();
			this->ptr = p;
			if (0 != this->ptr) this->ptr->Retain();
		}
	}

	/// returns true if ptr is not null
	bool Valid() const;
	/// returns direct reference to pointer (not recommended
	TYPE* Pointer() const;

	/// arrow operator
	TYPE* operator->() const;
	/// dereference operator
	TYPE& operator*() const;
	/// bool operator, useful if we do for example if(ptr)
	explicit operator bool() const;

private:
	TYPE* ptr;
};

//------------------------------------------------------------------------------
/**
*/
template <class TYPE>
inline
Ptr<TYPE>::Ptr() :
	ptr(nullptr)
{
	// empty
}

//------------------------------------------------------------------------------
/**
*/
template <class TYPE>
inline
Ptr<TYPE>::Ptr(const Ptr<TYPE>& rhs) :
	ptr(rhs.ptr)
{
	if (0 != this->ptr) this->ptr->Retain();
}

//------------------------------------------------------------------------------
/**
*/
template <class TYPE>
inline
Ptr<TYPE>::Ptr(const Ptr<TYPE>&& rhs)
{
	this->ptr = rhs.ptr;
	rhs.ptr = nullptr;
}

//------------------------------------------------------------------------------
/**
*/
template <class TYPE>
inline
Ptr<TYPE>::Ptr(TYPE* rhs) :
	ptr(rhs)
{
	if (nullptr != this->ptr) this->ptr->Retain();
}

//------------------------------------------------------------------------------
/**
*/
template <class TYPE>
inline 
Ptr<TYPE>::~Ptr()
{
	if (nullptr != this->ptr)
	{
		this->ptr->Release();
		this->ptr = 0;
	}
}

//------------------------------------------------------------------------------
/**
*/
template <class TYPE>
inline void
Ptr<TYPE>::operator=(const Ptr<TYPE>& rhs)
{
	if (this->ptr != rhs.ptr)
	{
		if (this->ptr) this->ptr->Release();
		this->ptr = rhs.ptr;
		if (this->ptr) this->ptr->Retain();
	}
}

//------------------------------------------------------------------------------
/**
*/
template <class TYPE>
inline void
Ptr<TYPE>::operator=(std::nullptr_t)
{
	if (nullptr != this->ptr)
	{
		this->ptr->Release();
		this->ptr = nullptr;
	}
}

//------------------------------------------------------------------------------
/**
*/
template <class TYPE>
inline void
Ptr<TYPE>::operator=(TYPE* rhs)
{
	if (this->ptr != rhs)
	{
		if (this->ptr) this->ptr->Release();
		this->ptr = rhs;
		if (this->ptr) = this->ptr->Retain();
	}
}

//------------------------------------------------------------------------------
/**
*/
template <class TYPE>
inline bool
Ptr<TYPE>::operator==(std::nullptr_t) const
{
	return this->ptr == nullptr;
}

//------------------------------------------------------------------------------
/**
*/
template <class TYPE>
inline bool
Ptr<TYPE>::operator!=(std::nullptr_t) const
{
	return this->ptr != nullptr;
}

//------------------------------------------------------------------------------
/**
*/
template <class TYPE>
bool
Ptr<TYPE>::operator==(const Ptr<TYPE>& rhs)
{
	return this->ptr == rhs.ptr;
}

//------------------------------------------------------------------------------
/**
*/
template <class TYPE>
bool
Ptr<TYPE>::operator!=(const Ptr<TYPE>& rhs)
{
	return this->ptr != rhs.ptr;
}

//------------------------------------------------------------------------------
/**
*/
template <class TYPE>
inline bool
Ptr<TYPE>::Valid() const
{
	return nullptr != this->ptr;
}

//------------------------------------------------------------------------------
/**
*/
template <class TYPE>
inline TYPE*
Ptr<TYPE>::Pointer() const
{
	return this->ptr;
}


//------------------------------------------------------------------------------
/**
*/
template <class TYPE>
inline TYPE*
Ptr<TYPE>::operator->() const
{
	j_assert(this->ptr != nullptr);
	return this->ptr;
}

//------------------------------------------------------------------------------
/**
*/
template <class TYPE>
inline TYPE&
Ptr<TYPE>::operator*() const
{
	j_assert(this->ptr != nullptr);
	return *this->ptr;
}

//------------------------------------------------------------------------------
/**
*/
template <class TYPE>
inline 
Ptr<TYPE>::operator bool() const
{
	return nullptr != this->ptr;
}