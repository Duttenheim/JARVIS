#pragma once
//------------------------------------------------------------------------------
/**
	@class JARVIS::Math::Vec4
	
    4-dimensional SSE vector representation for homogenous coordinates
	
	(C) 2015 See the LICENSE file.
*/
//------------------------------------------------------------------------------
#include "config.h"

//------------------------------------------------------------------------------
/**
    Fast vector select
*/
__m128
_mm_sel_ps_xor(const __m128& a, const __m128& b, const __m128& mask)
{
    // (((b ^ a) & mask)^a)
    return _mm_xor_ps(a, _mm_and_ps(mask, _mm_xor_ps(b, a)));
}

namespace JARVIS {
namespace Math
{

union __m128_vec
{
    float fv[4];
    __m128 sse;
};

class Vec3;
class align_16 Vec4
{
public:
    /// constructor
    Vec4();
    /// destructor
    virtual ~Vec4();
    
    /// construct from single float value (splat)
    Vec4(const float32& v);
    /// construct from four float values
    Vec4(const float32& x, const float32& y, const float32& z, const float32& w);
    /// construct from __m128
    Vec4(const __m128& vec);
    /// construct from __m128_vec
    Vec4(const __m128_vec& vec);
    /// copy constructor
    Vec4(const Vec4& rhs);
    /// constructor from Vec3
    Vec4(const Vec3& rhs);
    
    /// get x-coordinate
    float32 x() const;
    /// get y-coordinate
    float32 y() const;
    /// get z-coordinate
    float32 z() const;
    /// get w-coordinate
    float32 w() const;
    
    /// get x-coordinate read/write
    float32& x();
    /// get y-coordinate read/write
    float32& y();
    /// get z-coordinate read/write
    float32& z();
    /// get w-coordinate read/write
    float32& w();
    
    /// assignment operator
    void operator=(const Vec4& rhs);
    
    /// performs a component-wise addition
    Vec4 operator+(const Vec4& rhs) const;
    /// performs a component-wise subtraction
    Vec4 operator-(const Vec4& rhs) const;
    /// performs a component-wise multiplication
    Vec4 operator*(const Vec4& rhs) const;
    /// performs a multiplication with a single float value
    Vec4 operator*(const float32& scalar) const;
    /// performs a component-wise division
    Vec4 operator/(const Vec4& rhs) const;
    /// performs a division using a single float vlaue
    Vec4 operator/(const float32& scalar) const;
    
    /// load from a float pointer
    void load(float* buf);
    /// save to float pointer (does not allocate!)
    void store(float* buf);
    
    /// dot product as single float
    static float32 dot(const Vec4& lhs, const Vec4& rhs);
    /// dot product as vector of splatted result
    static Vec4 dot_vector(const Vec4& lhs, const Vec4& rhs);
    /// cross product, will operate on 3 dimensions
    static Vec4 cross(const Vec4& lhs, const Vec4& rhs);
    /// maximize per component
    static Vec4 maximize(const Vec4& lhs, const Vec4& rhs);
    /// maximize per component
    static Vec4 minimize(const Vec4& lhs, const Vec4& rhs);
    
    /// returns true if all components from v1 is lesser than v2
    static bool less_all(const Vec4& lhs, const Vec4& rhs);
    /// returns true if any component from v1 is lesser than v2
    static bool less_any(const Vec4& lhs, const Vec4& rhs);
    /// returns true if all components from v1 is lesser than v2
    static bool less_equal_all(const Vec4& lhs, const Vec4& rhs);
    /// returns true if any component from v1 is lesser than v2
    static bool less_equal_any(const Vec4& lhs, const Vec4& rhs);
    /// returns true if all components from v1 is bigger than v2
    static bool greater_all(const Vec4& lhs, const Vec4& rhs);
    /// returns true if any component from v1 is bigger than v2
    static bool greater_any(const Vec4& lhs, const Vec4& rhs);
    /// returns true if all components from v1 is bigger than v2
    static bool greater_equal_all(const Vec4& lhs, const Vec4& rhs);
    /// returns true if any component from v1 is bigger than v2
    static bool greater_equal_any(const Vec4& lhs, const Vec4& rhs);
    /// returns true if all components from v1 and v2 are equal
    static bool equal_all(const Vec4& lhs, const Vec4& rhs);
    /// returns true if any component from v1 and v2 are equal
    static bool equal_any(const Vec4& lhs, const Vec4& rhs);
    
