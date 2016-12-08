#pragma once
//------------------------------------------------------------------------------
/**
	@class JARVIS::Core::Map
	
	Dynamically typed key-value pair lookup dictionary. 

	Use this class to do fast lookups, since keys are always sorted, 
	and values can be retrieved by performing a binary search with a O(log n) running time.

	The indexing operator utilizes the array cached element search, 
	which means that accessing the same key several times using either the [] operator 
	or the Contains function will only perform a single search.

	This kind of scenario is rather common, using first Contains and then accessing said element.
		Using only the [] operator would assert such an element exists.
		Contains results in 2 searches just to get a single element.
	
	(C) 2015 See the LICENSE file.
*/
//------------------------------------------------------------------------------
#include "util/array.h"
namespace JARVIS { 
namespace Core
{
template <class KEY, class VALUE>
class Map
{
public:
	/// constructor
	Map();
	/// destructor
	virtual ~Map();
    
    /// forward declare struct
    struct Kvp;

	/// key-lookup operator for read only access
	const VALUE& operator[](const KEY& key) const;
	/// key-lookup for read-write access
	VALUE& operator[](const KEY& key);
	/// index-lookup for Key-Value pair
	const Kvp& Pair(const uint32 index) const;
	/// index-lookup for key
	const KEY& Key(const uint32 index) const;
	/// index-lookup for const value
	const VALUE& Value(const uint32 index) const;
    /// index-lookup for read-write access
    VALUE& Value(const uint32 index);

	/// add key-value pair by using key and value separately
	void Insert(const KEY& key, const VALUE& value);
	/// add key-value pair by using std::tuple
	void Insert(const Kvp& kvp);
	/// returns true if dictionary contains the key
	bool Contains(const KEY& key);
    /// get index of key into array, or -1 if it can't be found
    uint32 Index(const KEY& key);
    /// removes element on key
    void Remove(const KEY& key);

	/// resize internal storage before hand
	void Resize(const uint32 size);
	/// begin mass insertion, this wont add elements sorted until the end is run
	void BeginMassInsertion();
	/// special insert function which doesn't perform any sorting, this can only be done within begin/end mass insertion
	void InsertUnordered(const KEY& key, const VALUE& value);
	/// special insert function which inserts unordered, but must be done within begin/end mass insertion
	void InsertUnordered(const Kvp& kvp);
	/// end mass insertion, this will cause the dictionary to get sorted
	void EndMassInsertion();

	/// clear dictionary
	void Clear();

	/// get size of map
	const uint32 Size() const;
    
    struct Kvp
    {
        /// constructor from tuple
        Kvp(std::tuple<KEY, VALUE>&& tuple)
        {
            this->tuple = tuple;
        }
        /// constructor from key-value pair
        Kvp(const KEY& key, const VALUE& value)
        {
            this->tuple = std::make_tuple(key, value);
        }
        
        std::tuple<KEY, VALUE> tuple;
        
        /// less than operator
        bool operator<(const Kvp& rhs) const
        {
            return std::get<0>(this->tuple) < std::get<0>(rhs.tuple);
        }
        
        /// equality operator
        bool operator==(const Kvp& rhs) const
        {
            return std::get<0>(this->tuple) == std::get<0>(rhs.tuple);
        }
        
        /// inequality operator
        bool operator!=(const Kvp& rhs) const
        {
            return std::get<0>(this->tuple) != std::get<0>(rhs.tuple);
        }
        
