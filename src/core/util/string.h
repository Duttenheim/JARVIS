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
#include <string.h>
#include "array.h"
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
	String(const char* buf, SizeT size);
	/// construct from other string
	String(const String& rhs);
	/// move constructor from other string
	String(String&& rhs);
    /// construct empty string
    String(std::nullptr_t);
	/// destructor
	virtual ~String();
    
    /// clear string
    void Clear();

	/// set buffer from c string
	void Set(const char* str);
	/// set buffer from c string starting at offset and copying length
	void Set(const char* str, SizeT length);
	/// set buffer from other string
	void Set(const String& str);
	/// set buffer from other string starting at offset and copying length characters
	void Set(const String& str, SizeT length);

	/// addition-assign operator with c string
	void operator+=(const char* str);
	/// addition-assign operator with other string
	void operator+=(const String& str);
    /// assignment operator with c string
    void operator=(const char* str);
    /// assignment operator with other string
    void operator=(const String& str);
	/// implicit conversion to c string
	operator const char*() const;
    /// comparison between strings
    bool operator==(const String& rhs) const;
    /// comparison between char pointers
    bool operator==(const char* rhs) const;
    
    /// compare if one string is smaller than other
    bool operator<(const String& rhs) const;
    /// compare if one string is snaller than another char ptr
    bool operator<(const char* rhs) const;
    /// compare if one string is bigger than other
    bool operator>(const String& rhs) const;
    /// compare if one string is bigger than another char ptr
    bool operator>(const char* rhs) const;
    /// compare if smaller or same
    bool operator<=(const String& rhs) const;
    /// compare if smaller or same with char pointer
    bool operator<=(const char* rhs) const;
    /// compare if bigger or same
    bool operator>=(const String& rhs) const;
    /// compare if bigger or same with char pointer
    bool operator>=(const char* rhs) const;

	/// append c string 
	void Append(const char* str);
	/// append range of c string
	void Append(const char* str, SizeT length);
	/// append from other string
	void Append(const String& str);
	/// append range of other string
	void Append(const String& str, SizeT length);
    
    /// split string into segments
    Array<String> Split(const String& tokens) const;
    /// find first index of character
	ptrdiff FindFirst(char c, IndexT offset = 0) const;
    /// find last index of character
	ptrdiff FindLast(char c, IndexT offset = 0) const;
    /// extract string to string, returns match if failed, inclusive means you include match
    String ExtractToString(const String& match, bool inclusive = false) const;
    /// extract to end from string, returns match if failed, inclusive means you include match
    String ExtractToEndFromString(const String& match, bool inclusive = false) const;
    /// extract string to index
    String ExtractToIndex(IndexT index) const;
    /// extract from beginning to first occurrence of char
    String ExtractToFirstChar(char c) const;
    /// extract from beginning to last occurrence of char
    String ExtractToLastChar(char c) const;
    /// extract to end from first occurrence of char
    String ExtractToEndFromFirst(char c) const;
    /// extract to end from last occurrence of char
    String ExtractToEndFromLast(char c) const;
    
    /// replace character with other characters
    void Replace(const char find, const char replace);
    
    /// create new string using the printf syntax
    static Core::String Sprintf(const char* format, ...);

	/// get length of string
	const SizeT Length() const;
	/// get c pointer
	const char* CharPtr() const;
    /// generate hash for string
    const uint32 Hash() const;
private:

	/// delete heap buffer if valid
	void Delete();

	static const uint32 StackBufferSize = 64;

	char stackBuffer[StackBufferSize];
	char* heapBuffer;
	SizeT heapBufferLength;
	SizeT length;
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
	this->stackBuffer[0] = 0;
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
String::String(const char* buf, SizeT size) :
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
String::String(String&& rhs)
{
    this->heapBuffer = rhs.heapBuffer;
    this->heapBufferLength = rhs.heapBufferLength;
    this->length = rhs.length;
    if (this->heapBuffer == nullptr) Memory::Copy<char>(rhs.stackBuffer, this->stackBuffer, rhs.length);
    
    rhs.length = 0;
    rhs.stackBuffer[0] = 0;
	rhs.heapBuffer = nullptr;
    rhs.heapBufferLength = 0;
}