    /// returns a vector representing a per-component result for which are less
    static Vec4 less(const Vec4& lhs, const Vec4& rhs);
    /// returns a vector representing a per-component result for which are greater
    static Vec4 greater(const Vec4& lhs, const Vec4& rhs);
    /// returns a vector representing a per-component result for which are equal
    static Vec4 equal(const Vec4& lhs, const Vec4& rhs);
    
    /// normalize precise
    static Vec4 normalize(const Vec4& vec);
    /// normalize fast
    static Vec4 normalize_fast(const Vec4& vec);
    
    /// public convenience vectors
    static const Vec4 zero;
    static const Vec4 one;
    
private:
    friend class Vec3;
    friend class Vector;
    friend class Point;
    __m128_vec v;
};

//------------------------------------------------------------------------------
/**
*/
Vec4::Vec4()
{
    this->v.sse = _mm_setr_ps(0, 0, 0, 0);
}

//------------------------------------------------------------------------------
/**
*/
Vec4::~Vec4()
{
    // empty
}

//------------------------------------------------------------------------------
/**
*/
Vec4::Vec4(const float32& v)
{
    this->v.sse = _mm_set1_ps(v);
}

//------------------------------------------------------------------------------
/**
*/
Vec4::Vec4(const float32& x, const float32& y, const float32& z, const float32& w)
{
    this->v.sse = _mm_setr_ps(x, y, z, w);
}

//------------------------------------------------------------------------------
/**
*/
Vec4::Vec4(const __m128& vec)
{
    this->v.sse = vec;
}

//------------------------------------------------------------------------------
/**
*/
Vec4::Vec4(const __m128_vec& vec)
{
    this->v.sse = vec.sse;
}

//------------------------------------------------------------------------------
/**
*/
Vec4::Vec4(const Vec4& rhs)
{
    this->v.sse = rhs.v.sse;
}

//------------------------------------------------------------------------------
/**
    Setup static vector types which might be useful
*/
const Vec4 Vec4::zero = Vec4(0.0f);
const Vec4 Vec4::one = Vec4(1.0f);

//------------------------------------------------------------------------------
/**
*/
inline float32
Vec4::x() const
{
    float32 res;
    _mm_store_ss(&res, this->v.sse);
    return res;
}

//------------------------------------------------------------------------------
/**
*/
inline float32
Vec4::y() const
{
    float32 res;
    __m128 temp = _mm_shuffle_ps(this->v.sse, this->v.sse, _MM_SHUFFLE(1,1,1,1));
    _mm_store_ss(&res, temp);
    return res;
}

//------------------------------------------------------------------------------
/**
*/
inline float32
Vec4::z() const
{
    float32 res;
    __m128 temp = _mm_shuffle_ps(this->v.sse, this->v.sse, _MM_SHUFFLE(2,2,2,2));
    _mm_store_ss(&res, temp);
    return res;
}

//------------------------------------------------------------------------------
/**
*/
inline float32
Vec4::w() const
{
    float32 res;
    __m128 temp = _mm_shuffle_ps(this->v.sse, this->v.sse, _MM_SHUFFLE(3,3,3,3));
    _mm_store_ss(&res, temp);
    return res;
}

//------------------------------------------------------------------------------
/**
*/
inline float32&
Vec4::x()
{
    return this->v.fv[0];
}

//------------------------------------------------------------------------------
/**
*/
inline float32&
Vec4::y()
{
    return this->v.fv[1];
}

//------------------------------------------------------------------------------
/**
*/
inline float32&
Vec4::z()
{
    return this->v.fv[2];
}

//------------------------------------------------------------------------------
/**
*/
inline float32&
Vec4::w()
{
    return this->v.fv[3];
}

//------------------------------------------------------------------------------
/**
*/
inline void
Vec4::operator=(const Math::Vec4& rhs)
{
    this->v.sse = rhs.v.sse;
}

//------------------------------------------------------------------------------
/**
*/
inline Vec4
Vec4::operator+(const Math::Vec4& rhs) const
{
    return _mm_add_ps(this->v.sse, rhs.v.sse);
}

//------------------------------------------------------------------------------
/**
*/
inline Vec4
Vec4::operator-(const Math::Vec4& rhs) const
{
    return _mm_sub_ps(this->v.sse, rhs.v.sse);
}

//------------------------------------------------------------------------------
/**
*/
inline Vec4
Vec4::operator*(const Math::Vec4& rhs) const
{
    return _mm_mul_ps(this->v.sse, rhs.v.sse);
}

//------------------------------------------------------------------------------
/**
*/
inline Vec4
Vec4::operator*(const float32& v) const
{
    return _mm_mul_ps(this->v.sse, _mm_set1_ps(v));
}

//------------------------------------------------------------------------------
/**
*/
inline Vec4
Vec4::operator/(const Math::Vec4& rhs) const
{
    return _mm_div_ps(this->v.sse, rhs.v.sse);
}

//------------------------------------------------------------------------------
/**
*/
inline Vec4
Vec4::operator/(const float32& v) const
{
    return _mm_div_ps(this->v.sse, _mm_set1_ps(v));
}

//------------------------------------------------------------------------------
/**
*/
inline void
Vec4::load(float* buf)
{
    this->v.sse = _mm_load_ps(buf);
}

//------------------------------------------------------------------------------
/**
*/
inline void
Vec4::store(float* buf)
{
    _mm_store_ps(buf, this->v.sse);
}

//------------------------------------------------------------------------------
/**
*/
inline float32
Vec4::dot(const Vec4& lhs, const Vec4& rhs)
{
    // 22 will mean all 4 components get dotted, 0
    return _mm_cvtss_f32(_mm_dp_ps(lhs.v.sse, rhs.v.sse, 0xF1));
}

//------------------------------------------------------------------------------
/**
*/
inline Vec4
Vec4::dot_vector(const Vec4& lhs, const Vec4& rhs)
{
    return _mm_dp_ps(lhs.v.sse, rhs.v.sse, 0xF1);
}

//------------------------------------------------------------------------------
/**
*/
inline Vec4
Vec4::cross(const Vec4& lhs, const Vec4& rhs)
{
    __m128 tmp0, tmp1, tmp2, tmp3, result;
	tmp0 = _mm_shuffle_ps(lhs.v.sse, lhs.v.sse, _MM_SHUFFLE(3,0,2,1));
	tmp1 = _mm_shuffle_ps(rhs.v.sse, rhs.v.sse, _MM_SHUFFLE(3,1,0,2));
	tmp2 = _mm_shuffle_ps(lhs.v.sse, lhs.v.sse, _MM_SHUFFLE(3,1,0,2));
	tmp3 = _mm_shuffle_ps(rhs.v.sse, rhs.v.sse, _MM_SHUFFLE(3,0,2,1));
	result = _mm_mul_ps(tmp0, tmp1);
	result = _mm_sub_ps(result, _mm_mul_ps(tmp2, tmp3));
	return result;
}

//------------------------------------------------------------------------------
/**
*/
inline Vec4
Vec4::maximize(const Math::Vec4& lhs, const Math::Vec4& rhs)
{
    return _mm_max_ps(lhs.v.sse, rhs.v.sse);
}

//------------------------------------------------------------------------------
/**
*/
inline Vec4
Vec4::minimize(const Math::Vec4& lhs, const Math::Vec4& rhs)
{
    return _mm_min_ps(lhs.v.sse, rhs.v.sse);
}

//------------------------------------------------------------------------------
/**
*/
inline bool
Vec4::less_all(const Math::Vec4& lhs, const Math::Vec4& rhs)
{
    __m128 temp = _mm_cmplt_ps(lhs.v.sse, rhs.v.sse);
    int res = _mm_movemask_ps(temp);
    return res == 0;
}

//------------------------------------------------------------------------------
/**
*/
inline bool
Vec4::less_any(const Math::Vec4& lhs, const Math::Vec4& rhs)
{
    __m128 temp = _mm_cmplt_ps(lhs.v.sse, rhs.v.sse);
    int res = _mm_movemask_ps(temp);
    return res != 0xF;
}

//------------------------------------------------------------------------------
/**
*/
inline bool
Vec4::less_equal_all(const Math::Vec4& lhs, const Math::Vec4& rhs)
{
    __m128 temp = _mm_cmple_ps(lhs.v.sse, rhs.v.sse);
    int res = _mm_movemask_ps(temp);
    return res == 0;
}

//------------------------------------------------------------------------------
/**
*/
inline bool
Vec4::less_equal_any(const Math::Vec4& lhs, const Math::Vec4& rhs)
{
    __m128 temp = _mm_cmple_ps(lhs.v.sse, rhs.v.sse);
    int res = _mm_movemask_ps(temp);
    return res != 0xF;
}

//------------------------------------------------------------------------------
/**
*/
inline bool
Vec4::greater_all(const Math::Vec4& lhs, const Math::Vec4& rhs)
{
    __m128 temp = _mm_cmpgt_ps(lhs.v.sse, rhs.v.sse);
    int res = _mm_movemask_ps(temp);
    return res == 0xF;
}

//------------------------------------------------------------------------------
/**
*/
inline bool
Vec4::greater_any(const Math::Vec4& lhs, const Math::Vec4& rhs)
{
    __m128 temp = _mm_cmpgt_ps(lhs.v.sse, rhs.v.sse);
    int res = _mm_movemask_ps(temp);
    return res != 0;
}

//------------------------------------------------------------------------------
/**
*/
inline bool
Vec4::greater_equal_all(const Math::Vec4& lhs, const Math::Vec4& rhs)
{
    __m128 temp = _mm_cmpge_ps(lhs.v.sse, rhs.v.sse);
    int res = _mm_movemask_ps(temp);
    return res == 0xF;
}

//------------------------------------------------------------------------------
/**
*/
inline bool
Vec4::greater_equal_any(const Math::Vec4& lhs, const Math::Vec4& rhs)
{
    __m128 temp = _mm_cmpge_ps(lhs.v.sse, rhs.v.sse);
    int res = _mm_movemask_ps(temp);
    return res != 0;
}

//------------------------------------------------------------------------------
/**
*/
inline bool
Vec4::equal_all(const Math::Vec4& lhs, const Math::Vec4& rhs)
{
    __m128 temp = _mm_cmpeq_ps(lhs.v.sse, rhs.v.sse);
    int res = _mm_movemask_ps(temp);
    return res == 0xF;
}

//------------------------------------------------------------------------------
/**
*/
inline bool
Vec4::equal_any(const Math::Vec4& lhs, const Math::Vec4& rhs)
{
    __m128 temp = _mm_cmpeq_ps(lhs.v.sse, rhs.v.sse);
    int res = _mm_movemask_ps(temp);
    return res != 0;
}

//------------------------------------------------------------------------------
/**
*/
inline Vec4
Vec4::less(const Math::Vec4& lhs, const Math::Vec4& rhs)
{
    return _mm_min_ps(_mm_cmplt_ps(lhs.v.sse, rhs.v.sse), Vec4::one.v.sse);
}

//------------------------------------------------------------------------------
/**
*/
inline Vec4
Vec4::greater(const Math::Vec4& lhs, const Math::Vec4& rhs)
{
    return _mm_min_ps(_mm_cmpgt_ps(lhs.v.sse, rhs.v.sse), Vec4::one.v.sse);
}

//------------------------------------------------------------------------------
/**
*/
inline Vec4
Vec4::equal(const Math::Vec4& lhs, const Math::Vec4& rhs)
{
    return _mm_min_ps(_mm_cmpeq_ps(lhs.v.sse, rhs.v.sse), Vec4::one.v.sse);
}

//------------------------------------------------------------------------------
/**
*/
inline Vec4
Vec4::normalize(const Math::Vec4& vec)
{
    if (Vec4::equal_all(vec, zero)) return vec;
    return _mm_div_ps(vec.v.sse, _mm_sqrt_ps(_mm_dp_ps(vec.v.sse, vec.v.sse, 0xFF)));
}

//------------------------------------------------------------------------------
/**
*/
inline Vec4
Vec4::normalize_fast(const Math::Vec4& vec)
{
    if (Vec4::equal_all(vec, zero)) return vec;
    return _mm_mul_ps(vec.v.sse, _mm_rsqrt_ps(_mm_dp_ps(vec.v.sse, vec.v.sse, 0xFF)));
}

}} // namespace JARVIS::Math