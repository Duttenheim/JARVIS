#pragma once
//------------------------------------------------------------------------------
/**
	@class JARVIS::Core::String
	
	Represents a list of characters. 

	Uses a local buffer for small strings, and a heap allocated dynamic buffer for long strings.
	This allows for strings to be allocated fast if they fall within a small range.
	
	(C) 2015 See the LICENSE file.
*/
//------------------------------------------------------------------------------
#include "config.h"
#include "mem.h"
#include <string.h>
namespace JARVIS { 
namespace Core
{
class String
{
public:
	/// constructor
	String();
	/// construct from c string
	String(const char* buf);
	/// construct from c string with a given size
	String(const char* buf, uint32 size);
	/// construct from other string
	String(const String& rhs);
	/// move constructor from other string
	String(String&& rhs);
	/// destructor
	virtual ~String();

	/// set buffer from c string
	void Set(const char* str);
	/// set buffer from c string starting at offset and copying length
	void Set(const char* str, uint32 length);
	/// set buffer from other string
	void Set(const String& str);
	/// set buffer from other string starting at offset and copying length characters
	void Set(const String& str, uint32 length);

	/// addition-assign operator with c string
	void operator+=(const char* str);
	/// addition-assign operator with other string
	void operator+=(const String& str);
	/// implicit conversion to c string
	operator const char*() const;

	/// append c string 
	void Append(const char* str);
	/// append range of c string
	void Append(const char* str, uint32 length);
	/// append from other string
	void Append(const String& str);
	/// append range of other string
	void Append(const String& str, uint32 length);

	/// get length of string
	const uint32 Length() const;
	/// get c pointer
	const char* CharPtr() const;
private:

	/// delete heap buffer if valid
	void Delete();

	static const uint32 StackBufferSize = 64;

	char* heapBuffer;
	uint32 heapBufferLength;
	char stackBuffer[StackBufferSize];
	uint32 length;
};

//------------------------------------------------------------------------------
/**
*/
inline
String::String() :
	heapBuffer(nullptr),
	heapBufferLength(0),
	length(0)
{
	// empty
}

//------------------------------------------------------------------------------
/**
*/
inline
String::String(const char* buf) :
	heapBuffer(nullptr),
	heapBufferLength(0),
	length(0)
{
	this->Set(buf);
}

//------------------------------------------------------------------------------
/**
*/
inline
String::String(const char* buf, uint32 size) :
	heapBuffer(nullptr),
	heapBufferLength(0),
	length(0)
{
	this->Set(buf, size);
}

//------------------------------------------------------------------------------
/**
*/
inline
String::String(const String& rhs) :
	heapBuffer(nullptr),
	heapBufferLength(0),
	length(0)
{
	this->Set(rhs.CharPtr());
}

//------------------------------------------------------------------------------
/**
*/
inline
String::String(String&& rhs) :
	heapBuffer(nullptr),
	heapBufferLength(0),
	length(0)
{
	this->Set(rhs.CharPtr());
	rhs.heapBuffer = nullptr;
}

//------------------------------------------------------------------------------
/**
*/
inline
String::~String()
{
	if (nullptr != this->heapBuffer) Memory::Free(this->heapBuffer);
	this->heapBuffer = nullptr;
}

//------------------------------------------------------------------------------
/**
*/
inline void
String::Set(const char* str)
{
	this->Set(str, std::strlen(str));
}

//------------------------------------------------------------------------------
/**
*/
void
String::Set(const char* str, uint32 length)
{
	if (nullptr == str)
	{
		// we unset the string
		this->Delete();
	}
	else if (length < StackBufferSize)
	{
		// we can fit the string within the local buffer
		if (nullptr != this->heapBuffer) this->Delete();
		Memory::Copy<char>(str, this->stackBuffer, length);
		this->stackBuffer[length] = 0;
	}
	else if (length < this->heapBufferLength)
	{
		// we can fit our string within our currently allocated buffer
		Memory::Copy<char>(str, this->heapBuffer, length);
		this->heapBuffer[length] = 0;
		this->stackBuffer[0] = 0;
	}
	else
	{
		if (nullptr != this->heapBuffer) this->Delete();
		this->heapBuffer = Memory::Alloc<char>(length + 1);
		Memory::Copy(str, this->heapBuffer, length);
		this->heapBufferLength = length;
		this->heapBuffer[length] = 0;
		this->stackBuffer[0] = 0;
	}
	this->length = length;
}

//------------------------------------------------------------------------------
/**
*/
inline void
String::Set(const String& str)
{
	this->Set(str.CharPtr(), str.length);
}

//------------------------------------------------------------------------------
/**
*/
inline void
String::Set(const String& str, uint32 length)
{
	this->Set(str.CharPtr(), length);
}

//------------------------------------------------------------------------------
/**
*/
static inline String
operator+(const char* lhs, const String& rhs)
{
	String str(lhs);
	str.Append(rhs);
	return str;
}

//------------------------------------------------------------------------------
/**
*/
static inline String
operator+(const String& lhs, const String& rhs)
{
	String str(lhs);
	str.Append(rhs);
	return str;
}

//------------------------------------------------------------------------------
/**
*/
static inline String
operator+(const String& lhs, const char* rhs)
{
	String str = lhs;
	str.Append(rhs);
	return str;
}

//------------------------------------------------------------------------------
/**
*/
inline void
String::operator+=(const char* str)
{
	this->Append(str);
}

//------------------------------------------------------------------------------
/**
*/
inline void
String::operator+=(const String& str)
{
	this->Append(str, str.length);
}

//------------------------------------------------------------------------------
/**
*/
inline
String::operator const char*() const
{
	return this->CharPtr();
}

//------------------------------------------------------------------------------
/**
*/
inline void
String::Append(const char* str)
{
	this->Append(str, std::strlen(str));
}

//------------------------------------------------------------------------------
/**
*/
void
String::Append(const char* str, uint32 length)
{
	uint32 len = this->length + length;
	if (len < StackBufferSize)
	{
		Memory::Copy<char>(str, this->stackBuffer + this->length, length);
		this->stackBuffer[len] = 0;
	}
	else
	{
		// alloc new buffer
		auto buf = Memory::Alloc<char>(len);
		if (nullptr != this->heapBuffer)
		{
			Memory::Copy<char>(this->heapBuffer, buf, this->length);
			this->Delete();
		}
		else
		{
			Memory::Copy<char>(this->stackBuffer, buf, this->length);
		}
		Memory::Copy<char>(str, buf + this->length, length);
		this->heapBuffer[len] = 0;
		this->heapBufferLength = len;
		this->heapBuffer = buf;

	}
	this->length = len;
}

//------------------------------------------------------------------------------
/**
*/
inline void
String::Append(const String& str)
{
	this->Append(str.CharPtr(), str.length);
}

//------------------------------------------------------------------------------
/**
*/
inline void
String::Append(const String& str, uint32 length)
{
	this->Append(str.CharPtr(), length);
}

//------------------------------------------------------------------------------
/**
*/
inline const char*
String::CharPtr() const
{
	if (nullptr != this->heapBuffer) return this->heapBuffer;
	else							 return this->stackBuffer;
}

//------------------------------------------------------------------------------
/**
*/
void
String::Delete()
{
	if (nullptr != this->heapBuffer)
	{
		Memory::Free(this->heapBuffer);
		this->heapBuffer = nullptr;
		this->heapBufferLength = 0;
	}

	this->length = 0;
	this->stackBuffer[0] = 0;
}

}
} // namespace JARVIS::Core