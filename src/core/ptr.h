#pragma once
//------------------------------------------------------------------------------
/**
	@class JARVIS::Core::Ptr
	
	Implements a smart pointer which keeps track of how many times it's referenced.
        Assigning a smart pointer to an object will bump the reference count.
        Assigning a valid smart pointer to nullptr will diminish the reference count.
 
	If at any point the reference count reaches 0, the object is automatically deleted.
	Classes used as a template to Ptr must inherit from Ref in order to be a Ptr valid type.
	
	(C) 2015 See the LICENSE file.
*/
//------------------------------------------------------------------------------
namespace JARVIS {
namespace Core {
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
	Ptr(Ptr<TYPE>&& rhs);
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
	Ptr(Ptr<OTHERTYPE>&& rhs)
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
	template<class OTHERTYPE> void operator=(Ptr<OTHERTYPE>&& rhs)
	{
		TYPE* p = static_cast<TYPE*>(rhs.Pointer());
		if (p != this->ptr)
		{
			if (0 != this->ptr) this->ptr->Release();
			this->ptr = p;
			rhs.ptr = nullptr;
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
	if (nullptr != this->ptr) this->ptr->Retain();
}

//------------------------------------------------------------------------------
/**
*/
template <class TYPE>
inline
Ptr<TYPE>::Ptr(Ptr<TYPE>&& rhs)
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
		if (nullptr != this->ptr) this->ptr->Release();
		this->ptr = rhs.ptr;
		if (nullptr != this->ptr) this->ptr->Retain();
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
		if (nullptr != this->ptr) this->ptr->Release();
		this->ptr = rhs;
		if (nullptr != this->ptr) this->ptr->Retain();
	}
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

}} // namespace JARVIS::Core

//------------------------------------------------------------------------------
/**
    Use name alias in order to avoid writing Core::Ptr everywhere...
*/
namespace JARVIS {
template <class TYPE>
using Ptr = Core::Ptr<TYPE>;
}
