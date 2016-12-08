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

class align_16 Mat4
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
    /// create a new matrix which is moved in world space
    static Mat4 Translation(const float x, const float y, const float z);
    /// create a new matrix which scales all axis uniformly
    static Mat4 Scaling(const float x);
    /// create a matrix which scaled each axis individually
    static Mat4 Scaling(const float x, const float y, const float z);
    /// create a new perspective matrix
    static Mat4 Perspective(const float width, const float height, const float near, const float far, const float zrange = 1.0f, const float up = 1.0f);
    /// create a new perspective matrix for off-center
    static Mat4 PerspectiveOffCenter(const float left, const float right, const float top, const float bottom, const float near, const float far, const float zrange = 1.0f, const float up = 1.0f);

    
    /// multiply two matrices
    static Mat4 Multiply(const Mat4& lhs, const Mat4& rhs);
    /// transform vector with matrix
    static Vec4 Transform(const Vec4& vec, const Mat4& mat);
    
    /// get as float array
    const float* Get() const;
    
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
    res.m.sse[0] = _mm_setr_ps(cosine, 0, -sine, 0);
    res.m.sse[2] = _mm_setr_ps(sine, 0, cosine, 0);
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
inline Mat4
Math::Mat4::Translation(const float x, const float y, const float z)
{
    Math::Mat4 mat;
    mat.m.fvv[3][0] = x;
    mat.m.fvv[3][1] = y;
    mat.m.fvv[3][2] = z;
    return mat;
}

//------------------------------------------------------------------------------
/**
*/
inline Mat4
Math::Mat4::Scaling(const float x)
{
    Math::Mat4 mat;
    mat.m.fvv[0][0] = x;
    mat.m.fvv[1][1] = x;
    mat.m.fvv[2][2] = x;
    return mat;
}

//------------------------------------------------------------------------------
/**
*/
inline Mat4
Math::Mat4::Scaling(const float x, const float y, const float z)
{
    Math::Mat4 mat;
    mat.m.fvv[0][0] = x;
    mat.m.fvv[1][1] = y;
    mat.m.fvv[2][2] = z;
    return mat;
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

//------------------------------------------------------------------------------
/**
*/
inline
Mat4
Mat4::Perspective(const float width, const float height, const float near, const float far, const float zrange, const float up)
{
    Mat4 res;
    const float dist = far / (near - far);
    res.m.sse[0] = _mm_setr_ps(2.0f * near/width, 0, 0, 0);
    res.m.sse[1] = _mm_setr_ps(0, 2.0f * near/height*up, 0, 0);
    res.m.sse[2] = _mm_setr_ps(0, 0, dist * zrange, -1);
    res.m.sse[3] = _mm_setr_ps(0, 0, dist * near * zrange, 0);
    return res;
}

//------------------------------------------------------------------------------
/**
    TODO: implement me!
*/
inline
Mat4
Mat4::PerspectiveOffCenter(const float left, const float right, const float top, const float bottom, const float near, const float far, const float zrange, const float up)
{
    Mat4 res;
    return res;
}

//------------------------------------------------------------------------------
/**
*/
inline
const float*
Mat4::Get() const
{
    return this->m.fv;
}

}} // namespace JARVIS::Math