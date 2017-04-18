#pragma once
//------------------------------------------------------------------------------
/**
	@class JARVIS::Math::Mat3
	
    3x3 Matrix implementation, well, not at the moment
	
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
	/// construct from floats
	Mat3(float f11, float f12, float f13,
		 float f21, float f22, float f23,
		 float f31, float f32, float f33);
    /// destructor
    virtual ~Mat3();
    
private:
};

//------------------------------------------------------------------------------
/**
*/
inline
Mat3::Mat3(float f11, float f12, float f13, float f21, float f22, float f23, float f31, float f32, float f33) :
	Mat4(f11, f12, f13, 0, f21, f22, f23, 0, f31, f32, f33, 0, 0, 0, 0, 1)
{
	// empty
}

}} // namespace JARVIS::Math