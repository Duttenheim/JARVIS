//------------------------------------------------------------------------------
/**
    @file testscrap/main.cc
    
	Main entry point for scrap test.
	
	(C) 2015 See the LICENSE file.
*/
#include "config.h"
#include "functional/function.h"
#include "util/array.h"
#include "application.h"
#include "math/vec4.h"
#include "math/vec3.h"
#include "math/mat4.h"
#include <iostream>
#include <vector>
#include <map>
#include <random>

using namespace JARVIS::Core;
using namespace JARVIS::Math;

namespace JARVIS {
class PoolTest : public Core::Ref
{
    __ClassDeclPool(PoolTest);
    
    /// constructor
    PoolTest(int32 a, int32 b, int32 c) : a(a), b(b), c(c){};
private:
        int32 a, b, c;
};
__Pool(PoolTest);

}

enum Test
{
    A,
    B,
    C,
    D
};

Test SwitchTestString(const char* name)
{
    __SWITCHSTRING(name)
    {
        __FROMSTRING(Test::A);
        __FROMSTRING(Test::B);
        __FROMSTRING(Test::C);
        __FROMSTRING(Test::D);
        __DEFAULT(Test::A);
    }
}

Vec4 SupportVertex(const Vec4& dir, const Array<Vec4>& polygon)
{
    float dist = 0;
    Vec4 ret(0);
    
    for (uint32 i = 0; i < polygon.Size(); i++)
    {
        // produce Vec3 dot product
        float prod = Vec3::dot(polygon[i], dir);
        if (prod > dist) dist = prod, ret = polygon[i];
    }
    return ret;
}

Array<Vec4> Minkowski(const Array<Vec4>& A, const Array<Vec4>& B)
{
    Array<Vec4> ret;
    for (Vec4 a : A)
    {
        for (Vec4 b : B)
        {
            ret.Append(a-b);
        }
    }
    return ret;
}

JARVIS_MAIN
{
    
    float* blorf1 = new float[65535];
    blorf1[0] = 1;
    blorf1[1] = 2;
    blorf1[2] = 3;
    float* blorf2 = new float[65535];
    blorf2[0] = 4;
    blorf2[1] = 5;
    blorf2[2] = 6;
    
    blorf2 = blorf1;
    float* blorf3;
    blorf3 = blorf1;
    delete blorf3;
    blorf2[65533] = 3.0f;
    blorf1[65004] = 3.0f;
    blorf3[50000] = 3.0f;
    blorf1[65535 * 10] = 0.0f;

    
	Array<Ptr<Function<void()>>> arr;
    auto blorf = Functional::Lambda([]() { printf("BLORF\n"); });
    blorf->Call();
    auto florb = Functional::Lambda([]() { printf("FLORB\n"); });
    florb->Call();
    blorf = florb;
    blorf->Call();
    florb->Call();
        memset(blorf1, 0, 65535 * sizeof(float));
	uint32 foobar = 5;
	arr.Append(Functional::Lambda([&]() { printf("Hej! %d\n", foobar); }));
	arr.Append(Functional::Lambda([&]() { printf("Hej då! %d\n", foobar); }));
    arr[0]->Call();
    arr[1]->Call();
	arr.RemoveIndex(0);
	arr.RemoveIndex(0);

    Ptr<JARVIS::PoolTest> p1 = JARVIS::PoolTest::Create(1, 2, 3);
    Ptr<JARVIS::PoolTest> p2 = JARVIS::PoolTest::Create(4, 5, 6);
    Ptr<JARVIS::PoolTest> p3 = JARVIS::PoolTest::Create(1, 2, 3);
    Ptr<JARVIS::PoolTest> p4 = JARVIS::PoolTest::Create(4, 5, 6);
    
    p1 = nullptr;
    p2 = nullptr;
    p3 = nullptr;
    p4 = nullptr;
    
    Array<Vec4> A = {
    Vec4(-0.5, -0.5, -0.5, 1),
    Vec4(0.5, -0.5, -0.5, 1),
    Vec4(-0.5, 0.5, -0.5, 1),
    Vec4(0.5, 0.5, -0.5, 1),
    Vec4(-0.5, -0.5, 0.5, 1),
    Vec4(0.5, -0.5, 0.5, 1),
    Vec4(-0.5, 0.5, 0.5, 1),
    Vec4(0.5, 0.5, 0.5, 1),
    };
    Array<Vec4> B = A;
    
    std::random_device dev;
    std::mt19937 mt(dev());
    std::uniform_real_distribution<float> angle(0.0f, 3.14f);

    for (uint32 i = 0; i < 10; i++)
    {
        Mat4 trans1 = Mat4::Multiply(Mat4::RotationX(angle(mt)), Mat4::RotationY(angle(mt)));
        Mat4 trans2 = Mat4::Multiply(Mat4::RotationX(angle(mt)), Mat4::RotationY(angle(mt)));
        for (Vec4& v : A)
        {
            v = Mat4::Transform(v, trans1);
        }
        
        for (Vec4& v : B)
        {
            v = Mat4::Transform(v, trans2);
        }
        
        std::uniform_real_distribution<float> dirX(-1, 1);
        std::uniform_real_distribution<float> dirY(-1, 1);
        std::uniform_real_distribution<float> dirZ(-1, 1);
        Vec4 dir = Vec4(dirX(mt), dirY(mt), dirZ(mt), 0);
        Vec4 smart = SupportVertex(dir, A) - SupportVertex(-dir, B);
        Vec4 dumb = SupportVertex(dir, Minkowski(A, B));
        j_assert(Vec4::equal_all(smart, dumb));
    }
    
    String a = "Foobar";
    Array<String> arrA = {a};
    Array<String> arrB = arrA;


	std::cin.get();
	return 0;
}
