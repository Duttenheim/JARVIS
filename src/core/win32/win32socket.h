#pragma once
//------------------------------------------------------------------------------
/**
	@class JARVIS::Win32::Socket
	
	Implements a WINSOCK interface.
	
	(C) 2016  See the LICENSE file.
*/
//------------------------------------------------------------------------------
#include "ref.h"
namespace JARVIS {
namespace Win32
{
class Socket : public Core::Ref
{
	__ClassDecl(Socket);
public:
	/// constructor
	Socket();
	/// destructor
	virtual ~Socket();
private:
};
}} // namespace JARVIS::Win32