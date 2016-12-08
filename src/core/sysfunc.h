#pragma once
//------------------------------------------------------------------------------
/**
	@class JARVIS::Core::SysFunc
	
	Implements the OS-specific system functions
	
	(C) 2016 See the LICENSE file.
*/
//------------------------------------------------------------------------------
#if __WIN32__
#include "win32/win32sysfunc.h"
namespace JARVIS {
namespace Core {
using SysFunc = JARVIS::Win32::SysFunc;
}} // namespace JARVIS::Core
#elif __APPLE__
#include "apple/applesysfunc.h"
namespace JARVIS {
namespace Core {
using SysFunc = JARVIS::Apple::SysFunc;
}} // namespace JARVIS::Core
#elif __LINUX__
#include "posix/posixsysfunc.h"
namespace JARVIS {
namespace Core {
using SysFunc = JARVIS::Posix::SysFunc;
}} // namespace JARVIS::Core
#endif