        /// greater than operator
        bool operator>(const Kvp& rhs) const
        {
            return std::get<0>(this->tuple) > std::get<0>(rhs.tuple);
        }
    };

private:
	bool inMassInsertion;
	Array<Kvp> data;
};

//------------------------------------------------------------------------------
/**
*/
template <class KEY, class VALUE>
inline
Map<KEY, VALUE>::Map() :
	inMassInsertion(false)
{
	// empty
}

//------------------------------------------------------------------------------
/**
*/
template <class KEY, class VALUE>
inline
JARVIS::Core::Map<KEY, VALUE>::~Map()
{
	// empty
}

//------------------------------------------------------------------------------
/**
*/
template <class KEY, class VALUE>
inline VALUE&
Map<KEY, VALUE>::operator[](const KEY& key)
{
	int32 index = this->data.SearchBinary(Kvp(std::forward_as_tuple(key, VALUE())));
	j_assert(index != -1);
	return std::get<1>(this->data[index].tuple);
}

//------------------------------------------------------------------------------
/**
*/
template <class KEY, class VALUE>
inline const VALUE&
Map<KEY, VALUE>::operator[](const KEY& key) const
{
	int32 index = this->data.SearchBinary(std::forward_as_tuple(key, VALUE()));
	j_assert(index != -1);
	return std::get<1>(this->data[index].tuple);
}

//------------------------------------------------------------------------------
/**
*/
template <class KEY, class VALUE>
inline const typename Map<KEY, VALUE>::Kvp&
Map<KEY, VALUE>::Pair(const uint32 index) const
{
	j_assert(index < this->data.Size());
	return this->data[index];
}

//------------------------------------------------------------------------------
/**
*/
template <class KEY, class VALUE>
inline const KEY&
Map<KEY, VALUE>::Key(const uint32 index) const
{
	j_assert(index < this->data.Size());
	return std::get<0>(this->data[index]);
}

//------------------------------------------------------------------------------
/**
*/
template <class KEY, class VALUE>
inline const VALUE&
Map<KEY, VALUE>::Value(const uint32 index) const
{
	j_assert(index < this->data.Size());
	return std::get<1>(this->data[index]);
}

//------------------------------------------------------------------------------
/**
*/
template <class KEY, class VALUE>
inline VALUE&
Map<KEY, VALUE>::Value(const uint32 index)
{
	j_assert(index < this->data.Size());
	return std::get<1>(this->data[index]);
}

//------------------------------------------------------------------------------
/**
*/
template <class KEY, class VALUE>
inline void
Map<KEY, VALUE>::Insert(const KEY& key, const VALUE& value)
{
	this->data.InsertOrdered(Kvp(std::forward_as_tuple(key, value)));
}

//------------------------------------------------------------------------------
/**
*/
template <class KEY, class VALUE>
inline void
Map<KEY, VALUE>::Insert(const Kvp& kvp)
{
	this->data.InsertOrdered(kvp);
}

//------------------------------------------------------------------------------
/**
*/
template <class KEY, class VALUE>
inline bool
Map<KEY, VALUE>::Contains(const KEY& key)
{
	return this->data.SearchBinary(Kvp(std::forward_as_tuple(key, VALUE()))) != -1;
}

//------------------------------------------------------------------------------
/**
*/
template <class KEY, class VALUE>
inline uint32
Map<KEY, VALUE>::Index(const KEY& key)
{
    return this->data.SearchBinary(std::forward_as_tuple(key, VALUE()));
}

//------------------------------------------------------------------------------
/**
*/
template <class KEY, class VALUE>
inline void
Map<KEY, VALUE>::Remove(const KEY& key)
{
    uint32 index = this->data.SearchBinary(Kvp(std::forward_as_tuple(key, VALUE())));
    j_assert(index != -1);
    this->data.RemoveIndex(index);
}

//------------------------------------------------------------------------------
/**
*/
template <class KEY, class VALUE>
inline void
Map<KEY, VALUE>::Resize(const uint32 size)
{
	j_assert(size > 0);
	this->data.Resize(size);
}

//------------------------------------------------------------------------------
/**
*/
template <class KEY, class VALUE>
inline void
Map<KEY, VALUE>::BeginMassInsertion()
{
	j_assert(!this->inMassInsertion);
	this->inMassInsertion = true;
}

//------------------------------------------------------------------------------
/**
*/
template <class KEY, class VALUE>
inline void
Map<KEY, VALUE>::InsertUnordered(const KEY& key, const VALUE& value)
{
	j_assert(this->inMassInsertion);
	this->data.Append(Kvp(key, value));
}

//------------------------------------------------------------------------------
/**
*/
template <class KEY, class VALUE>
inline void
Map<KEY, VALUE>::InsertUnordered(const Kvp& kvp)
{
	j_assert(this->inMassInsertion);
	this->data.Append(kvp);
}

//------------------------------------------------------------------------------
/**
*/
template <class KEY, class VALUE>
inline void
Map<KEY, VALUE>::EndMassInsertion()
{
	j_assert(this->inMassInsertion);
	this->data.Sort();
	this->inMassInsertion = false;
}

//------------------------------------------------------------------------------
/**
*/
template <class KEY, class VALUE>
inline void
Map<KEY, VALUE>::Clear()
{
	this->data.Clear();
}

}} // namespace JARVIS::Core