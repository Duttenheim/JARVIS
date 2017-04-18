#pragma once
//------------------------------------------------------------------------------
/**
	@class JARVIS::Math::Vector
	
    Implements a 4D homogenous vector which will always retain its w-coordinate as 0.
	
	(C) 2015 See the LICENSE file.
 */
//------------------------------------------------------------------------------
#include "vec4.h"
namespace JARVIS {
namespace Math
{
class align_16 Vector : public Vec4
{
public:
    /// constructor
    Vector();
    /// destructor
    virtual ~Vector();
    
    /// construct from single float value (splat)
    Vector(const float32& v);
    /// construct from four float values
    Vector(const float32& x, const float32& y, const float32& z);
    /// copy constructor
    Vector(const Vector& rhs);
    /// construct from Vec4
    Vector(const Vec4& rhs);
    /// construct from Vec3
    Vector(const Vec3& rhs);
    
    /// calcuate length of vector
    static float32 length(const Vector& lhs);
    
private:
};

//------------------------------------------------------------------------------
/**
*/
inline
Vector::Vector()
{
    this->v.sse = _mm_setr_ps(0, 0, 0, 0);
}

//------------------------------------------------------------------------------
/**
*/
inline
Vector::~Vector()
{
    // empty
}

//------------------------------------------------------------------------------
/**
*/
inline
Vector::Vector(const float32& v)
{
    this->v.sse = _mm_set1_ps(v);
}

//------------------------------------------------------------------------------
/**
*/
inline
Vector::Vector(const float32& x, const float32& y, const float32& z)
{
    this->v.sse = _mm_setr_ps(x, y, z, 0);
}

//------------------------------------------------------------------------------
/**
*/
inline
Vector::Vector(const Vector& rhs)
{
    this->v.sse = rhs.v.sse;
}

//------------------------------------------------------------------------------
/**
*/
inline
Vector::Vector(const Vec4& rhs)
{
    const __m128 control = _mm_setr_ps(0, 0, 0, (float)0xFFFFFFFF);
    this->v.sse = _mm_sel_ps_xor(rhs.v.sse, Vec4::zero.sse, control);
}

//------------------------------------------------------------------------------
/**
*/
inline
Vector::Vector(const Vec3& rhs)
{
	const __m128 control = _mm_setr_ps(0, 0, 0, (float)0xFFFFFFFF);
    this->v.sse = _mm_sel_ps_xor(rhs.v.sse, Vec4::zero.sse, control);
}

//------------------------------------------------------------------------------
/**
*/
inline float32
Vector::length(const Vector& rhs)
{
    return _mm_cvtss_f32(_mm_sqrt_ps(_mm_dp_ps(rhs.v.sse, rhs.v.sse, 0xFF)));
}

}} // namespace JARVIS::Math