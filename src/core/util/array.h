#pragma once
//------------------------------------------------------------------------------
/**
	@class JARVIS::Core::Array
	
	Dynamically sized array. Uses a grow variable to increase the array size.
	
	(C) 2015 See the LICENSE file.
*/
//------------------------------------------------------------------------------
#include "mem.h"
#include <functional>
#include <algorithm>
namespace JARVIS { 
namespace Core
{
template <class TYPE>
class Array
{
public:

	/// iterator
	typedef TYPE* Iter;

	/// constructor
	Array();
	/// destructor
	virtual ~Array();
	/// move constructor
	Array(const Array<TYPE>&& rhs);

	/// assignment operator
	void operator=(const Array<TYPE>& rhs);
	/// move operator
	void operator=(const Array<TYPE>&& rhs);
	/// read-write access operator
	TYPE& operator[](uint32 index) const;

	/// resize array to have given capacity, and retains the content if it fits
	void Resize(const uint32 size);
	/// set grow size, this will cause the array to allocate 'grow' new elements each time the array needs to increase its size
	void SetGrow(const uint32 grow);

	/// add to array
	void Append(const TYPE& key);
	/// merge with other array
	void Merge(const Array<TYPE>& arr);
	/// remove from array by searching for key
	void Remove(const TYPE& key);
	/// remove from array using an iterator
	void Remove(Iter iterator);
	/// remove from array using index
	void Remove(int32 index);
	/// clear array
	void Clear();

	/// get iterator to first element
	Iter Start();
	/// get iterator to lats element
	Iter End();

	/// search for key, return index in array, or -1 if not found
	int32 Search(const TYPE& key);
	/// search for key using binary search, but only works if array is sorted.
	int32 SearchBinary(const TYPE& key);

	/// sort array
	void Sort();
	/// sort array using a special sorting function
	void Sort(const std::function<bool(const TYPE&, const TYPE&)>& func);
	
private:

	/// grow array using the grow parameter
	void Grow();
	/// shrinks array by allocating a new array which only contains size, so basically capacity becomes size
	void Shrink();

