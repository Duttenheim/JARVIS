#pragma once
//------------------------------------------------------------------------------
/**
	@class JARVIS::Math::Point
	
    Point is a 4D homogenous vector which retains its w-coordinate as 1.
	
	(C) 2015 See the LICENSE file.
 */
//------------------------------------------------------------------------------
#include "vec4.h"
namespace JARVIS {
namespace Math
{
class align_16 Point : public Vec4
{
public:
    /// constructor
    Point();
    /// destructor
    virtual ~Point();
    
    /// construct from single float value (splat)
    Point(const float32& v);
    /// construct from four float values
    Point(const float32& x, const float32& y, const float32& z);
    /// copy constructor
    Point(const Point& rhs);
    /// construct from Vec4
    Point(const Vec4& rhs);
    /// construct from Vec3
    Point(const Vec3& rhs);
    
    /// calcuate distance between points
    static float32 distance(const Point& lhs, const Point& rhs);

private:

    /// normalize precise, hidden since normalizing a point is pointless (heh)
    static Vec4 normalize(const Vec4& vec);
    /// normalize fast, hidden since normalizing a point is pointless (heh)
    static Vec4 normalize_fast(const Vec4& vec);
    
};

//------------------------------------------------------------------------------
/**
*/
inline
Point::Point()
{
    this->v.sse = _mm_setr_ps(0, 0, 0, 1);
}

//------------------------------------------------------------------------------
/**
*/
inline
Point::~Point()
{
    // empty
}

//------------------------------------------------------------------------------
/**
*/
inline
Point::Point(const float32& v)
{
    this->v.sse = _mm_set1_ps(v);
}

//------------------------------------------------------------------------------
/**
*/
inline
Point::Point(const float32& x, const float32& y, const float32& z)
{
    this->v.sse = _mm_setr_ps(x, y, z, 1);
}

//------------------------------------------------------------------------------
/**
*/
inline
Point::Point(const Point& rhs)
{
    this->v.sse = rhs.v.sse;
}

//------------------------------------------------------------------------------
/**
*/
inline
Point::Point(const Vec4& rhs)
{
	const __m128 control = _mm_setr_ps(0, 0, 0, 0xFFFFFFFF);
    this->v.sse = _mm_sel_ps_xor(rhs.v.sse, Vec4::one.sse, control);
}

//------------------------------------------------------------------------------
/**
*/
inline
Point::Point(const Vec3& rhs)
{
    const __m128 control = _mm_setr_ps(0, 0, 0, 0xFFFFFFFF);
    this->v.sse = _mm_sel_ps_xor(rhs.v.sse, Vec4::one.sse, control);
}

//------------------------------------------------------------------------------
/**
*/
inline float32
Point::distance(const Point& lhs, const Point& rhs)
{
    __m128 temp = _mm_sub_ps(lhs.v.sse, rhs.v.sse);
    return _mm_cvtss_f32(_mm_sqrt_ps(_mm_dp_ps(temp, temp, 0xFF)));
}
}} // namespace JARVIS::Math