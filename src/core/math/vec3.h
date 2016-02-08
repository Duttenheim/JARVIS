#pragma once
//------------------------------------------------------------------------------
/**
	@class JARVIS::Math::Vec3

    3-dimensional SSE accelerated vector. Refrain from using this since Vec4 is more SSE-compliant.
	
	(C) 2015 See the LICENSE file.
*/
//------------------------------------------------------------------------------
#include "config.h"
#include "vec4.h"
namespace JARVIS {
namespace Math
{
class Vec3;
class align_16 Vec3 : public Vec4
{
public:
    /// constructor
    Vec3();
    /// destructor
    virtual ~Vec3();
    
    /// construct from single float value (splat)
    Vec3(const float32& v);
    /// construct from four float values
    Vec3(const float32& x, const float32& y, const float32& z);
    /// construct from __m128
    Vec3(const __m128& vec);
    /// construct from __m128_vec
    Vec3(const __m128_vec& vec);
    /// copy constructor
    Vec3(const Vec3& rhs);
    /// create from vec4
    Vec3(const Vec4& rhs);
    /// friend constructor for Vec4 of Vec3
    friend Vec4::Vec4(const Vec3& v);
    
     /// dot product as single float
    static float32 dot(const Vec3& lhs, const Vec3& rhs);
    /// dot product as vector of splatted result
    static Vec3 dot_vector(const Vec3& lhs, const Vec3& rhs);

    /// normalize precise
    static Vec3 normalize(const Vec3& vec);
    /// normalize fast
    static Vec3 normalize_fast(const Vec3& vec);
    
private:
    /// get w-coordinate, hidden and inaccessible for vec3
    float32 w() const;
    /// get w-coordinate read/write, hidden and inaccessible for vec3
    float32& w();
};

//------------------------------------------------------------------------------
/**
*/
inline
Vec3::Vec3()
{
    this->v.sse = _mm_setr_ps(0, 0, 0, 0);
}

//------------------------------------------------------------------------------
/**
*/
inline
Vec3::~Vec3()
{
    // empty
}

//------------------------------------------------------------------------------
/**
*/
inline
Vec3::Vec3(const float32& v)
{
    this->v.sse = _mm_set1_ps(v);
}

//------------------------------------------------------------------------------
/**
*/
inline
Vec3::Vec3(const float32& x, const float32& y, const float32& z)
{
    this->v.sse = _mm_setr_ps(x, y, z, 0);
}

//------------------------------------------------------------------------------
/**
*/
inline
Vec3::Vec3(const __m128& vec)
{
    this->v.sse = vec;
}

//------------------------------------------------------------------------------
/**
*/
inline
Vec3::Vec3(const __m128_vec& vec)
{
    this->v.sse = vec.sse;
}

//------------------------------------------------------------------------------
/**
*/
inline
Vec3::Vec3(const Vec3& rhs)
{
    this->v.sse = rhs.v.sse;
}

//------------------------------------------------------------------------------
/**
*/
inline
Vec3::Vec3(const Vec4& rhs)
{
    this->v.sse = rhs.v.sse;
}

//------------------------------------------------------------------------------
/**
*/
inline
Vec4::Vec4(const Vec3& rhs)
{
    this->v.sse = rhs.v.sse;
}

//------------------------------------------------------------------------------
/**
*/
inline float32
Vec3::dot(const Vec3& lhs, const Vec3& rhs)
{
    // 22 will mean all 4 components get dotted, 0
    return _mm_cvtss_f32(_mm_dp_ps(lhs.v.sse, rhs.v.sse, 0x71));
}

//------------------------------------------------------------------------------
/**
*/
inline Vec3
Vec3::dot_vector(const Vec3& lhs, const Vec3& rhs)
{
    return _mm_dp_ps(lhs.v.sse, rhs.v.sse, 0xF1);
}

//------------------------------------------------------------------------------
/**
*/
inline Vec3
Vec3::normalize(const Math::Vec3& vec)
{
    if (Vec4::equal_all(vec, Vec4::zero)) return vec;
    __m128 temp = _mm_sqrt_ps(_mm_dp_ps(vec.v.sse, vec.v.sse, 0x77));
    return _mm_insert_ps(_mm_div_ps(vec.v.sse, temp), Vec4::zero.sse, 0xF7);
}

//------------------------------------------------------------------------------
/**
*/
inline Vec3
Vec3::normalize_fast(const Math::Vec3& vec)
{
    if (Vec4::equal_all(vec, Vec4::zero)) return vec;
    __m128 temp = _mm_rsqrt_ps(_mm_dp_ps(vec.v.sse, vec.v.sse, 0x77));
    return _mm_mul_ps(vec.v.sse, _mm_insert_ps(temp, Vec4::zero.sse, 0xF7));
}

}} // namespace JARVIS::Math