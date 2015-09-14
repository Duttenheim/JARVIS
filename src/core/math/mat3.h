#pragma once
//------------------------------------------------------------------------------
/**
	@class JARVIS::Math::Mat3
	
    3x3 Matrix implementation
	
	(C) 2015 See the LICENSE file.
*/
//------------------------------------------------------------------------------
#include "mat4.h"
namespace JARVIS {
namespace Math
{
class Mat3 : public Mat4
{
public:
    /// constructor
    Mat3();
    /// destructor
    virtual ~Mat3();
    
private:
};

}} // namespace JARVIS::Math