#pragma once
//------------------------------------------------------------------------------
/**
	@class JARVIS::Math::Mat4
	
    An SSE-accellerated 4D homogenous matrix.
	
	(C) 2015 See the LICENSE file.
 */
//------------------------------------------------------------------------------
#include "vec4.h"
#include <math.h>
namespace JARVIS {
namespace Math
{

union __m128_mat
{
    float fv[16];
    float fvv[4][4];
    struct
    {
        float _11, _12, _13, _14,
              _21, _22, _23, _24,
              _31, _32, _33, _34,
              _41, _42, _43, _44;
    } m;
    __m128_vec rows[4];
    __m128 sse[4];
};

class Mat4
{
public:
    /// constructor
    Mat4();
    /// destructor
    virtual ~Mat4();
    
    /// create new matrix using global X axis
    static Mat4 RotationX(const float angle);
    /// create new matrix using global Y axis
    static Mat4 RotationY(const float angle);
    /// create new matrix using global Z axis
    static Mat4 RotationZ(const float angle);
    
    /// multiply two matrices
    static Mat4 Multiply(const Mat4& lhs, const Mat4& rhs);
    /// transform vector with matrix
    static Vec4 Transform(const Vec4& vec, const Mat4& mat);
    
protected:
    __m128_mat m;
};

//------------------------------------------------------------------------------
/**
*/
inline
Mat4::Mat4()
{
    m.sse[0] = _mm_setr_ps(1, 0, 0, 0);
    m.sse[1] = _mm_setr_ps(0, 1, 0, 0);
    m.sse[2] = _mm_setr_ps(0, 0, 1, 0);
    m.sse[3] = _mm_setr_ps(0, 0, 0, 1);
}

//------------------------------------------------------------------------------
/**
*/
inline
Mat4::~Mat4()
{
    // empty
}

//------------------------------------------------------------------------------
/**
*/
inline
Mat4
Mat4::RotationX(const float angle)
{
    Mat4 res;
    const float sine = sin(angle);
    const float cosine = cos(angle);
    res.m.sse[1] = _mm_setr_ps(0, cosine, -sine, 0);
    res.m.sse[2] = _mm_setr_ps(0, sine, cosine, 0);
    return res;
}

//------------------------------------------------------------------------------
/**
*/
inline
Mat4
Mat4::RotationY(const float angle)
{
    Mat4 res;
    const float sine = sin(angle);
    const float cosine = cos(angle);
    res.m.sse[0] = _mm_setr_ps(cosine, 0, sine, 0);
    res.m.sse[2] = _mm_setr_ps(-sine, 0, cosine, 0);
    return res;
}

//------------------------------------------------------------------------------
/**
*/
inline
Mat4
Mat4::RotationZ(const float angle)
{
    Mat4 res;
    const float sine = sin(angle);
    const float cosine = cos(angle);
    res.m.sse[0] = _mm_setr_ps(cosine, -sine, 0, 0);
    res.m.sse[1] = _mm_setr_ps(sine, cosine, 0, 0);
    return res;
}

//------------------------------------------------------------------------------
/**
*/
Mat4
Mat4::Multiply(const Mat4& lhs, const Mat4& rhs)
{
    Mat4 res;
    for (uint32 i = 0; i < 4; i++)
    {
        __m128 brod0 = _mm_set1_ps(lhs.m.rows[i].fv[0]);
        __m128 brod1 = _mm_set1_ps(lhs.m.rows[i].fv[1]);
        __m128 brod2 = _mm_set1_ps(lhs.m.rows[i].fv[2]);
        __m128 brod3 = _mm_set1_ps(lhs.m.rows[i].fv[3]);
        res.m.rows[i].sse = _mm_add_ps(
                    _mm_add_ps(
                        _mm_mul_ps(brod0, rhs.m.rows[0].sse),
                        _mm_mul_ps(brod1, rhs.m.rows[1].sse)),
                    _mm_add_ps(
                        _mm_mul_ps(brod2, rhs.m.rows[2].sse),
                        _mm_mul_ps(brod3, rhs.m.rows[3].sse)));
        
    }
    return res;
}

//------------------------------------------------------------------------------
/**
*/
inline
Vec4
Mat4::Transform(const Vec4& vec, const Mat4& mat)
{
    __m128 x = _mm_dp_ps(vec.v.sse, mat.m.sse[0], 0xF1);
    __m128 y = _mm_dp_ps(vec.v.sse, mat.m.sse[1], 0xF2);
    __m128 z = _mm_dp_ps(vec.v.sse, mat.m.sse[2], 0xF4);
    __m128 w = _mm_dp_ps(vec.v.sse, mat.m.sse[3], 0xF8);
    return _mm_add_ps(_mm_add_ps(x, y), _mm_add_ps(z, w));
}

}} // namespace JARVIS::Math