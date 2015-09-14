#pragma once
//------------------------------------------------------------------------------
/**
	@class JARVIS::Math::Mat4
	
    An SSE-accellerated 4D homogenous matrix.
	
	(C) 2015 See the LICENSE file.
 */
//------------------------------------------------------------------------------
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
    }
    __m128 sse[4];
};

class Mat4
{
public:
    /// constructor
    Mat4();
    /// destructor
    virtual ~Mat4();
    
protected:
    __m128_mat m;
};

}} // namespace JARVIS::Math