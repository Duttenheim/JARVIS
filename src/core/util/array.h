#pragma once
//------------------------------------------------------------------------------
/**
	@class JARVIS::Core::Array
	
	Dynamically sized array. Increases array size by doubling the capacity.
	Can be resized so that appends doesn't modify its size.

	Supports sorting using std::sort, and also with a custom comparison function lambda.
	
	(C) 2015 See the LICENSE file.
*/
//------------------------------------------------------------------------------
#include <functional>
#include <algorithm>
#include <mutex>

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
    /// copy constructor form other array
    Array(const Array<TYPE>& rhs);
	/// move constructor
	Array(Array<TYPE>&& rhs);
    /// construct from init list
    Array(InitList<TYPE> rhs);
	/// destructor
	virtual ~Array();
    
	/// assignment operator
	void operator=(const Array<TYPE>& rhs);
	/// move operator
	void operator=(Array<TYPE>&& rhs);
    /// copy constructor from an initializer list
    void operator=(InitList<TYPE> rhs);
	/// read-write access operator
	TYPE& operator[](const uint32 index);
	/// read-only access operator
	const TYPE& operator[](const uint32 index) const;

	/// resize array to have given capacity, and retains the content if it fits
	void Resize(const uint32 size);
	/// set grow size, this will cause the array to allocate 'grow' new elements each time the array needs to increase its size
	void SetGrow(const uint32 grow);
    /// fill array with value
    void Fill(const TYPE& val);

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
	void RemoveIndex(const uint32 index);
	/// clear array
	void Clear();

	/// get iterator to first element
	Iter Start() const;
	/// get iterator to lats element
	Iter End() const;
	/// get size of array
	const uint32 Size() const;
    /// get internal buffer
    const TYPE* Buffer() const;
    
    /// used for range based const iteration
    const TYPE* begin() const;
    /// used for range based const iteration
    const TYPE* end() const;
    /// used for range based non-const iteration
    TYPE* begin();
    /// used for range based non-const iteration
    TYPE* end();

	/// search for key, return index in array, or -1 if not found
	int32 Search(const TYPE& key);
	/// search for key using binary search, but only works if array is sorted. Returns -1 if no such element is found.
	int32 SearchBinary(const TYPE& key);

	/// sort array
	void Sort();
	/// sort array using a special sorting function
	void Sort(const std::function<bool(const TYPE&, const TYPE&)>& func);
    
    /// thread safe append function
    void AppendThreadSafe(const TYPE& val);
    /// thread safe remove function
    void RemoveThreadSafe(const TYPE& key);
    /// thread safe remove index function
    void RemoveIndexThreadSafe(const uint32 index);
	
private:
	/// grow array using the grow parameter
	void Grow();
	/// shrinks array by allocating a new array which only contains size, so basically capacity becomes size
	void Shrink();

	uint32 grow;
	uint32 capacity;
	uint32 size;
	TYPE* data;
    std::mutex mutex;
};

//------------------------------------------------------------------------------
/**
*/
template <class TYPE>
inline
Array<TYPE>::Array() :
	grow(8),
    capacity(0),
    size(0),
    data(nullptr)
{
	this->data = nullptr;
}

//------------------------------------------------------------------------------
/**
    Move constructor.
    @param rhs  Array to move into this array.
*/
template <class TYPE>
inline
Array<TYPE>::Array(Array<TYPE>&& rhs)
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
inline
Array<TYPE>::Array(const Array<TYPE>& rhs) :
	grow(8),
    capacity(0),
    size(0),
    data(nullptr)
{
    this->Resize(rhs.size);
    this->capacity = rhs.capacity;
	this->grow = rhs.grow;
	this->size = rhs.size;
    for (uint32 i = 0; i < this->size; i++) new (this->data + i) TYPE(Fw(rhs.data[i]));
}

//------------------------------------------------------------------------------
/**
*/
template <class TYPE>
inline
Array<TYPE>::Array(InitList<TYPE> rhs) :
	grow(8),
    capacity(0),
    size(0),
    data(nullptr)
{
    size_t listSize = rhs.size();
    if (listSize > 0)
    {
        this->Resize(listSize);
        this->size = listSize;
        for (uint32 i = 0; i < listSize; i++) new (this->data + i) TYPE(Mv(rhs.begin()[i]));
    }
}

