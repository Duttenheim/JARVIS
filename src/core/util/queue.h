#pragma once
//------------------------------------------------------------------------------
/**
	@class JARVIS::Util::Queue
	
	Implements a LIFO list.
	
	(C) 2016 See the LICENSE file.
*/
//------------------------------------------------------------------------------
namespace JARVIS {
namespace Util
{
template <class TYPE>
class Queue
{
public:
	/// constructor
	Queue();
	/// destructor
	virtual ~Queue();
private:
	Util::Array<TYPE> arr;
};
}} // namespace JARVIS::Util