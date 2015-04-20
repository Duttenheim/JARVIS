#pragma once
//------------------------------------------------------------------------------
/**
	@file core/mem.h

	Memory macros. Use these to get appropriate memory allocation with allocation counting and allocation failure management

	(C) 2015 See the LICENSE file.
*/
#include <cstdlib>
#include <cstring>

#define JARVIS_MEM_INIT	 0xFF
#define JARVIS_MEM_DEBUG (1)
#define JARVIS_FILL_DUFFSDEVICE (1)

namespace JARVIS {
namespace Core {
namespace Memory
{

static void Fill(void* buf, uint32 size, uint8 val);
template <class TYPE> static void Fill(TYPE* buf, uint32 size, const TYPE& val);

//------------------------------------------------------------------------------
/**
	Allocate memory.
	@param elements		Number of elements to allocate.
*/
template <class TYPE> 
inline static TYPE*
Alloc(uint32 elements)
{
	TYPE* buf = (TYPE*)std::malloc(sizeof(TYPE) * elements);
	j_assert(buf != nullptr);
#if JARVIS_MEM_DEBUG
	Memory::Fill(buf, sizeof(TYPE) * elements, JARVIS_MEM_INIT);
#endif
	return buf;
}

//------------------------------------------------------------------------------
/**
	Allocate memory.
	@param size			Number of bytes to allocate.
*/
inline static byte*
Alloc(uint32 size)
{
	byte* buf = (byte*)std::malloc(size);
	j_assert(buf != nullptr);
#if JARVIS_MEM_DEBUG
	Memory::Fill(buf, size, JARVIS_MEM_INIT);
#endif
	return buf;
}

//------------------------------------------------------------------------------
/**
    Allocate new instance of class.
*/
template <class TYPE, class ...ARGS>
inline static TYPE*
New(ARGS&&... args)
{
    return new TYPE(args...);
}

//------------------------------------------------------------------------------
/**
	Deallocate memory.
	@param ptr			Pointer to release.
*/
inline static void
Free(void* ptr)
{
	std::free(ptr);
}

//------------------------------------------------------------------------------
/**
	Copy data between two buffers.
	@param from			Source buffer to copy data from.
	@param to			Destination buffer to which the data will copied.
	@param elements		Number of elements (not bytes) to be copied.
*/
template <class TYPE>
inline static void
Copy(const TYPE* from, TYPE* to, uint32 elements)
{
	std::memcpy((void*)to, (void*)from, sizeof(TYPE) * elements);
}

//------------------------------------------------------------------------------
/**
	Copy data between two buffers.
	@param from			Source buffer to copy data from.
	@param to			Destination buffer to which the data will be copied.
	@param size			Number of bytes to copy.
*/
inline static void 
Copy(const void* from, void* to, uint32 size)
{
	std::memcpy(to, from, size);
}

//------------------------------------------------------------------------------
/**
	Move data from one buffer to another.
	@param from			Source buffer to be moved.
	@param to			Destination buffer to which the data will be moved.
	@param elements		Number of elements to move.
*/
template <class TYPE>
inline static void
Move(TYPE* from, TYPE* to, uint32 elements)
{
	std::memmove((void*)to, (void*)from, sizeof(TYPE) * elements);
}

//------------------------------------------------------------------------------
/**
	Move data from one buffer to another.
	@param from			Source buffer to be moved.
	@param to			Destination buffer to which the data will be moved.
	@param size			Number of elements to move.
*/
inline static void
Move(void* from, void* to, uint32 size)
{
	std::memmove(to, from, size);
}

//------------------------------------------------------------------------------
/**
	Fills data using duffs device.
	@param buf			The buffer we want to fill.
	@param size			The number of elements we want to fill with.
	@param val			The value we want to fill with
*/
template <class TYPE>
inline static void
Fill(TYPE* buf, uint32 elements, const TYPE& val)
{
	TYPE *to = buf;
    auto count = elements;
	{
		auto n = (count + 7) / 8;
		switch (count % 8)
		{
			case 0: do {	*to++ = val;
			case 7:			*to++ = val;
			case 6:			*to++ = val;
			case 5:			*to++ = val;
			case 4:			*to++ = val;
			case 3:			*to++ = val;
			case 2:			*to++ = val;
			case 1:			*to++ = val;
			} while (--n > 0);
		}
	}
}

//------------------------------------------------------------------------------
/**
	Fills buffer.
	@param buf			The buffer we want to fill.
	@param size			The number of bytes we want to fill.
	@param val			The byte value we want to fill with.
*/
inline static void
Fill(void* buf, uint32 size, uint8 val)
{
	std::memset(buf, val, size);
}

}}}