	uint32 grow;
	uint32 capacity;
	uint32 size;
	TYPE* data;
};

//------------------------------------------------------------------------------
/**
*/
template <class TYPE>
inline
Array<TYPE>::Array() :
	size(0),
	capacity(0),
	grow(8)
{
	this->data = nullptr;
}

//------------------------------------------------------------------------------
/**
*/
template <class TYPE>
inline
Array<TYPE>::~Array()
{
	if (this->data != nullptr) Memory::Free(this->data);
}

//------------------------------------------------------------------------------
/**
*/
template <class TYPE>
inline
Array<TYPE>::Array(const Array<TYPE>&& rhs)
{
	this->capacity = rhs.capacity;
	this->grow = rhs.grow;
	this->size = rhs.size;
	this->data = rhs.data;

	rhs.size = rhs.capacity = rhs.grow = 0;
	rhs.data = nullptr;
}

//------------------------------------------------------------------------------
/**
*/
template <class TYPE>
inline void
Array<TYPE>::operator=(const Array<TYPE>& rhs)
{
	if (this->data != rhs.data)
	{
		this->capacity = rhs.capacity;
		this->grow = rhs.grow;
		TYPE* buf = Memory::Alloc<TYPE>(this->capacity);
		Memory::Copy<TYPE>(rhs.data, buf, rhs.size);
		this->size = rhs.size;
	}	
}

//------------------------------------------------------------------------------
/**
*/
template <class TYPE>
inline void
Array<TYPE>::operator=(const Array<TYPE>&& rhs)
{
	this->capacity = rhs.capacity;
	this->grow = rhs.grow;
	this->size = rhs.size;
	this->data = rhs.data;

	rhs.capacity = rhs.grow = rhs.size = 0;
	rhs.data = nullptr;
}

//------------------------------------------------------------------------------
/**
*/
template <class TYPE>
inline TYPE&
Array<TYPE>::operator[](uint32 index) const
{
	j_assert(index < this->size);
	return this->data[index];
}

//------------------------------------------------------------------------------
/**
*/
template <class TYPE>
inline void
Array<TYPE>::Resize(const uint32 size)
{
	// only do something if the resize is valid
	if (this->size != size)
	{
		this->capacity = size;
		if (this->size > this->capacity) this->size = this->capacity;
		TYPE* buf = Memory::Alloc<TYPE>(size);
		j_assert(buf != nullptr);
		Memory::Copy<TYPE>(this->data, buf, this->size);
		Memory::Free(this->data);
		this->data = buf;
	}	
}

//------------------------------------------------------------------------------
/**
*/
template <class TYPE>
inline void
Array<TYPE>::SetGrow(const uint32 grow)
{
	j_assert(grow >= 0);
	this->grow = grow;
}

//------------------------------------------------------------------------------
/**
*/
template <class TYPE>
inline void
Array<TYPE>::Append(const TYPE& key)
{	
	// if we don't have any room, then we make room!
	if (this->size == this->capacity) this->Grow();
	this->data[this->size] = key;
	this->size++;
}

//------------------------------------------------------------------------------
/**
*/
template <class TYPE>
void
Array<TYPE>::Merge(const Array<TYPE>& arr)
{
	// only do this if we have two different arrays
	if (this->data != arr.data)
	{
		uint32 newCapacity = this->capacity + arr.capacity;
		TYPE* buf = Memory::Alloc<TYPE>(newCapacity);
		Memory::Copy<TYPE>(this->data, buf, this->size);
		Memory::Copy<TYPE>(arr.data, buf + this->size, arr.size);
		this->size += arr.size;
	}
}

//------------------------------------------------------------------------------
/**
*/
template <class TYPE>
inline void
Array<TYPE>::Remove(const TYPE& key)
{
	int32 index = this->Search(key);
	this->Remove(index);
}

//------------------------------------------------------------------------------
/**
*/
template <class TYPE>
inline void
Array<TYPE>::Remove(Iter iterator)
{
	j_assert(iterator != nullptr);
	this->Remove(int32(iterator - this->data));
}

//------------------------------------------------------------------------------
/**
*/
template <class TYPE>
void
Array<TYPE>::Remove(int32 index)
{
	j_assert(index >= 0 && uint32(index) < this->size);
	uint32 dist = this->size - index - 1;

	// run destructor (make sure the virtual destructor can run!
	(&this->data[index])->~TYPE();

	// if we're not at the end of the list, move the data
	if (dist > 0) Memory::Move<TYPE>(this->data + index + 1, this->data + index, dist);

	this->size--;
}

//------------------------------------------------------------------------------
/**
*/
template <class TYPE>
inline typename Array<TYPE>::Iter
Array<TYPE>::Start()
{
	return this->data;
}

//------------------------------------------------------------------------------
/**
*/
template <class TYPE>
inline typename Array<TYPE>::Iter
Array<TYPE>::End()
{
	return this->data + this->size;
}

//------------------------------------------------------------------------------
/**
*/
template <class TYPE>
int32
Array<TYPE>::Search(const TYPE& key)
{
	for (uint32 i = 0; i < this->size; i++)
	{
		if (this->data[i] == key) return i;
	}
	return -1;
}

//------------------------------------------------------------------------------
/**
*/
template <class TYPE>
int32
Array<TYPE>::SearchBinary(const TYPE& key)
{
	// lambda function which recurses the array to find the index, if none is found it simply returns -1
	std::function<int32(TYPE*, uint32, int32)> bin = [&, key](TYPE* data, uint32 range, int32 index)
	{
		uint32 halfRange = (range / 2) + 1;
		const TYPE& val = data[index];

		if (halfRange > 0)
		{
			if (val > key)		return bin(data, halfRange, index - halfRange);
			else if (val < key) return bin(data, halfRange, index + halfRange);
		}		
		return val == key ? index : -1;
	};

	return bin(this->data, this->size/2, this->size/2);	
}

//------------------------------------------------------------------------------
/**
*/
template <class TYPE>
inline void
Array<TYPE>::Sort()
{
	std::sort(this->data, this->data + this->size);
}

//------------------------------------------------------------------------------
/**
*/
template <class TYPE>
inline void
Array<TYPE>::Sort(const std::function<bool(const TYPE&, const TYPE&)>& func)
{
	std::sort(this->data, this->data + this->size, func);
}

//------------------------------------------------------------------------------
/**
*/
template <class TYPE>
void
Array<TYPE>::Grow()
{
	uint32 growSize;
	if (0 == this->capacity)
	{
		growSize = this->grow;
	}
	else
	{
		growSize = this->capacity >> 1;
		growSize = j_min(growSize, 0x3FFFFFFF);
	}

	uint32 newCapacity = this->capacity + growSize;
	TYPE* buf = Memory::Alloc<TYPE>(newCapacity);
	if (this->data != nullptr)
	{
		Memory::Copy<TYPE>(this->data, buf, this->size);
		Memory::Free(this->data);
	}	

	// run constructor on newly created elements
	for (uint32 i = this->size; i < newCapacity; i++) new (buf + i) TYPE();

	this->capacity = newCapacity;
	this->data = buf;
}

//------------------------------------------------------------------------------
/**
*/
template <class TYPE>
void
Array<TYPE>::Shrink()
{
	// only do this if the array is not full
	if (this->size != this->capacity)
	{
		uint32 newCapacity = this->size;
		TYPE* buf = Memory::Alloc<TYPE>(newCapacity);
		Memory::Copy<TYPE>(this->data, buf, this->size);
		Memory::Free(this->data);
		this->data = buf;
		this->capacity = newCapacity
	}	
}

}} // namespace JARVIS::Core