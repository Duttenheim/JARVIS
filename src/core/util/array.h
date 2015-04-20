#pragma once
//------------------------------------------------------------------------------
/**
	@class JARVIS::Core::Array
	
	Dynamically sized array. Increases array size by doubling the capacity.
	Can be resized so that appends doesn't modify its size.

	Supports sorting using std::sort, and also with a custom comparison function lambda.
	Uses element caching to save the last searched for index, which makes searching for the same value instant.
	
	(C) 2015 See the LICENSE file.
*/
//------------------------------------------------------------------------------
#include "mem.h"
#include <functional>
#include <algorithm>

#define JARVIS_CACHED_ELEMENT 1

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
	TYPE& operator[](const uint32 index);
	/// read-only access operator
	const TYPE& operator[](const uint32 index) const;

	/// resize array to have given capacity, and retains the content if it fits
	void Resize(const uint32 size);
	/// set grow size, this will cause the array to allocate 'grow' new elements each time the array needs to increase its size
	void SetGrow(const uint32 grow);

	/// add to array
	void Append(const TYPE& val);
	/// add to array at a specific index
	void Insert(const TYPE& val, uint32 index);
	/// add to array, but make sure that the array retains sorting
	void InsertOrdered(const TYPE& val);
	/// merge with other array
	void Merge(const Array<TYPE>& arr);
	/// remove from array by searching for key
	void Remove(const TYPE& key);
	/// remove from array using an iterator
	void Remove(Iter iterator);
	/// remove from array using index
	void Remove(uint32 index);
	/// clear array
	void Clear();

	/// get iterator to first element
	Iter Start() const;
	/// get iterator to lats element
	Iter End() const;
	/// get size of array
	const uint32 Size() const;

	/// search for key, return index in array, or -1 if not found
	int32 Search(const TYPE& key);
	/// search for key using binary search, but only works if array is sorted. Returns -1 if no such element is found.
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
#if JARVIS_CACHED_ELEMENT
	TYPE* cachedElement;
#endif
};

//------------------------------------------------------------------------------
/**
*/
template <class TYPE>
inline
Array<TYPE>::Array() :
	grow(8),
    capacity(0),
    size(0)
#if JARVIS_CACHED_ELEMENT
	,cachedElement(nullptr)
#endif
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
Array<TYPE>::operator[](const uint32 index)
{
	j_assert(index < this->size);
	return this->data[index];
}

//------------------------------------------------------------------------------
/**
*/
template <class TYPE>
inline const TYPE&
Array<TYPE>::operator[](const uint32 index) const
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
	if (this->capacity != size)
	{
		this->capacity = size;
		TYPE* buf = Memory::Alloc<TYPE>(size);
		j_assert(buf != nullptr);
        this->size = j_min(this->size, this->capacity);
        
        // run constructor on newly created elements
        for (uint32 i = this->size; i < this->capacity; i++) new (buf + i) TYPE();
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
Array<TYPE>::Insert(const TYPE& val, uint32 index)
{
	j_assert(index <= this->size);

	// special case if we insert at the end of the list
	if (index == this->size)
	{
		this->Append(val);
	}
	else
	{
		if (this->size == this->capacity) this->Grow();
		Memory::Move<TYPE>(this->data + index, this->data + index + 1, this->size - index);
		this->data[index] = val;
		this->size++;
	}
}

//------------------------------------------------------------------------------
/**
*/
template <class TYPE>
void
Array<TYPE>::InsertOrdered(const TYPE& val)
{
	// if we don't have any room, then we make room!
	if (this->size == this->capacity) this->Grow();

	// very very similar to the lambda found in SearchBinary, but this one returns the closest index regardless if the value is found or not
	std::function<uint32(TYPE*, int32, int32)> bin = [&](TYPE* data, int32 min, int32 max) -> uint32
	{
		// base case if our recursion is done with the binary search
		if (max < min)
		{
			int32 mid = max;
			const TYPE& cur = data[mid];
			
			// get value at min value (which is really the max value since they have passed each other)
			// if we are bigger than min, then insert element into that slot, otherwise, place before min
			if (cur < val)			return mid;
			else					return mid + 1;
		}
		else
		{
			int32 mid = min + ((max - min) >> 1);
			const TYPE& cur = data[mid];
			if (cur > val)			return bin(data, min, mid - 1);
			else if (cur < val)		return bin(data, mid + 1, max);
			else					return mid;
		}
	};

	// run lambda, get index, do insertion
	uint32 index = bin(this->data, 0, this->size);
	this->Insert(val, index);
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
	j_assert(index != -1);
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
	this->Remove(uint32(iterator - this->data));
}

//------------------------------------------------------------------------------
/**
*/
template <class TYPE>
void
Array<TYPE>::Remove(uint32 index)
{
	j_assert(index >= 0 && index < this->size);

	// convert index to size and calculate how many elements we must move
	uint32 dist = this->size - (index + 1);

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
void
Array<TYPE>::Clear()
{
	Memory::Free((void*)this->data);
	this->capacity = 0;
	this->size = 0;
	this->data = nullptr;
}

//------------------------------------------------------------------------------
/**
*/
template <class TYPE>
inline typename Array<TYPE>::Iter
Array<TYPE>::Start() const
{
	return this->data;
}

//------------------------------------------------------------------------------
/**
*/
template <class TYPE>
inline typename Array<TYPE>::Iter
Array<TYPE>::End() const
{
	return this->data + this->size;
}

//------------------------------------------------------------------------------
/**
*/
template <class TYPE>
const uint32
Array<TYPE>::Size() const
{
	return this->size;
}

//------------------------------------------------------------------------------
/**
*/
template <class TYPE>
int32
Array<TYPE>::Search(const TYPE& key)
{
#if JARVIS_CACHED_ELEMENT
	if (this->cachedElement != nullptr && *this->cachedElement == key) return int32(this->cachedElement - this->data);
#endif

	for (uint32 i = 0; i < this->size; i++)
	{
		if (this->data[i] == key)
		{
#if JARVIS_CACHED_ELEMENT
			this->cachedElement = &this->data[i];
#endif
			return i;
		}
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
#if JARVIS_CACHED_ELEMENT
	if (this->cachedElement != nullptr && *this->cachedElement == key) return int32(this->cachedElement - this->data);
#endif

	// lambda function which recurses the array to find the index, if none is found it simply returns -1
	std::function<int32(TYPE*, int32, int32)> bin = [&, key](TYPE* data, int32 min, int32 max) -> int32
	{
		if (max < min) return -1;
		else
		{
			int32 mid = min + ((max - min) >> 1);
			const TYPE& cur = data[mid];
			if (cur > key)			return bin(data, min, mid - 1);
			else if (cur < key)		return bin(data, mid + 1, max);
			else					return mid;
		}
	};

	int32 index = bin(this->data, 0, this->size);
#if JARVIS_CACHED_ELEMENT
	if (index != -1)
	{
		this->cachedElement = &this->data[index];
	}
#endif
	return index;
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
        this->capacity = newCapacity;
	}	
}

}} // namespace JARVIS::Core