#include <metal_stdlib>
using namespace metal;

struct VertexOut
{
    float4 pos [[ position ]];
};

struct Transforms
{
    float4x4 view;
    float4x4 transform;
};

vertex VertexOut basic_vertex(
    const device packed_float3* vertex_array [[ buffer(0) ]],
    constant Transforms& trans [[ buffer(1) ]],
    unsigned int vid [[ vertex_id ]])
{
    VertexOut out;
    out.pos = trans.view * trans.transform * float4(vertex_array[vid], 1);
    return out;
}

fragment half4 basic_fragment(VertexOut v)
{
    return half4(v.pos.z, v.pos.z, v.pos.z, 1);
}