//------------------------------------------------------------------------------
/**
    @file testscrap/main.cc
    
	Main entry point for scrap test.
	
	(C) 2015 See the LICENSE file.
*/
#include "config.h"
#include "math/vec4.h"
#include "math/vec3.h"
#include "math/vector.h"
#include "math/point.h"
#include "util/timer.h"
#include "threads/persistentthread.h"

using namespace JARVIS::Core;
using namespace JARVIS::Math;

JARVIS_MAIN
{
    Vec4 v1(1,2,3,4), v2(5,6,7,8);
    Vec4 v3 = v1 + v2;
    Vec4 v4(1);
    v4 = Vec4::normalize(v4);
    Vec4 v5(2);
    v5 = Vec4::normalize_fast(v5);
    
    Vec3 v6(1,2,3), v7(4,5,6);
    Vec3 v8 = v6 + v7;
    Vec3 v9 = Vec3(1);
    v9 = Vec3::normalize(v9);
    Vec3 v10 = Vec3(2);
    v10 = Vec3::normalize_fast(v10);
    float dot = Vec3::dot(v6, v7);
    dot = Vec3::dot(v7, v6);
    
    Vector vec(1, 1, 1);
    //float32 len = Vector::length(vec);
    
    Vec4* inputs = new Vec4[2000000];
    Vec4* outputs = new Vec4[2000000];
    Vec4* uniforms = new Vec4(1);
    uniforms[0] = Vec4(1,1,1,1);
    auto ctx = Threading::CreateContext(inputs, outputs, uniforms);
    
    auto specialThreadProc =
	Functional::Lambda([](byte* input, byte* output, byte* uniform) -> void
	{
        Vec4* in = (Vec4*)input;
        Vec4* out = (Vec4*)output;
        Vec4* u = (Vec4*)uniform;
        int32 i;
        for (i = 0; i < 2000000; i++)
        {
            out[i] = Vec4::cross(in[i] + Vec4(1,2,3,4), u[0]);
        }
        const Vec4& vec = out[i-1];
        printf("Result: %f, %f, %f, %f\n", vec.x(), vec.y(), vec.z(), vec.w());
    });
    
    Ptr<Timer> timer = Timer::Create();
    timer->Start();
    Ptr<PersistentThread> pthread = PersistentThread::Create();
    pthread->Start();
    pthread->Enqueue(specialThreadProc, ctx);
    //pthread->Enqueue(specialThreadProc, ctx);
    //pthread->Enqueue(specialThreadProc, ctx);
    //pthread->Enqueue(specialThreadProc, ctx);
    while (pthread->Working());
    pthread->Stop();
    timer->Stop();
    printf("Time taken to complete: %f\n", timer->Time());
    delete [] inputs;
    delete [] outputs;
    delete uniforms;
    
	return 0;
}