//------------------------------------------------------------------------------
/**
*/
template <class TYPE>
inline
Array<TYPE>::~Array()
{
    this->Clear();
}

//------------------------------------------------------------------------------
/**
    Assignment operator.
    @param rhs  Array to copy from.
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
    Move operator.
    @param rhs  Array to move from.
*/
template <class TYPE>
inline void
Array<TYPE>::operator=(Array<TYPE>&& rhs)
{
    // first, clear our data since we are stealing the rhs pointer
    this->Clear();
    
	this->capacity = rhs.capacity;
	this->grow = rhs.grow;
	this->size = rhs.size;
	this->data = rhs.data;

	rhs.capacity = rhs.grow = rhs.size = 0;
	rhs.data = nullptr;
}

//------------------------------------------------------------------------------
/**
    Move operator from std::vector, lets us do Array<TYPE> foo = {...}.
    @param rhs  Array to move from.
*/
template <class TYPE>
inline void
Array<TYPE>::operator=(InitList<TYPE> rhs)
{
    this->Clear();
    size_t listSize = rhs.size();
    if (listSize > 0)
    {
        this->Resize(listSize);
        this->size = listSize;
        for (uint32 i = 0; i < listSize; i++) new (this->data + i) TYPE(Mv(rhs.begin()[i]));
    }
}

//------------------------------------------------------------------------------
/**
    Read-write access operator.
    @param index    Index into the list.
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
    Read-only access operator
    @param index    Index into the list.
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
    Resize array to given size. If the size to resize is bigger than the array, the data is just copied.
    Otherwise, the array gets shrunk and only the data that fits will be copied.
    @param size     Number of elements to resize to.
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
		for (uint32 i = 0; i < this->size && i < this->capacity; i++)
		{
			new (buf + i) TYPE(std::move(this->data[i]));
			(&this->data[i])->~TYPE();
		}
        //for (uint32 i = this->size; i < this->capacity; i++) new (buf + i) TYPE;
		//Memory::Copy<TYPE>(this->data, buf, this->size);
		Memory::Fill(buf + this->size, (this->capacity - this->size) * sizeof(TYPE), 0);
        if (nullptr != this->data) Memory::Free(this->data);
		this->data = buf;
	}	
}

//------------------------------------------------------------------------------
/**
    Set how many elements the array should use to increase it's size if empty.
    @param grow     Number of elements to initiate the array to.
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
    Fill array with elements so that size ise equal to capacity
    @param val      Value to fill array with.
*/
template <class TYPE>
inline void
Array<TYPE>::Fill(const TYPE& val)
{
    // destroy elements already in the array
    for (uint32 i = 0; i < this->size; i++)
    {
        (&this->data[i])->~TYPE();
    }
    for (uint32 i = 0; i < this->capacity; i++)
    {
        new (&this->data[i]) TYPE(Fw(val));
    }
    this->size = this->capacity;
}

//------------------------------------------------------------------------------
/**
    Append element to end of array
    @param val      Element to add.
*/
template <class TYPE>
inline void
Array<TYPE>::Append(const TYPE& val)
{	
	// if we don't have any room, then we make room!
	if (this->size == this->capacity) this->Grow();
    
    // allocate new element here
	new (this->data + this->size) TYPE(val);
	this->size++;
}

//------------------------------------------------------------------------------
/**
    Insert element into array at given index.
    @param val      Element to insert.
    @param index    Location in array to which this value gets inserted.
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
    Insert element but retain the ordered state of the array. Only viable if array is sorted.
    @param val      Element to insert.
*/
template <class TYPE>
void
Array<TYPE>::InsertOrdered(const TYPE& val)
{
	// if we don't have any room, then we make room!
	if (this->size == this->capacity) this->Grow();
    
    int32 min = 0;
    int32 max = this->size;
    int32 result;
    int32 mid = min;
    while (max > min)
    {
        mid = min + ((max - min) >> 1);
        const TYPE& cur = data[mid];
        if (cur < val)		min = mid + 1;
        else				max = mid;
    }
    
    // get the max value which should either be equal to min if found, or LESS than min if not
    const TYPE& cur = data[mid];
    
    // if value at midpoint is bigger, select min, otherwise max
    if (cur < val) result = min;
    else           result = max;

	// insert, result must be a valid result here
	this->Insert(val, result);
}