//------------------------------------------------------------------------------
/**
*/
inline
String::String(std::nullptr_t) :
    String()
{
    // empty
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
String::Clear()
{
    this->Delete();
    this->heapBuffer = nullptr;
    this->heapBufferLength = 0;
    this->length = 0;
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
inline void
String::Set(const char* str, SizeT length)
{
	if (nullptr == str)
	{
		// we unset the string
		this->Delete();
	}
	else if (length < StackBufferSize)
	{
		// we can fit the string within the local buffer
        this->Delete();
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
String::Set(const String& str, SizeT length)
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
inline void
String::operator=(const char* str)
{
    this->Delete();
    this->Set(str);
}
    
//------------------------------------------------------------------------------
/**
 */
inline void
String::operator=(const String& str)
{
	j_assert(this != &str);
    this->Delete();
    this->Set(str);
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
inline bool
String::operator==(const String& rhs) const
{
    return strcmp(this->CharPtr(), rhs.CharPtr()) == 0;
}

//------------------------------------------------------------------------------
/**
*/
inline bool
String::operator==(const char* rhs) const
{
    return strcmp(this->CharPtr(), rhs) == 0;
}

//------------------------------------------------------------------------------
/**
*/
inline bool
String::operator<(const String& rhs) const
{
    return strcmp(this->CharPtr(), rhs.CharPtr()) < 0;
}

//------------------------------------------------------------------------------
/**
*/
inline bool
String::operator<(const char* rhs) const
{
    return strcmp(this->CharPtr(), rhs) < 0;
}

//------------------------------------------------------------------------------
/**
*/
inline bool
String::operator>(const String& rhs) const
{
    return strcmp(this->CharPtr(), rhs.CharPtr()) > 0;
}

//------------------------------------------------------------------------------
/**
*/
inline bool
String::operator>(const char* rhs) const
{
    return strcmp(this->CharPtr(), rhs) > 0;
}

//------------------------------------------------------------------------------
/**
*/
inline bool
String::operator>=(const String& rhs) const
{
    return strcmp(this->CharPtr(), rhs.CharPtr()) >= 0;
}

//------------------------------------------------------------------------------
/**
*/
inline bool
String::operator>=(const char* rhs) const
{
    return strcmp(this->CharPtr(), rhs) >= 0;
}

//------------------------------------------------------------------------------
/**
*/
inline bool
String::operator<=(const String& rhs) const
{
    return strcmp(this->CharPtr(), rhs.CharPtr()) <= 0;
}

//------------------------------------------------------------------------------
/**
*/
inline bool
String::operator<=(const char* rhs) const
{
    return strcmp(this->CharPtr(), rhs) <= 0;
}

//------------------------------------------------------------------------------
/**
    Add string to this string.
    @param str The string to concatenate with.
*/
inline void
String::Append(const char* str)
{
	this->Append(str, std::strlen(str));
}

//------------------------------------------------------------------------------
/**
    Add string but with limited size
    @param str The string to concatenate with this string.
    @param length The size of str to use (in characters).
*/
inline void
String::Append(const char* str, SizeT length)
{
	SizeT len = this->length + length;
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
		this->heapBuffer = buf;
        this->heapBuffer[len] = 0;
		this->heapBufferLength = len;
	}
	this->length = len;
}

//------------------------------------------------------------------------------
/**
    Add string to this string.
    @param str The string to concatenate with.
*/
inline void
String::Append(const String& str)
{
	this->Append(str.CharPtr(), str.length);
}

//------------------------------------------------------------------------------
/**
    Add string but with limited size
    @param str The string to concatenate with this string.
    @param length The size of str to use (in characters).
*/
inline void
String::Append(const String& str, SizeT length)
{
	this->Append(str.CharPtr(), length);
}

//------------------------------------------------------------------------------
/**
    Split string into tokens.
    @tokens A string contanining characters used to subdivide string into fragments.
    @return Array of strings, where each element represents a string fragment terminated with any character in tokens.
*/
inline Array<String>
String::Split(const String& tokens) const
{
    Array<String> ret;
    String copy(*this);
    char* ptr = const_cast<char*>(copy.CharPtr());
    char* tok = strtok(ptr, tokens.CharPtr());
    while (tok != nullptr)
    {
        ret.Append(String(tok));
        tok = strtok(nullptr, tokens.CharPtr());
    }
    return ret;
}

//------------------------------------------------------------------------------
/**
    Find first occurrence of character.
    @param c The character to locate.
    @param offset The offset from the start of the buffer to start looking.
    @return index or -1 if c is not located.
*/
inline ptrdiff
String::FindFirst(char c, IndexT offset) const
{
    if (this->length > 0)
    {
        j_assert(offset < this->length);
        const char* ptr = strchr(this->CharPtr() + offset, c);
        if (ptr != nullptr) return ptr - this->CharPtr();
    }
    return -1;
}

//------------------------------------------------------------------------------
/**
    Find last occurrence of character.
    @param c The character to locate.
    @param offset The offset from the start of the buffer to start looking.
    @return index or -1 if c is not located.
*/
inline ptrdiff
String::FindLast(char c, IndexT offset) const
{
    if (this->length > 0)
    {
        j_assert(this->length - offset > 0);
        const char* ptr = strrchr(this->CharPtr() - offset, c);
        if (ptr != nullptr) return ptr - this->CharPtr();
    }
    return -1;
}

//------------------------------------------------------------------------------
/**
    Extract from beginning of string leading up to matching string
    @param match The string to locate.
    @param inclusive If true (default false) will also include rhs in result.
    @return new string from start until match is encountered.
*/
inline String
String::ExtractToString(const String& match, bool inclusive) const
{
    if (this->length > 0 && match.length > 0)
    {
        const char* ptr = this->CharPtr();
        const char* other = match.CharPtr();
        const char* offset = strstr(ptr, other);
		SizeT len = inclusive ? match.length : 0;
        if (offset != nullptr) return String(ptr, offset - ptr + len);
        else                   return *this;
    }
    return nullptr;
}

//------------------------------------------------------------------------------
/**
    Extract from located string segment leading up to the end of the string.
    @param match The string to locate.
    @param inclusive If true (default false) will also include rhs in result.
    @return new string from match up until end.
*/
inline String
String::ExtractToEndFromString(const String& match, bool inclusive) const
{
    if (this->length > 0 && match.length > 0)
    {
        const char* ptr = this->CharPtr();
        const char* other = match.CharPtr();
        const char* offset = strstr(ptr, other);
		SizeT len = inclusive ? 0 : match.length;
        if (offset != nullptr) return String(offset + len);
        else                   return *this;
    }
    return nullptr;
}

//------------------------------------------------------------------------------
/**
    Extracts part of string from beginning leading to index.
    @param index Location within string buffer to split the string on.
*/
inline String
String::ExtractToIndex(IndexT index) const
{
    j_assert(index < this->length);
    String ret(this->CharPtr(), index);
    return ret;
}

//------------------------------------------------------------------------------
/**
    Extracts part of the string from beginning up until character.
    Locates the first occurrence of said character.
    @param c Character to end the new string on.
*/
inline String
String::ExtractToFirstChar(char c) const
{
    String ret;
    ptrdiff index = this->FindFirst(c);
    if (index != -1)
    {
        ret.Set(this->CharPtr(), index);
    }
    return ret;
}

//------------------------------------------------------------------------------
/**
    Extracts part of the string from beginning up until character.
    Locates the last occurrence of said character.
    @param c Character to end the new string on.
*/
inline String
String::ExtractToLastChar(char c) const
{
    String ret;
	ptrdiff index = this->FindLast(c);
    if (index != -1)
    {
        ret.Set(this->CharPtr(), index);
    }
    return ret;
}

//------------------------------------------------------------------------------
/**
    Extracts portion of string starting at character up until the end.
    Locates the first occurrence of said character.
    @param c Character to start the new string from.
*/
inline String
String::ExtractToEndFromFirst(char c) const
{
    String ret;
	ptrdiff index = this->FindFirst(c);
    if (index != -1)
    {
        ret.Set(this->CharPtr() + index);
    }
    return ret;
}

//------------------------------------------------------------------------------
/**
    Extracts portion of string starting at character up until the end.
    Locates the last occurrence of said character.
    @param c Character to start the new string from.
*/
inline String
String::ExtractToEndFromLast(char c) const
{
    String ret;
	ptrdiff index = this->FindLast(c);
    if (index != -1)
    {
        ret.Set(this->CharPtr() + index);
    }
    return ret;
}

//------------------------------------------------------------------------------
/**
    Replaces every occurence of one char with another.
    @param find Character to locate
    @param replace Character to replace 'find' with.
*/
inline void
String::Replace(const char find, const char replace)
{
    char* str = const_cast<char*>(this->CharPtr());
    uint32 index;
    for (index = 0; index < this->length; index++)
    {
        if (str[index] == find) str[index] = replace;
    }
}

//------------------------------------------------------------------------------
/**
*/
inline Core::String
String::Sprintf(const char* format, ...)
{
    String ret;
    va_list argList;
    va_start(argList, format);
    char buf[4096];
    vsnprintf(buf, sizeof(buf), format, argList);
    va_end(argList);
    ret.Set(buf);
    return ret;
}

//------------------------------------------------------------------------------
/**
    Return length of string.
*/
inline const SizeT
String::Length() const
{
    return this->length;
}

//------------------------------------------------------------------------------
/**
    Returns string as const char*
    @return If string fits in the 64 byte stack buffer, it is returned, otherwise the heap buffer is used.
*/
inline const char*
String::CharPtr() const
{
	if (nullptr != this->heapBuffer) return this->heapBuffer;
	else							 return this->stackBuffer;
}

//------------------------------------------------------------------------------
/**
    Generate 32 bit hash from string.
*/
inline const uint32
String::Hash() const
{
    uint32 hash = 0;
    const char* ptr = this->CharPtr();
	SizeT len = this->length;
	SizeT i;
    for (i = 0; i < len; i++)
    {
        hash += ptr[i];
        hash += hash << 10;
        hash ^= hash >>  6;
    }
    hash += hash << 3;
    hash ^= hash >> 11;
    hash += hash << 15;
    return hash;
}

//------------------------------------------------------------------------------
/**
*/
inline void
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

}} // namespace JARVIS::Core