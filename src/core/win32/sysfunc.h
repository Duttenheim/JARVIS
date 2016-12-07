#pragma once
//------------------------------------------------------------------------------
/**
	@class JARVIS::Win32::SysFunc
	
	Implements Windows-specific system functions
	
	(C) 2016 See the LICENSE file.
*/
//------------------------------------------------------------------------------
namespace JARVIS {
namespace Win32
{
class SysFunc
{
public:
	/// constructor
	SysFunc();
	/// destructor
	virtual ~SysFunc();

	/// get location of exe
	Core::String BinDir();
private:
};

}} // namespace JARVIS::Win32