//------------------------------------------------------------------------------
/**
    Merge two arrays, the other array will be retained.
    @param arr      Array to merge into this array.
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
    Rmmove element, assumes element actually exists in array.
    @param key      Element to search for, and if found, remove.
*/
template <class TYPE>
inline void
Array<TYPE>::Remove(const TYPE& key)
{
	int32 index = this->Search(key);
	j_assert(index != -1);
	this->RemoveIndex(index);
}

//------------------------------------------------------------------------------
/**
    Remove an index in the array using an iterator. Does no searching.
    @param iterator     Iterator into the array.
*/
template <class TYPE>
inline void
Array<TYPE>::Remove(Iter iterator)
{
	j_assert(iterator != nullptr);
	this->RemoveIndex(uint32(iterator - this->data));
}

//------------------------------------------------------------------------------
/**
    Remove an index in the array using an index.
    @param index        Index in the array to remove.
*/
template <class TYPE>
void
Array<TYPE>::RemoveIndex(const uint32 index)
{
	j_assert(index >= 0 && index < this->size);

	// convert index to size and calculate how many elements we must move
	uint32 dist = this->size - (index + 1);

	// run destructor on element we remove
	(&this->data[index])->~TYPE();

	// if we're not at the end of the list, move the data
	if (dist > 0)
	{
		// move data
		Memory::Move<TYPE>(this->data + index + 1, this->data + index, dist);
	}

	// decrease size
	this->size--;
}

//------------------------------------------------------------------------------
/**
*/
template <class TYPE>
void
Array<TYPE>::Clear()
{
    uint32 i;
    for (i = 0; i < this->size; i++)
    {
		(&this->data[i])->~TYPE();
    }
    
    if (nullptr != this->data && this->size > 0) Memory::Free((void*)this->data);
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
const TYPE*
Array<TYPE>::Buffer() const
{
	return this->data;
}

//------------------------------------------------------------------------------
/**
*/
template <class TYPE>
const TYPE*
Array<TYPE>::begin() const
{
    return &this->data[0];
}

//------------------------------------------------------------------------------
/**
*/
template <class TYPE>
const TYPE*
Array<TYPE>::end() const
{
    return &this->data[this->size];
}

//------------------------------------------------------------------------------
/**
*/
template <class TYPE>
TYPE*
Array<TYPE>::begin()
{
    return &this->data[0];
}

//------------------------------------------------------------------------------
/**
*/
template <class TYPE>
TYPE*
Array<TYPE>::end()
{
    return &this->data[this->size];
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
		if (this->data[i] == key)
		{
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
    if (this->size == 0) return -1;
    
    int32 min = 0;
    int32 max = this->size-1;
    int32 mid;
    int32 result = -1;
    while (max > min)
    {
        mid = min + ((max - min) >> 1);
        const TYPE& cur = data[mid];
        if (cur < key)		min = mid + 1;
        else				max = mid;
    }
    if ((max == min) && (data[min] == key)) result = min;
	return result;
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
	Memory::Fill(buf + this->size, (newCapacity - this->size) * sizeof(TYPE), 0);

	if (this->data != nullptr)
	{
		for (uint32 i = 0; i < this->size; i++)
		{
			new (buf + i) TYPE(std::move(this->data[i]));
			(&this->data[i])->~TYPE();
		}
		Memory::Free(this->data);
	}	

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

//------------------------------------------------------------------------------
/**
*/
template <class TYPE>
inline void
Array<TYPE>::AppendThreadSafe(const TYPE& val)
{
    std::lock_guard<std::mutex> lock(this->mutex);
    this->Append(val);
}

//------------------------------------------------------------------------------
/**
*/
template <class TYPE>
inline void
Array<TYPE>::RemoveThreadSafe(const TYPE &key)
{
    std::lock_guard<std::mutex> lock(this->mutex);
    this->Remove(key);
}

//------------------------------------------------------------------------------
/**
    Thread-safe method for indexed removal
    @param index        Index to remove from the list.
*/
template <class TYPE>
inline void
Array<TYPE>::RemoveIndexThreadSafe(const uint32 index)
{
    std::lock_guard<std::mutex> lock(this->mutex);
    this->RemoveIndex(index);
}

}} // namespace JARVIS::Core