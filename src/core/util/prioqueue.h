#pragma once
//------------------------------------------------------------------------------
/**
	@class JARVIS::Util::PrioQueue
	
	Implements a priority queue, similar to an ordinary queue,
	but appends to the queue dependent on the priority of the item.

	It's implemented as a Fibonacci heap internally.
	
	(C) 2016 See the LICENSE file.
*/
//------------------------------------------------------------------------------
namespace JARVIS {
namespace Util
{
template <class TYPE>
class PrioQueue
{
public:
	/// constructor
	PrioQueue();
	/// destructor
	virtual ~PrioQueue();
private:
	Util::Array<TYPE> arr;
};
}} // namespace JARVIS::Util