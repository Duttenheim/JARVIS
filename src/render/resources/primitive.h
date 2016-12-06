#pragma once
//------------------------------------------------------------------------------
/**
	@class JARVIS::Render::Primitive
	
    Contains the information used to render a primitive.
    Bind to context prior to rendering in order to make a valid draw.
	
	(C) 2015 See the LICENSE file.
*/
//------------------------------------------------------------------------------
namespace JARVIS {
namespace Render
{
struct Primitive
{
    enum class Topology : uint8
    {
        Point,
        Line,
        LineStrip,
        Triangle,
        TriangleStrip
    };
    
    /// constructor
    Primitive();
    /// destructor
    virtual ~Primitive();
 
    Topology topo;
    uint32 baseIndex;
    uint32 baseVertex;
    uint32 indexCount;
    uint32 vertexCount;
};

//------------------------------------------------------------------------------
/**
*/
inline
Primitive::Primitive() :
    topo(Topology::Triangle),
    baseIndex(0),
    baseVertex(0),
    indexCount(0),
    vertexCount(0)
{
    // empty
}

//------------------------------------------------------------------------------
/**
*/
inline
Primitive::~Primitive()
{
    // empty
}

}} // namespace JARVIS::Render